/* esp32-firmware
 * Copyright (C) 2022 Olaf Lüke <olaf@tinkerforge.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include <type_traits>

#include "energy_manager.h"
#include "module_dependencies.h"
#include "musl_libc_timegm.h"

#include "bindings/errors.h"

#include "api.h"
#include "build.h"
#include "event_log.h"
#include "task_scheduler.h"
#include "tools.h"
#include "web_server.h"

#include "gcc_warnings.h"

void EnergyManager::pre_setup()
{
    // States
    state = Config::Object({
        {"phases_switched", Config::Uint8(0)},
        {"input3_state", Config::Bool(false)},
        {"input4_state", Config::Bool(false)},
        {"relay_state", Config::Bool(false)},
        {"error_flags", Config::Uint32(0)},
        {"config_error_flags", Config::Uint32(0)},
        {"external_control", Config::Uint32(EXTERNAL_CONTROL_STATE_DISABLED)},
    });

    low_level_state = Config::Object({
        {"power_at_meter", Config::Float(0)},
        {"power_at_meter_filtered", Config::Float(0)}, //TODO make this int?
        {"power_available", Config::Int32(0)},
        {"power_available_filtered", Config::Int32(0)},
        {"overall_min_power", Config::Int32(0)},
        {"threshold_3to1", Config::Int32(0)},
        {"threshold_1to3", Config::Int32(0)},
        {"charge_manager_available_current", Config::Uint32(0)},
        {"charge_manager_allocated_current", Config::Uint32(0)},
        {"max_current_limited", Config::Uint32(0)},
        {"uptime_past_hysteresis", Config::Bool(false)},
        {"is_3phase", Config::Bool(false)},
        {"wants_3phase", Config::Bool(false)},
        {"wants_3phase_last", Config::Bool(false)},
        {"is_on_last", Config::Bool(false)},
        {"wants_on_last", Config::Bool(false)},
        {"phase_state_change_blocked", Config::Bool(false)},
        {"phase_state_change_delay", Config::Uint32(0)},
        {"on_state_change_blocked", Config::Bool(false)},
        {"on_state_change_delay", Config::Uint32(0)},
        {"charging_blocked", Config::Uint32(0)},
        {"switching_state", Config::Uint32(0)},
        {"consecutive_bricklet_errors", Config::Uint32(0)},
        // Bricklet states below
        {"contactor", Config::Bool(false)},
        {"contactor_check_state", Config::Uint8(0)},
        {"input_voltage", Config::Uint16(0)},
        {"led_rgb", Config::Array({Config::Uint8(0), Config::Uint8(0), Config::Uint8(0)},
            new Config{Config::Uint8(0)}, 3, 3, Config::type_id<Config::ConfUint>())
        },
        {"uptime", Config::Uint32(0)},
    });
    meter_state = Config::Object({ // TODO: Remove?
        {"energy_meter_type", Config::Uint8(0)},
        {"energy_meter_power", Config::Float(0)}, // watt
        {"energy_meter_energy_import", Config::Float(0)}, // kWh
        {"energy_meter_energy_export", Config::Float(0)}, // kWh
    });

    // Config
    config = ConfigRoot(Config::Object({
        {"contactor_installed", Config::Bool(false)},
        {"phase_switching_mode", Config::Uint(PHASE_SWITCHING_AUTOMATIC, PHASE_SWITCHING_MIN, PHASE_SWITCHING_MAX)},
        {"excess_charging_enable", Config::Bool(false)},
        {"default_mode", Config::Uint(0, 0, 3)},
        {"auto_reset_mode", Config::Bool(false)},
        {"auto_reset_time", Config::Uint(0, 0, 1439)},
        {"target_power_from_grid", Config::Int32(0)}, // in watt
        {"guaranteed_power", Config::Uint(1380, 0, 22080)}, // in watt
        {"cloud_filter_mode", Config::Uint(CLOUD_FILTER_MEDIUM, CLOUD_FILTER_OFF, CLOUD_FILTER_STRONG)},
        {"relay_config", Config::Uint8(0)},
        {"relay_rule_when", Config::Uint8(0)},
        {"relay_rule_is", Config::Uint8(0)},
        {"input3_rule_then", Config::Uint8(0)},
        {"input3_rule_then_limit", Config::Uint32(0)}, // in A
        {"input3_rule_is", Config::Uint8(0)},
        {"input3_rule_then_on_high", Config::Uint(MODE_DO_NOTHING, 0, 255)},
        {"input3_rule_then_on_low", Config::Uint(MODE_DO_NOTHING, 0, 255)},
        {"input4_rule_then", Config::Uint8(0)},
        {"input4_rule_then_limit", Config::Uint32(0)}, // in A
        {"input4_rule_is", Config::Uint8(0)},
        {"input4_rule_then_on_high", Config::Uint(MODE_DO_NOTHING, 0, 255)},
        {"input4_rule_then_on_low", Config::Uint(MODE_DO_NOTHING, 0, 255)},
    }), [](const Config &cfg) -> String {
        uint32_t max_current_ma = charge_manager.config_in_use.get("maximum_available_current")->asUint();
        uint32_t input3_rule_then_limit_ma = cfg.get("input3_rule_then_limit")->asUint();
        uint32_t input4_rule_then_limit_ma = cfg.get("input4_rule_then_limit")->asUint();

        if (input3_rule_then_limit_ma > max_current_ma) {
            return "Input 3 current limit exceeds maximum total current of all chargers.";
        }
        if (input4_rule_then_limit_ma > max_current_ma) {
            return "Input 4 current limit exceeds maximum total current of all chargers.";
        }

        if (cfg.get("phase_switching_mode")->asUint() == 3) { // external control
            if (cfg.get("contactor_installed")->asBool() != true)
                return "Can't enable external control with no contactor installed.";
            if (cfg.get("excess_charging_enable")->asBool() != false)
                return "Can't enable external control unless excess charging is disabled.";
            if (cfg.get("default_mode")->asUint() != MODE_FAST)
                return "Can't enable external control with any charging mode besides 'Fast'.";
            if (cfg.get("auto_reset_mode")->asBool() != false)
                return "Can't enable external control unless auto reset mode is disabled.";
            if (cfg.get("input3_rule_then")->asUint() == INPUT_CONFIG_SWITCH_MODE)
                return "Can't enable external control when input 3 is configured to change charging mode.";
            if (cfg.get("input4_rule_then")->asUint() == INPUT_CONFIG_SWITCH_MODE)
                return "Can't enable external control when input 4 is configured to change charging mode.";
        }

        return "";
    });

    debug_config = Config::Object({
        {"hysteresis_time", Config::Uint(HYSTERESIS_MIN_TIME_MINUTES, 0, 60)}, // in minutes
    });

    // Runtime config
    charge_mode = Config::Object({
        {"mode", Config::Uint(0, 0, 3)},
    });
    charge_mode_update = charge_mode;

    external_control = Config::Object({
        {"phases_wanted", Config::Uint32(0)},
    });
    external_control_update = external_control;

    // history
    history_wallbox_5min = Config::Object({
        {"uid", Config::Uint32(0)},
        // date in UTC to avoid DST overlap problems
        {"year", Config::Uint(0, 2000, 2255)},
        {"month", Config::Uint(0, 1, 12)},
        {"day", Config::Uint(0, 1, 31)},
    });

    history_wallbox_daily = Config::Object({
        {"uid", Config::Uint32(0)},
        // date in local time to have the days properly aligned
        {"year", Config::Uint(0, 2000, 2255)},
        {"month", Config::Uint(0, 1, 12)},
    });

    history_energy_manager_5min = Config::Object({
        // date in UTC to avoid DST overlap problems
        {"year", Config::Uint(0, 2000, 2255)},
        {"month", Config::Uint(0, 1, 12)},
        {"day", Config::Uint(0, 1, 31)},
    });

    history_energy_manager_daily = Config::Object({
        // date in local time to have the days properly aligned
        {"year", Config::Uint(0, 2000, 2255)},
        {"month", Config::Uint(0, 1, 12)},
    });
}

void EnergyManager::setup_energy_manager()
{
    if (!this->DeviceModule::setup_device()) {
        logger.printfln("energy_manager: setup_device error. Reboot in 5 Minutes.");

        task_scheduler.scheduleOnce([](){
            trigger_reboot("Energy Manager");
        }, 5 * 60 * 1000);
        return;
    }

    initialized = true;
}

void EnergyManager::check_debug()
{
    task_scheduler.scheduleOnce([this](){
        if (deadline_elapsed(last_debug_keep_alive + 60000) && debug)
        {
            logger.printfln("Debug log creation canceled because no continue call was received for more than 60 seconds.");
            debug = false;
        }
        else if (debug)
            check_debug();
    }, 10000);
}

void EnergyManager::setup()
{
    setup_energy_manager();
    if (!device_found) {
        set_error(ERROR_FLAGS_BRICKLET_MASK);
        return;
    }

    api.addFeature("energy_manager");

    update_status_led();

    // Forgets all settings when new setting is introduced: "Failed to restore persistent config config: JSON object is missing key 'input3_rule_then_limit'\nJSON object is missing key 'input4_rule_then_limit'"
    api.restorePersistentConfig("energy_manager/config", &config);
    config_in_use = config;

#if MODULE_DEBUG_AVAILABLE()
    api.restorePersistentConfig("energy_manager/debug_config", &debug_config);
#endif
    debug_config_in_use = debug_config;

    charge_manager.set_allocated_current_callback([this](uint32_t current_ma){
        //logger.printfln("energy_manager: allocated current callback: %u", current_ma);
        charge_manager_allocated_current_ma = current_ma;
    });

    // Cache config for energy update
    default_mode                = config_in_use.get("default_mode")->asUint();
    excess_charging_enable      = config_in_use.get("excess_charging_enable")->asBool();
    target_power_from_grid_w    = config_in_use.get("target_power_from_grid")->asInt();          // watt
    guaranteed_power_w          = config_in_use.get("guaranteed_power")->asUint();               // watt
    contactor_installed         = config_in_use.get("contactor_installed")->asBool();
    phase_switching_mode        = config_in_use.get("phase_switching_mode")->asUint();
    switching_hysteresis_ms     = debug_config_in_use.get("hysteresis_time")->asUint() * 60 * 1000;    // milliseconds (from minutes)
    max_current_unlimited_ma    = charge_manager.config_in_use.get("maximum_available_current")->asUint();      // milliampere
    min_current_1p_ma           = charge_manager.config_in_use.get("minimum_current_1p")->asUint();             // milliampere
    min_current_3p_ma           = charge_manager.config_in_use.get("minimum_current")->asUint();                // milliampere

    uint32_t auto_reset_time    = config_in_use.get("auto_reset_time")->asUint();
    auto_reset_hour   = auto_reset_time / 60;
    auto_reset_minute = auto_reset_time % 60;

    mode = default_mode;
    charge_mode.get("mode")->updateUint(mode);

    if (phase_switching_mode == PHASE_SWITCHING_EXTERNAL_CONTROL)
        state.get("external_control")->updateUint(EXTERNAL_CONTROL_STATE_UNAVAILABLE);

    // Set up meter power filter.
    uint32_t power_mavg_span_s;
    switch (mode) {
        default:
        case CLOUD_FILTER_OFF:    power_mavg_span_s =   0; break;
        case CLOUD_FILTER_LIGHT:  power_mavg_span_s = 120; break;
        case CLOUD_FILTER_MEDIUM: power_mavg_span_s = 240; break;
        case CLOUD_FILTER_STRONG: power_mavg_span_s = 480; break;
    }
    if (power_mavg_span_s <= 0) {
        power_at_meter_mavg_values_count = 1;
    } else {
        power_at_meter_mavg_values_count = static_cast<int32_t>(power_mavg_span_s * 1000 / EM_TASK_DELAY_MS);
    }
    power_at_meter_mavg_values_w = static_cast<int32_t*>(malloc_psram(static_cast<size_t>(power_at_meter_mavg_values_count) * sizeof(power_at_meter_mavg_values_w[0])));

    // Bricklet and meter access, requires power filter to be set up
    update_all_data();

    // Set up output relay and input pins
    output = new OutputRelay(config_in_use);
    input3 = new InputPin(3, 0, config_in_use, all_data.input[0]);
    input4 = new InputPin(4, 1, config_in_use, all_data.input[1]);

    // If the user accepts the additional wear, the minimum hysteresis time is 10s. Less than that will cause the control algorithm to oscillate.
    uint32_t hysteresis_min_ms = 10 * 1000;  // milliseconds
    if (switching_hysteresis_ms < hysteresis_min_ms)
        switching_hysteresis_ms = hysteresis_min_ms;

    // Pre-calculate various limits
    int32_t min_phases;
    if (phase_switching_mode == PHASE_SWITCHING_ALWAYS_1PHASE) {
        min_phases = 1;
    } else if (phase_switching_mode == PHASE_SWITCHING_ALWAYS_3PHASE) {
        min_phases = 3;
    } else { // automatic, external or PV1P/FAST3P
        min_phases = 1;
    }
    if (min_phases < 3) {
        overall_min_power_w = static_cast<int32_t>(230 * 1 * min_current_1p_ma / 1000);
    } else {
        overall_min_power_w = static_cast<int32_t>(230 * 3 * min_current_3p_ma / 1000);
    }

    const int32_t max_1phase_w = static_cast<int32_t>(230 * 1 * max_current_unlimited_ma / 1000);
    const int32_t min_3phase_w = static_cast<int32_t>(230 * 3 * min_current_3p_ma / 1000);

    if (min_3phase_w > max_1phase_w) { // have dead current range
        int32_t range_width = min_3phase_w - max_1phase_w;
        threshold_3to1_w = max_1phase_w + static_cast<int32_t>(0.25 * range_width);
        threshold_1to3_w = max_1phase_w + static_cast<int32_t>(0.75 * range_width);
    } else { // no dead current range, use simple limits
        threshold_3to1_w = min_3phase_w;
        threshold_1to3_w = max_1phase_w;
    }

    low_level_state.get("overall_min_power")->updateInt(overall_min_power_w);
    low_level_state.get("threshold_3to1")->updateInt(threshold_3to1_w);
    low_level_state.get("threshold_1to3")->updateInt(threshold_1to3_w);

    // Initialize contactor check state so that the check doesn't trip immediately if the first response from the bricklet is invalid.
    all_data.contactor_check_state = 1;

    // Check for incomplete configuration after as much as possible has been set up.
    // The default configuration after a factory reset must be good enough for everything to run without crashing.
    if ((config_in_use.get("phase_switching_mode")->asUint() == PHASE_SWITCHING_AUTOMATIC) && !config_in_use.get("contactor_installed")->asBool()) {
        logger.printfln("energy_manager: Invalid configuration: Automatic phase switching selected but no contactor installed.");
        set_config_error(CONFIG_ERROR_FLAGS_PHASE_SWITCHING_MASK);
        return;
    }

    task_scheduler.scheduleWithFixedDelay([this](){
        this->update_all_data();
    }, 0, EM_TASK_DELAY_MS);

    task_scheduler.scheduleWithFixedDelay([this](){
        this->update_io();
    }, EM_TASK_DELAY_MS, EM_TASK_DELAY_MS);

    start_network_check_task();

    // Tell CM how many phases are available. is_3phase is updated in the previous call to update_all_data().
    // set_available_phases() uses callCommand(), which is not available during setup phase, so schedule a task for it.
    task_scheduler.scheduleOnce([this](){
        set_available_phases(is_3phase ? 3 : 1);
    }, 0);

    // Can't check for chargers in setup() because CM's setup() hasn't run yet to load the charger configuration.
    task_scheduler.scheduleOnce([this](){
        if (!charge_manager.have_chargers()) {
            logger.printfln("energy_manager: No chargers configured. Won't try to distribute energy.");
            set_config_error(CONFIG_ERROR_FLAGS_NO_CHARGERS_MASK);
        }
    }, 0);

    if (max_current_unlimited_ma == 0) {
        logger.printfln("energy_manager: No maximum current configured for chargers. Disabling energy distribution.");
        set_config_error(CONFIG_ERROR_FLAGS_NO_MAX_CURRENT_MASK);
        return;
    }

    task_scheduler.scheduleWithFixedDelay([this](){
        this->update_energy();
    }, EM_TASK_DELAY_MS, EM_TASK_DELAY_MS);

    task_scheduler.scheduleOnce([this](){
        uptime_past_hysteresis = true;
        low_level_state.get("uptime_past_hysteresis")->updateBool(uptime_past_hysteresis);
    }, switching_hysteresis_ms);

    if (config_in_use.get("auto_reset_mode")->asBool())
        start_auto_reset_task();

    task_scheduler.scheduleOnce([this](){
        if (excess_charging_enable && em_meter_config.config_in_use.get("meter_source")->asUint() == 0) {
            set_error(ERROR_FLAGS_BAD_CONFIG_MASK);
            logger.printfln("energy_manager: Excess charging enabled but no meter configured.");
        }
    }, 0);

    task_scheduler.scheduleWithFixedDelay([this](){collect_data_points();}, 10000, 10000);
    task_scheduler.scheduleWithFixedDelay([this](){set_pending_data_points();}, 10000, 100);
}

void EnergyManager::register_urls()
{
    // Always export state so that the status page can show an error when no bricklet was found.
    api.addState("energy_manager/state", &state, {}, 1000);

    server.on("/energy_manager/start_debug", HTTP_GET, [this](WebServerRequest request) {
        last_debug_keep_alive = millis();
        check_debug();
        ws.pushRawStateUpdate(this->get_energy_manager_debug_header(), "energy_manager/debug_header");
        debug = true;
        return request.send(200);
    });

    server.on("/energy_manager/continue_debug", HTTP_GET, [this](WebServerRequest request) {
        last_debug_keep_alive = millis();
        return request.send(200);
    });

    server.on("/energy_manager/stop_debug", HTTP_GET, [this](WebServerRequest request){
        debug = false;
        return request.send(200);
    });

    api.addPersistentConfig("energy_manager/config", &config, {}, 1000);
#if MODULE_DEBUG_AVAILABLE()
    api.addPersistentConfig("energy_manager/debug_config", &debug_config, {}, 1000);
#endif
    api.addState("energy_manager/low_level_state", &low_level_state, {}, 1000);
    api.addState("energy_manager/meter_state", &meter_state, {}, 1000);

    api.addState("energy_manager/charge_mode", &charge_mode, {}, 1000);
    api.addCommand("energy_manager/charge_mode_update", &charge_mode_update, {}, [this](){
        uint32_t new_mode = charge_mode_update.get("mode")->asUint();

        if (new_mode == MODE_DO_NOTHING)
            return;

        auto runtime_mode = charge_mode.get("mode");
        uint32_t old_mode = runtime_mode->asUint();
        runtime_mode->updateUint(new_mode);
        mode = new_mode;

        if (new_mode != old_mode)
            just_switched_mode = true;

        logger.printfln("energy_manager: Switched mode %u->%u", old_mode, mode);
    }, false);

    api.addState("energy_manager/external_control", &external_control, {}, 1000);
    api.addCommand("energy_manager/external_control_update", &external_control_update, {}, [this](){
        uint32_t external_control_state = state.get("external_control")->asUint();
        switch (external_control_state) {
            case EXTERNAL_CONTROL_STATE_DISABLED:
                logger.printfln("energy_manager: Ignoring external control phase change request: External control is not enabled.");
                return;
            case EXTERNAL_CONTROL_STATE_UNAVAILABLE:
                logger.printfln("energy_manager: Ignoring external control phase change request: Phase switching is currently unavailable.");
                return;
            case EXTERNAL_CONTROL_STATE_SWITCHING:
                logger.printfln("energy_manager: Ignoring external control phase change request: Phase switching in progress.");
                return;
            default:
                break; // All good, proceed.
        }

        auto phases_wanted = external_control.get("phases_wanted");
        uint32_t old_phases = phases_wanted->asUint();
        uint32_t new_phases = external_control_update.get("phases_wanted")->asUint();

        if (new_phases == old_phases) {
            logger.printfln("energy_manager: Ignoring external control phase change request: Value is already %u.", new_phases);
            return;
        }

        if (new_phases == 2 || new_phases > 3) {
            logger.printfln("energy_manager: Ignoring external control phase change request: Value %u is invalid.", new_phases);
            return;
        }

        logger.printfln("energy_manager: External control phase change request: switching from %u to %u", old_phases, new_phases);
        phases_wanted->updateUint(new_phases);
    }, true);

    api.addResponse("energy_manager/history_wallbox_5min", &history_wallbox_5min, {}, [this](IChunkedResponse *response, Ownership *ownership, uint32_t owner_id){history_wallbox_5min_response(response, ownership, owner_id);});
    api.addResponse("energy_manager/history_wallbox_daily", &history_wallbox_daily, {}, [this](IChunkedResponse *response, Ownership *ownership, uint32_t owner_id){history_wallbox_daily_response(response, ownership, owner_id);});
    api.addResponse("energy_manager/history_energy_manager_5min", &history_energy_manager_5min, {}, [this](IChunkedResponse *response, Ownership *ownership, uint32_t owner_id){history_energy_manager_5min_response(response, ownership, owner_id);});
    api.addResponse("energy_manager/history_energy_manager_daily", &history_energy_manager_daily, {}, [this](IChunkedResponse *response, Ownership *ownership, uint32_t owner_id){history_energy_manager_daily_response(response, ownership, owner_id);});

    this->DeviceModule::register_urls();
}

void EnergyManager::loop()
{
    this->DeviceModule::loop();

    static uint32_t last_debug = 0;
    if (debug && deadline_elapsed(last_debug + 50)) {
        last_debug = millis();
        ws.pushRawStateUpdate(this->get_energy_manager_debug_line(), "energy_manager/debug");
    }
}

void EnergyManager::update_all_data()
{
    update_all_data_struct();

    low_level_state.get("contactor")->updateBool(all_data.contactor_value);
    low_level_state.get("led_rgb")->get(0)->updateUint(all_data.rgb_value_r);
    low_level_state.get("led_rgb")->get(1)->updateUint(all_data.rgb_value_g);
    low_level_state.get("led_rgb")->get(2)->updateUint(all_data.rgb_value_b);
    state.get("input3_state")->updateBool(all_data.input[0]);
    state.get("input4_state")->updateBool(all_data.input[1]);
    state.get("relay_state")->updateBool(all_data.relay);
    low_level_state.get("input_voltage")->updateUint(all_data.voltage);
    low_level_state.get("contactor_check_state")->updateUint(all_data.contactor_check_state);
    low_level_state.get("uptime")->updateUint(all_data.uptime);

    if (all_data.energy_meter_type != METER_TYPE_NONE) {
        meter_state.get("energy_meter_type")->updateUint(all_data.energy_meter_type);
        meter_state.get("energy_meter_power")->updateFloat(all_data.power);
        meter_state.get("energy_meter_energy_import")->updateFloat(all_data.energy_import);
        meter_state.get("energy_meter_energy_export")->updateFloat(all_data.energy_export);
    }

    // Update states derived from all_data
    is_3phase   = contactor_installed ? all_data.contactor_value : phase_switching_mode == PHASE_SWITCHING_ALWAYS_3PHASE;
    have_phases = 1 + static_cast<uint32_t>(is_3phase) * 2;
    low_level_state.get("is_3phase")->updateBool(is_3phase);
    state.get("phases_switched")->updateUint(have_phases);

    power_at_meter_raw_w = all_data.energy_meter_type ? all_data.power : meter.values.get("power")->asFloat(); // watt

    if (!isnan(power_at_meter_raw_w)) {
        int32_t raw_power_w = static_cast<int32_t>(power_at_meter_raw_w);

#if MODULE_EM_PV_FAKER_AVAILABLE()
        // PV faker must influence meter value before doing anything with it.
        raw_power_w -= em_pv_faker.state.get("fake_power")->asInt(); // watt
#endif

        low_level_state.get("power_at_meter")->updateFloat(static_cast<float>(raw_power_w)); //TODO Maybe keep as float until here?

        // Filtered/smoothed values must not be modified anywhere else.

        // Check if smooth values need to be initialized.
        if (power_at_meter_smooth_w == INT32_MAX) {
            for (int32_t i = 0; i < CURRENT_POWER_SMOOTHING_SAMPLES; i++) {
                power_at_meter_smooth_values_w[i] = raw_power_w;
            }
            power_at_meter_smooth_total = raw_power_w * CURRENT_POWER_SMOOTHING_SAMPLES;
        } else {
            power_at_meter_smooth_total = power_at_meter_smooth_total - power_at_meter_smooth_values_w[power_at_meter_smooth_position] + raw_power_w;
            power_at_meter_smooth_values_w[power_at_meter_smooth_position] = raw_power_w;
            power_at_meter_smooth_position++;
            if (power_at_meter_smooth_position >= CURRENT_POWER_SMOOTHING_SAMPLES)
                power_at_meter_smooth_position = 0;
        }

        // Signed division requires both numbers to be signed.
        static_assert(std::is_same<int32_t, decltype(power_at_meter_smooth_total)>::value, "power_at_meter_smooth_total must be signed");
        power_at_meter_smooth_w = power_at_meter_smooth_total / CURRENT_POWER_SMOOTHING_SAMPLES;

        // Check if filter values need to be initialized.
        if (power_at_meter_filtered_w == INT32_MAX) {
            for (int32_t i = 0; i < power_at_meter_mavg_values_count; i++) {
                power_at_meter_mavg_values_w[i] = raw_power_w;
            }
            power_at_meter_mavg_total = raw_power_w * power_at_meter_mavg_values_count;
        } else {
            power_at_meter_mavg_total = power_at_meter_mavg_total - power_at_meter_mavg_values_w[power_at_meter_mavg_position] + raw_power_w;
            power_at_meter_mavg_values_w[power_at_meter_mavg_position] = raw_power_w;
            power_at_meter_mavg_position++;
            if (power_at_meter_mavg_position >= power_at_meter_mavg_values_count)
                power_at_meter_mavg_position = 0;
        }

        // Signed division requires both numbers to be signed.
        static_assert(std::is_same<int32_t, decltype(power_at_meter_mavg_total       )>::value, "power_at_meter_mavg_total must be signed");
        static_assert(std::is_same<int32_t, decltype(power_at_meter_mavg_values_count)>::value, "power_at_meter_mavg_values_count must be signed");
        power_at_meter_filtered_w = power_at_meter_mavg_total / power_at_meter_mavg_values_count;

        low_level_state.get("power_at_meter_filtered")->updateFloat(static_cast<float>(power_at_meter_filtered_w));
    }

    if (contactor_installed) {
        if ((all_data.contactor_check_state & 1) == 0) {
            logger.printfln("Contactor check tripped. Check contactor.");
            contactor_check_tripped = true;
            set_error(ERROR_FLAGS_CONTACTOR_MASK);
        }
    }
}

void EnergyManager::update_all_data_struct()
{
    int rc = tf_warp_energy_manager_get_all_data_1(
        &device,
        &all_data.contactor_value,
        &all_data.rgb_value_r,
        &all_data.rgb_value_g,
        &all_data.rgb_value_b,
        &all_data.power,
        &all_data.energy_import,
        &all_data.energy_export,
        &all_data.energy_meter_type,
        all_data.error_count,
        all_data.input,
        &all_data.relay,
        &all_data.voltage,
        &all_data.contactor_check_state,
        &all_data.uptime
    );

    check_bricklet_reachable(rc, "update_all_data_struct");

    if (rc == TF_E_OK) {
        all_data.last_update = millis();
        all_data.is_valid = true;
    }
}

void EnergyManager::update_status_led()
{
    if (error_flags & ERROR_FLAGS_BAD_CONFIG_MASK)
        rgb_led.set_status(EmRgbLed::Status::BadConfig);
    else if (error_flags & ERROR_FLAGS_ALL_ERRORS_MASK)
        rgb_led.set_status(EmRgbLed::Status::Error);
    else if (error_flags & ERROR_FLAGS_ALL_WARNINGS_MASK)
        rgb_led.set_status(EmRgbLed::Status::Warning);
    else
        rgb_led.set_status(EmRgbLed::Status::OK);
}

void EnergyManager::clr_error(uint32_t error_mask)
{
    error_flags &= ~error_mask;
    state.get("error_flags")->updateUint(error_flags);
    update_status_led();
}

bool EnergyManager::is_error(uint32_t error_bit_pos)
{
    return (error_flags >> error_bit_pos) & 1;
}

void EnergyManager::set_error(uint32_t error_mask)
{
    error_flags |= error_mask;
    state.get("error_flags")->updateUint(error_flags);

    if (device_found)
        update_status_led();
}

void EnergyManager::set_config_error(uint32_t config_error_mask)
{
    config_error_flags |= config_error_mask;
    state.get("config_error_flags")->updateUint(config_error_flags);

    set_error(ERROR_FLAGS_BAD_CONFIG_MASK);
}

void EnergyManager::check_bricklet_reachable(int rc, const char *context) {
    if (rc == TF_E_OK) {
        consecutive_bricklet_errors = 0;
        if (!bricklet_reachable) {
            bricklet_reachable = true;
            clr_error(ERROR_FLAGS_BRICKLET_MASK);
            logger.printfln("energy_manager: Bricklet is reachable again.");
        }
    } else {
        if (rc == TF_E_TIMEOUT) {
            logger.printfln("energy_manager (%s): Bricklet access timed out.", context);
        } else {
            logger.printfln("energy_manager (%s): Bricklet access returned error %d.", context, rc);
        }
        if (bricklet_reachable && ++consecutive_bricklet_errors >= 8) {
            bricklet_reachable = false;
            set_error(ERROR_FLAGS_BRICKLET_MASK);
            logger.printfln("energy_manager (%s): Bricklet is unreachable.", context);
        }
    }
    low_level_state.get("consecutive_bricklet_errors")->updateUint(consecutive_bricklet_errors);
}

void EnergyManager::update_io()
{
    output->update();

    // Oversampling inputs is currently not used because all of the implemented input pin functions require update_energy() to run anyway.
    //// We "over-sample" the two inputs compared to the other data in the all_data struct
    //// to make sure that we can always react in a timely manner to input changes
    //int rc = tf_warp_energy_manager_get_input(&device, all_data.input);
    //if (rc != TF_E_OK) {
    //    logger.printfln("get_input error %d", rc);
    //}

    // Restore values that can be changed by input pins.
    max_current_limited_ma      = max_current_unlimited_ma;

    input3->update(all_data.input[0]);
    input4->update(all_data.input[1]);
}

void EnergyManager::start_network_check_task()
{
    task_scheduler.scheduleWithFixedDelay([this](){
        bool disconnected;
        do {
#if MODULE_ETHERNET_AVAILABLE()
            if (ethernet.get_connection_state() == EthernetState::CONNECTED) {
                disconnected = false;
                break;
            }
#endif
#if MODULE_WIFI_AVAILABLE()
            if (wifi.get_connection_state() == WifiState::CONNECTED) {
                disconnected = false;
                break;
            }
#endif
#if MODULE_ETHERNET_AVAILABLE()
            if (ethernet.is_enabled()) {
                disconnected = true;
                break;
            }
#endif
#if MODULE_WIFI_AVAILABLE()
            if (wifi.is_sta_enabled()) {
                disconnected = true;
                break;
            }
#endif
            disconnected = false;
        } while (0);

        if (disconnected) {
            set_error(ERROR_FLAGS_NETWORK_MASK);
        } else {
            if (is_error(ERROR_FLAGS_NETWORK_BIT_POS))
                clr_error(ERROR_FLAGS_NETWORK_MASK);
        }
    }, 0, 5000);
}

void EnergyManager::start_auto_reset_task()
{
#if MODULE_NTP_AVAILABLE()
    task_scheduler.scheduleOnce([this](){
        if (ntp.state.get("synced")->asBool())
            schedule_auto_reset_task();
        else
            start_auto_reset_task();
    }, 30 * 1000);
#endif
}

void EnergyManager::schedule_auto_reset_task()
{
    time_t delay_ms = ms_until_time(static_cast<int>(auto_reset_hour), static_cast<int>(auto_reset_minute));
    if (delay_ms < 0) {
        logger.printfln("energy_manager: Auto reset task delay negative: %li", delay_ms);
        return;
    }
    task_scheduler.scheduleOnce([this](){
        switch_mode(default_mode);
        schedule_auto_reset_task();
    }, static_cast<uint32_t>(delay_ms));
}

void EnergyManager::limit_max_current(uint32_t limit_ma)
{
    if (max_current_limited_ma > limit_ma)
        max_current_limited_ma = limit_ma;
}

void EnergyManager::switch_mode(uint32_t new_mode)
{
    api.callCommand("energy_manager/charge_mode_update", Config::ConfUpdateObject{{
        {"mode", new_mode}
    }});
}

void EnergyManager::set_available_current(uint32_t current)
{
    is_on_last = current > 0;

    String err = api.callCommand("charge_manager/available_current_update", Config::ConfUpdateObject{{
        {"current", current},
    }});

    if (!err.isEmpty())
        logger.printfln("energy_manager: set_available_current failed: %s", err.c_str());

    charge_manager_available_current_ma = current;
    low_level_state.get("charge_manager_available_current")->updateUint(current);
}

void EnergyManager::set_available_phases(uint32_t phases)
{
    String err = api.callCommand("charge_manager/available_phases_update", Config::ConfUpdateObject{{
        {"phases", phases},
    }});

    if (!err.isEmpty())
        logger.printfln("energy_manager: set_available_phases failed: %s", err.c_str());
}

void EnergyManager::update_energy()
{
    static SwitchingState prev_state = switching_state;
    if (switching_state != prev_state) {
        logger.printfln("energy_manager: now in state %i", static_cast<int>(switching_state));
        prev_state = switching_state;
        low_level_state.get("switching_state")->updateUint(static_cast<uint32_t>(switching_state));
    }

    if (!bricklet_reachable) {
        set_available_current(0);

        if (phase_switching_mode == PHASE_SWITCHING_EXTERNAL_CONTROL)
            state.get("external_control")->updateUint(EXTERNAL_CONTROL_STATE_UNAVAILABLE);

        return;
    }

    if (switching_state == SwitchingState::Monitoring) {
        if (contactor_check_tripped) {
            set_available_current(0);

            // The contactor check only detects a contactor defect when the contactor should be on.
            // Switch contactor off when a defect is detected, to make sure that it's not energized.
            if (all_data.contactor_value) {
                logger.printfln("energy_manager: Switching off possibly defective contactor.");
                wants_3phase = false;
                switching_state = SwitchingState::Stopping;
                switching_start = millis();
            }

            if (phase_switching_mode == PHASE_SWITCHING_EXTERNAL_CONTROL)
                state.get("external_control")->updateUint(EXTERNAL_CONTROL_STATE_UNAVAILABLE);

            return;
        }

        const bool     is_on = is_on_last;
        const uint32_t charge_manager_allocated_power_w = 230 * have_phases * charge_manager_allocated_current_ma / 1000; // watt

        low_level_state.get("charge_manager_allocated_current")->updateUint(charge_manager_allocated_current_ma);
        low_level_state.get("max_current_limited")->updateUint(max_current_limited_ma);
        low_level_state.get("charging_blocked")->updateUint(charging_blocked.combined);

        if (charging_blocked.combined) {
            if (is_on) {
                phase_state_change_blocked_until = on_state_change_blocked_until = millis() + switching_hysteresis_ms;
            }
            set_available_current(0);
            just_switched_phases = false;

            if (phase_switching_mode == PHASE_SWITCHING_EXTERNAL_CONTROL)
                state.get("external_control")->updateUint(EXTERNAL_CONTROL_STATE_UNAVAILABLE);

            return;
        }

        int32_t p_error_w, p_error_filtered_w;
        if (!excess_charging_enable) {
            p_error_w          = 0;
            p_error_filtered_w = 0;
        } else {
            if (power_at_meter_smooth_w == INT32_MAX) {
                if (!printed_skipping_energy_update) {
                    logger.printfln("energy_manager: Pausing energy updates because power value is not available yet.");
                    printed_skipping_energy_update = true;
                }
                return;
            } else {
                if (printed_skipping_energy_update) {
                    logger.printfln("energy_manager: Resuming energy updates because power value is now available.");
                    printed_skipping_energy_update = false;
                }
            }
            p_error_w          = target_power_from_grid_w - power_at_meter_smooth_w;
            p_error_filtered_w = target_power_from_grid_w - power_at_meter_filtered_w;

            if (p_error_w > 200)
                rgb_led.update_grid_balance(EmRgbLed::GridBalance::Export);
            else if (p_error_w < -200)
                rgb_led.update_grid_balance(EmRgbLed::GridBalance::Import);
            else
                rgb_led.update_grid_balance(EmRgbLed::GridBalance::Balanced);
        }

        switch (mode) {
            case MODE_FAST:
                power_available_w          = static_cast<int32_t>(230 * 3 * max_current_limited_ma / 1000);
                power_available_filtered_w = power_available_w;
                break;
            case MODE_OFF:
            default:
                power_available_w          = 0;
                power_available_filtered_w = 0;
                break;
            case MODE_PV:
            case MODE_MIN_PV:
                // Excess charging enabled; use a simple P controller to adjust available power.
                int32_t p_adjust_w;
                int32_t p_adjust_filtered_w;
                if (!is_on) {
                    // When the power is not on, use p=1 so that the switch-on threshold can be reached properly.
                    p_adjust_w          = p_error_w;
                    p_adjust_filtered_w = p_error_filtered_w;
                } else {
                    // Some EVs may only be able to adjust their charge power in steps of 1500W,
                    // so smaller factors are required for smaller errors.
                    int32_t p_error_abs_w = abs(p_error_w);
                    if (p_error_abs_w < 1000) {
                        // Use p=0.5 for small differences so that the controller can converge without oscillating too much.
                        p_adjust_w          = p_error_w          / 2;
                        p_adjust_filtered_w = p_error_filtered_w / 2;
                    } else if (p_error_abs_w < 1500) {
                        // Use p=0.75 for medium differences so that the controller can converge reasonably fast while still avoiding too many oscillations.
                        p_adjust_w          = p_error_w          * 3 / 4;
                        p_adjust_filtered_w = p_error_filtered_w * 3 / 4;
                    } else {
                        // Use p=0.875 for large differences so that the controller can converge faster.
                        p_adjust_w          = p_error_w          * 7 / 8;
                        p_adjust_filtered_w = p_error_filtered_w * 7 / 8;
                    }
                }

                power_available_w          = static_cast<int32_t>(charge_manager_allocated_power_w) + p_adjust_w;
                power_available_filtered_w = static_cast<int32_t>(charge_manager_allocated_power_w) + p_adjust_filtered_w;

                if (mode != MODE_MIN_PV)
                    break;

                // Check against guaranteed power only in MIN_PV mode.
                if (power_available_w          < static_cast<int32_t>(guaranteed_power_w))
                    power_available_w          = static_cast<int32_t>(guaranteed_power_w);
                if (power_available_filtered_w < static_cast<int32_t>(guaranteed_power_w))
                    power_available_filtered_w = static_cast<int32_t>(guaranteed_power_w);

                break;
        }

        if (phase_switching_mode == PHASE_SWITCHING_EXTERNAL_CONTROL && external_control.get("phases_wanted")->asUint() == 0) {
            power_available_w          = 0;
            power_available_filtered_w = 0;
        }

        // CP disconnect support unknown if some chargers haven't replied yet.
        if (!charge_manager.seen_all_chargers()) {
            // Don't constantly complain if we don't have any chargers configured.
            if (charge_manager.have_chargers()) {
                if (!printed_not_seen_all_chargers) {
                    logger.printfln("energy_manager: Not seen all chargers yet.");
                    printed_not_seen_all_chargers = true;
                }
            }

            if (phase_switching_mode == PHASE_SWITCHING_EXTERNAL_CONTROL)
                state.get("external_control")->updateUint(EXTERNAL_CONTROL_STATE_UNAVAILABLE);

            return;
        } else if (!printed_seen_all_chargers) {
            logger.printfln("energy_manager: Seen all chargers.");
            printed_seen_all_chargers = true;
        }

        // Check how many phases are wanted.
        if (phase_switching_mode == PHASE_SWITCHING_ALWAYS_1PHASE) {
            wants_3phase = false;
        } else if (phase_switching_mode == PHASE_SWITCHING_ALWAYS_3PHASE) {
            wants_3phase = true;
        } else if (phase_switching_mode == PHASE_SWITCHING_EXTERNAL_CONTROL) {
            wants_3phase = external_control.get("phases_wanted")->asUint() == 3;
        } else if (phase_switching_mode == PHASE_SWITCHING_PV1P_FAST3P) {
            wants_3phase = mode == MODE_FAST;
        } else { // automatic
            if (is_3phase) {
                wants_3phase = power_available_filtered_w >= threshold_3to1_w;
            } else { // is 1phase
                wants_3phase = power_available_filtered_w > threshold_1to3_w;
            }
        }

        // Need to get the time here instead of using deadline_elapsed(), to avoid stopping the charge when the phase switch deadline check fails but the start/stop deadline check succeeds.
        uint32_t time_now = millis();

        low_level_state.get("power_available")->updateInt(power_available_w);
        low_level_state.get("power_available_filtered")->updateInt(power_available_filtered_w);
        low_level_state.get("wants_3phase")->updateBool(wants_3phase);
        low_level_state.get("wants_3phase_last")->updateBool(wants_3phase_last);
        low_level_state.get("is_on_last")->updateBool(is_on_last);
        low_level_state.get("wants_on_last")->updateBool(wants_on_last);

        // Remember last decision change to start hysteresis time.
        if (wants_3phase != wants_3phase_last) {
            logger.printfln("energy_manager: wants_3phase decision changed to %i", wants_3phase);
            phase_state_change_blocked_until = time_now + switching_hysteresis_ms;
            wants_3phase_last = wants_3phase;
        }

        bool phase_state_change_is_blocked = a_after_b(phase_state_change_blocked_until, time_now);
        bool on_state_change_is_blocked = a_after_b(on_state_change_blocked_until, time_now);
        low_level_state.get("phase_state_change_blocked")->updateBool(phase_state_change_is_blocked);
        low_level_state.get("phase_state_change_delay")->updateUint(phase_state_change_is_blocked ? phase_state_change_blocked_until - time_now : 0);
        low_level_state.get("on_state_change_blocked")->updateBool(on_state_change_is_blocked);
        low_level_state.get("on_state_change_delay")->updateUint(on_state_change_is_blocked ? on_state_change_blocked_until - time_now : 0);

        // Check if phase switching is allowed right now.
        bool switch_phases = false;
        if (wants_3phase != is_3phase) {
            if (!contactor_installed) {
                logger.printfln("energy_manager: Phase switch wanted but no contactor installed. Check configuration.");
            } else if (!charge_manager.is_control_pilot_disconnect_supported(time_now - 5000)) {
                logger.printfln("energy_manager: Phase switch wanted but not supported by all chargers.");
            } else if (phase_switching_mode == PHASE_SWITCHING_EXTERNAL_CONTROL) {
                // Switching phases is always allowed when under external control.
                switch_phases = true;
            } else if (!uptime_past_hysteresis) {
                // (Re)booted recently. Allow immediate switching.
                logger.printfln("energy_manager: Immediate phase switch to %s during start-up period. available (filtered)=%i", wants_3phase ? "3 phases" : "1 phase", power_available_filtered_w);
                switch_phases = true;
                // Only one immediate switch on/off allowed; mark as used.
                uptime_past_hysteresis = true;
                low_level_state.get("uptime_past_hysteresis")->updateBool(uptime_past_hysteresis);
            } else if (just_switched_mode) {
                // Just switched modes. Allow immediate switching.
                logger.printfln("energy_manager: Immediate phase switch to %s after changing modes. available (filtered)=%i", wants_3phase ? "3 phases" : "1 phase", power_available_filtered_w);
                switch_phases = true;
            } else if (!is_on && !on_state_change_is_blocked && a_after_b(time_now, phase_state_change_blocked_until - switching_hysteresis_ms/2)) {
                // On/off deadline passed and at least half of the phase switching deadline passed.
                logger.printfln("energy_manager: Immediate phase switch to %s while power is off. available (filtered)=%i", wants_3phase ? "3 phases" : "1 phase", power_available_filtered_w);
                switch_phases = true;
            } else if (phase_state_change_is_blocked) {
                //logger.printfln("energy_manager: Phase switch wanted but decision changed too recently. Have to wait another %ums.", phase_state_change_blocked_until - time_now);
            } else {
                logger.printfln("energy_manager wants phase change to %s: available (filtered)=%i", wants_3phase ? "3 phases" : "1 phase", power_available_filtered_w);
                switch_phases = true;
            }
        }

        if (phase_switching_mode == PHASE_SWITCHING_EXTERNAL_CONTROL) {
            if (charge_manager.is_control_pilot_disconnect_supported(time_now - 5000)) {
                state.get("external_control")->updateUint(EXTERNAL_CONTROL_STATE_AVAILABLE);
            } else {
                state.get("external_control")->updateUint(EXTERNAL_CONTROL_STATE_UNAVAILABLE);
            }
        }

        // Switch phases or deal with what's available.
        if (switch_phases) {
            set_available_current(0);
            set_available_phases(wants_3phase ? 3 : 1);
            switching_state = SwitchingState::Stopping;
            switching_start = time_now;
        } else {
            // Check against overall minimum power, to avoid wanting to switch off when available power is below 3-phase minimum but switch to 1-phase is possible.
            bool wants_on = power_available_filtered_w >= overall_min_power_w;

            // Remember last decision change to start hysteresis time.
            if (wants_on != wants_on_last) {
                logger.printfln("energy_manager: wants_on decision changed to %i", wants_on);
                on_state_change_blocked_until = time_now + switching_hysteresis_ms;
                on_state_change_is_blocked = true; // Set manually because the usual update already ran before the phase switching code.
                wants_on_last = wants_on;
            }

            // Filtered power can be above the threshold while current power is below it.
            // In that case, don't switch yet but also don't change wants_on_last state.
            // Instead, wait for the current power to raise above threshold while wants_on(_last) is still true.
            // The inverse applies to the switch-off period.
            if (is_on) {
                // Power is on. Stay on if currently available power is above threshold, even if filtered power might be below it.
                // Requires both filtered and current available power to be below the minimum limit to switch off.
                if (power_available_w >= overall_min_power_w)
                    wants_on = true;
            } else {
                // Power is off. Stay off if currently available power is below threshold, even if filtered power might be below it.
                // Requires both filtered and current available power to be above the minimum limit to switch on.
                if (power_available_w < overall_min_power_w)
                    wants_on = false;
            }

            uint32_t min_current_now_ma = is_3phase ? min_current_3p_ma : min_current_1p_ma;

            uint32_t current_available_ma;
            if (!wants_on) {
                current_available_ma = 0;
            } else if (power_available_w <= 0) {
                current_available_ma = 0;
            } else {
                current_available_ma = (static_cast<uint32_t>(power_available_w) * 1000) / (230 * have_phases);
            }

            // Check if switching on/off is allowed right now.
            if (wants_on != is_on) {
                if (phase_switching_mode == PHASE_SWITCHING_EXTERNAL_CONTROL) {
                    // Switching on/off is always allowed when under external control.
                } else if (!on_state_change_is_blocked) {
                    // Start/stop allowed
                    logger.printfln("energy_manager: Switch %s, power available: %i, current available: %u", wants_on ? "on" : "off", power_available_w, current_available_ma);
                } else if (!uptime_past_hysteresis) {
                    // (Re)booted recently. Allow immediate switching.
                    logger.printfln("energy_manager: Immediate switch-%s during start-up period, power available: %i, current available: %u", wants_on ? "on" : "off", power_available_w, current_available_ma);
                    // Only one immediate switch on/off allowed; mark as used.
                    uptime_past_hysteresis = true;
                    low_level_state.get("uptime_past_hysteresis")->updateBool(uptime_past_hysteresis);
                } else if (just_switched_mode) {
                    // Just switched modes. Allow immediate switching.
                    logger.printfln("energy_manager: Immediate switch-%s after changing modes, power available: %i, current available: %u", wants_on ? "on" : "off", power_available_w, current_available_ma);
                } else if (just_switched_phases && a_after_b(time_now, on_state_change_blocked_until - switching_hysteresis_ms/2)) {
                    logger.printfln("energy_manager: Opportunistic switch-%s, power available: %i, current available: %u", wants_on ? "on" : "off", power_available_w, current_available_ma);
                } else { // Switched too recently
                    //logger.printfln("energy_manager: Start/stop wanted but decision changed too recently. Have to wait another %ums.", off_state_change_blocked_until - time_now);
                    if (is_on) { // Is on, needs to stay on at minimum current.
                        current_available_ma = min_current_now_ma;
                    } else { // Is off, needs to stay off.
                        current_available_ma = 0;
                    }
                }
            } else { // Don't want to change.
                if (is_on) {
                    // Power is on and wants on too, need to ensure minimum current because unfiltered power available can be negative.
                    if (current_available_ma < min_current_now_ma) {
                        current_available_ma = min_current_now_ma;
                    }
                }
            }

            // Apply minimum/maximum current limits.
            if (current_available_ma < min_current_now_ma) {
                if (current_available_ma != 0)
                    current_available_ma = min_current_now_ma;
            } else if (current_available_ma > max_current_limited_ma) {
                current_available_ma = max_current_limited_ma;
            }

            set_available_current(current_available_ma);
            just_switched_phases = false;
            just_switched_mode = false;
        }
    } else if (switching_state == SwitchingState::Stopping) {
        set_available_current(0);

        if (charge_manager.is_charging_stopped(switching_start)) {
            switching_state = SwitchingState::DisconnectingCP;
            switching_start = millis();
        }
    } else if (switching_state == SwitchingState::DisconnectingCP) {
        charge_manager.set_all_control_pilot_disconnect(true);

        if (charge_manager.are_all_control_pilot_disconnected(switching_start)) {
            switching_state = SwitchingState::TogglingContactor;
            switching_start = millis();
        }
    } else if (switching_state == SwitchingState::TogglingContactor) {
        tf_warp_energy_manager_set_contactor(&device, wants_3phase);

        if (all_data.contactor_value == wants_3phase) {
            switching_state = SwitchingState::ConnectingCP;
            switching_start = millis();
        }
    } else if (switching_state == SwitchingState::ConnectingCP) {
        charge_manager.set_all_control_pilot_disconnect(false);

        switching_state = SwitchingState::Monitoring;
        switching_start = 0;

        just_switched_phases = true;
    }

    if (phase_switching_mode == PHASE_SWITCHING_EXTERNAL_CONTROL && switching_state != SwitchingState::Monitoring)
        state.get("external_control")->updateUint(EXTERNAL_CONTROL_STATE_SWITCHING);
}

bool EnergyManager::get_sdcard_info(struct sdcard_info *data)
{
    int rc = tf_warp_energy_manager_get_sd_information(
        &device,
        &data->sd_status,
        &data->lfs_status,
        &data->sector_size,
        &data->sector_count,
        &data->card_type,
        &data->product_rev,
        data->product_name,
        &data->manufacturer_id
    );

    // Product name retrieved from the SD card is an unterminated 5-character string, so we have to terminate it here.
    data->product_name[sizeof(data->product_name) - 1] = 0;

    check_bricklet_reachable(rc, "get_sdcard_info");

    if (rc != TF_E_OK) {
        set_error(ERROR_FLAGS_SDCARD_MASK);
        logger.printfln("energy_manager: Failed to get SD card information. Error %i", rc);
        return false;
    }

    if (is_error(ERROR_FLAGS_SDCARD_BIT_POS))
        clr_error(ERROR_FLAGS_SDCARD_MASK);

    return true;
}

bool EnergyManager::format_sdcard()
{
    uint8_t ret_format_status;
    int rc = tf_warp_energy_manager_format_sd(&device, 0x4223ABCD, &ret_format_status);

    check_bricklet_reachable(rc, "format_sdcard");

    return rc == TF_E_OK && ret_format_status == TF_WARP_ENERGY_MANAGER_FORMAT_STATUS_OK;
}

uint16_t EnergyManager::get_energy_meter_detailed_values(float *ret_values)
{
    uint16_t len = 0;
    int rc = tf_warp_energy_manager_get_energy_meter_detailed_values(&device, ret_values, &len);

    check_bricklet_reachable(rc, "get_energy_meter_detailed_values");

    return rc == TF_E_OK ? len : 0;
}

void EnergyManager::set_output(bool output_value)
{
    int result = tf_warp_energy_manager_set_output(&device, output_value);

    // Don't check if bricklet is reachable because the setter call won't tell us.

    if (result != TF_E_OK)
        logger.printfln("energy_manager: Failed to set output relay: error %i", result);
}

void EnergyManager::set_rgb_led(uint8_t pattern, uint16_t hue)
{
    int rc = tf_warp_energy_manager_set_led_state(&device, pattern, hue);

    // Don't check if bricklet is reachable because the setter call won't tell us.

    if (rc != TF_E_OK)
        logger.printfln("energy_manager: Failed to set LED state: error %i. Continuing anyway.", rc);
}

void EnergyManager::set_time(const tm &date_time)
{
    uint32_t retries = 3;
    int rc;

    do {
        rc = tf_warp_energy_manager_set_date_time(&device,
                                                  static_cast<uint8_t >(date_time.tm_sec),
                                                  static_cast<uint8_t >(date_time.tm_min),
                                                  static_cast<uint8_t >(date_time.tm_hour),
                                                  static_cast<uint8_t >(date_time.tm_mday - 1),
                                                  static_cast<uint8_t >(date_time.tm_wday),
                                                  static_cast<uint8_t >(date_time.tm_mon),
                                                  static_cast<uint16_t>(date_time.tm_year - 100));
        if (rc == TF_E_OK)
            return;
    } while (retries-- > 0);

    logger.printfln("energy_manager: Failed to set datetime: error %i", rc);
}

struct timeval EnergyManager::get_time()
{
    struct tm date_time;
    struct timeval time;
    time.tv_usec = 0;

    uint8_t tm_sec;
    uint8_t tm_min;
    uint8_t tm_hour;
    uint8_t tm_mday;
    uint8_t tm_wday;
    uint8_t tm_mon;
    uint16_t tm_year;

    uint32_t retries = 1;
    int rc;

    do {
        rc = tf_warp_energy_manager_get_date_time(&device, &tm_sec, &tm_min, &tm_hour, &tm_mday, &tm_wday, &tm_mon, &tm_year);

        check_bricklet_reachable(rc, "get_time");

        if (rc != TF_E_OK)
            continue;

        date_time.tm_sec  = tm_sec;
        date_time.tm_min  = tm_min;
        date_time.tm_hour = tm_hour;
        date_time.tm_mday = tm_mday + 1;
        date_time.tm_wday = tm_wday;
        date_time.tm_mon  = tm_mon;
        date_time.tm_year = tm_year + 100;

        time.tv_sec = timegm(&date_time);

        //FIXME not Y2038-safe
        if (time.tv_sec < static_cast<time_t>(build_timestamp() - 24 * 3600))
            time.tv_sec = 0;

        return time;
    } while (retries-- > 0);

    logger.printfln("energy_manager: Failed to get datetime: error %i", rc);
    time.tv_sec = 0;
    return time;
}

bool EnergyManager::disallow_fw_update_with_vehicle_connected()
{
    return config.get("contactor_installed")->asBool();
}
