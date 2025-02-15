/** @jsxImportSource preact */
import { h } from "preact";
let x = {
    "evse": {
        "status": {
            "evse": "Vehicle state",
            "not_connected": "Disconnected",
            "waiting_for_charge_release": "Waiting for release",
            "ready_to_charge": "Ready",
            "charging": "Charging",
            "error": "Error",
            "configured_charging_current": "Configured charging current",
            "allowed_charging_current": "Allowed charging current",
            "charge_control": "Charge control",
            "start_charging": "Start",
            "stop_charging": "Stop"
        },
        "navbar": {
            "evse": "Charge Status",
            "evse_settings": "Charge Settings"
        },
        "content": {
            "status": "Charge Status",
            "settings": "Charge Settings",
            "iec_state": "IEC 61851 state",
            "iec_state_a": "A (disconnected)",
            "iec_state_b": "B (connected)",
            "iec_state_c": "C (charging)",
            "iec_state_d": "D (not supported)",
            "iec_state_ef": "E/F (error)",
            "contactor_state": "Contactor check",
            "contactor_names": "before contactor, behind contactor, state",
            "contactor_not_live": "Not live",
            "contactor_live": "Live",
            "contactor_ok": "OK",
            "contactor_error": "Error",
            "allowed_charging_current": "Allowed charging current",
            "error_state": "Error state",
            "error_state_desc": <><a href="{{{manual_url}}}">see manual for details</a></>,
            "error_ok": "OK",
            "error_switch": "Switch error",
            "error_contactor": "Contactor error",
            "error_communication": "Communication error",
            "lock_state": "Cable lock",
            "lock_init": "Init",
            "lock_open": "Open",
            "lock_closing": "Closing",
            "lock_close": "Close",
            "lock_opening": "Opening",
            "lock_error": "Error",
            "time_since_state_change": "Time since state change",
            "state_change": "State change",
            "uptime": "Uptime",
            "configuration": "Hardware configuration",
            "has_lock_switch": "Cable lock available",
            "lock_no": "No",
            "lock_yes": "Yes",
            "jumper_config_max_current": "Max current of supply cable",
            "jumper_config": "switch configured",
            "jumper_config_software": "Software",
            "jumper_config_unconfigured": "Unconfigured",
            "evse_version": "Charge controller hardware version",
            "evse_fw_version": "Charge controller firmware version",
            "charging_current": "Charging current limits",
            "charging_current_muted": "minimum of the charging current limits",
            "reset_slot": "Reset",
            "low_level_state": "Low-level state",
            "led_state": "LED state",
            "led_state_off": "Off",
            "led_state_on": "On",
            "led_state_blinking": "Acknowledge blinking",
            "led_state_flickering": "Rejecting blinking",
            "led_state_breathing": "Demanding blinking",
            "led_state_error": /*SFN*/(count: number) => {
                return "Blinking (" + count + " x)";
            }/*NF*/,
            "led_state_api": "API",
            "led_duration": "Duration",
            "cp_pwm_dc": "CP PWM duty cycle",
            "adc_values": "ADC values",
            "voltages": "Voltages",
            "resistances": "Resistances",
            "resistance_names": "CP/PE, PP/PE",
            "gpios": "GPIOs",
            "gpio_low": "Low",
            "gpio_high": "High",
            "debug": "Charge log",
            "debug_start": "Start",
            "debug_stop": "Stop+Download",
            "debug_description": "Create charge log",
            "debug_description_muted": "to diagnose charging problems",
            "active_high": "If open",
            "active_low": "If closed",
            "gpio_state": "State",
            "gpio_out_high": "High impedance",
            "gpio_out_low": "Connected to ground",
            "gpio_out": "General purpose output",
            "gpio_in": "General purpose input",
            "gpio_shutdown": "Shutdown input",
            "button_pressed": "At button press",
            "button_released": "At button release",
            "button_configuration": "Button configuration",

            "auto_start_description": "Manual charge release",
            "auto_start_description_muted": <><a href="https://www.warp-charger.com/evcc.html?v=2">see manual for details</a></>,
            "auto_start_enable": "Requires that charges are always manually released via the web interface, the API or (depending on the button configuration) the button.",

            "external_description": "External control",
            "external_description_muted": <><a href="https://www.warp-charger.com/evcc.html?v=2">see setup tutorial for details</a></>,
            "external_enable": <>Enables an external control system (for example <a href="https://evcc.io/">EVCC</a>) to control this charger</>,

            "boost_mode_desc": "Boost Mode",
            "boost_mode_desc_muted": <><a href="https://www.warp-charger.com/evcc.html?v=2">see manual for details</a></>,
            "boost_mode": "Allows the vehicle's charge controller a slightly higher charge current (+ 0.24 A) to compensate measurement errors of the vehicle. Use only if your vehicle charges with less than the allowed charge current!",

            "reset_description": "Actions",
            "reset_description_muted": "",
            "reset_evse": "Restart",
            "reflash_evse": "Reflash",
            "charging_time": "Charging for",

            "meter_monitoring": "Meter monitoring",
            "meter_monitoring_desc": "Monitors the energy meter and blocks charging if a malfunction is detected.",

            "enable_led_api": "Status-LED control",
            "enable_led_api_desc": "Allows an external source to control the Status-LED.",
            "api_must_be_enabled": "API must be enabled to use this feature.",
            "cron_state_change_trigger": /*FFN*/(state: string) => {
                return (
                  <>
                    If the charge status changes to "<b>{state}</b>",{" "}
                  </>
                );
              }/*NF*/,
              "cron_action_text": /*FFN*/(current: number) => {
                return (
                  <>
                    set the allowed charging current to <b>{current} A</b>.
                  </>
                );
              }/*NF*/,
              "cron_led_action_text": /*FFN*/(state: string, duration: number) => {
                if (state == "An" || state == "Aus") {
                  return <>
                    turn the status-LED <b>{state}</b> for <b>{duration} seconds</b>.
                  </>
                }
                return (
                  <>
                    show <b>{state}</b> for <b>{duration / 1000} seconds</b> on the status-LED.
                  </>
                );
              }/*NF*/,

            "slot_0": "Supply cable",
            "slot_1": "Type 2 charging cable",
            "slot_2": "Shutdown input",
            "slot_3": "Configurable input",
            "slot_4": "Manual charge release",
            "slot_5": "Configuration",
            "slot_6": "User/NFC",
            "slot_7": "Charge manager",
            "slot_8": "External control",
            "slot_9": "Modbus TCP current",
            "slot_10": "Modbus TCP clearance",
            "slot_11": "OCPP",
            "slot_12": "Energy/Time limit",
            "slot_13": "Meter monitoring",
            "slot_14": "Cron"
        },
        "script": {
            "error_code": "Error code",
            "set_charging_current_failed": "Failed to set charging current",
            "start_charging_failed": "Failed to start charging",
            "stop_charging_failed": "Failed to stop charging",
            "tab_close_warning": "Charge log capture will be aborted if this tab is closed.",
            "loading_debug_report": "Loading debug report",
            "loading_debug_report_failed": "Loading debug report failed",
            "loading_event_log": "Loading event log",
            "loading_event_log_failed": "Loading event log failed",
            "starting_debug": "Starting charge log capture",
            "starting_debug_failed": "Starting charge log capture failed.",
            "debug_running": "Capturing. Don't close tab!",
            "debug_stop_failed": "Stopping charge log capture failed",
            "debug_stopped": "Stopped charge log capture",
            "debug_done": "Done",

            "acc_blocked": "Blocked",
            "by": "by",

            "save_failed": "Failed to save charge settings.",

            "reset_slot_failed": "Releasing the current limit failed",

            "slot_disabled": "Not active",
            "slot_blocks": "Blocks",
            "slot_no_limit": "Released",

            "slot_0": "supply cable",
            "slot_1": "charging cable",
            "slot_2": "shutdown input",
            "slot_3": "general purpose input",
            "slot_5": "configuration",
            "slot_6": "user/NFC",
            "slot_7": "charge management",
            "slot_8": "external control",
            "slot_9": "Modbus TCP",
            "slot_10": "Modbus TCP clearance",
            "slot_11": "OCPP",
            "slot_12": "energy/time limit",
            "slot_13": "meter monitoring",

            "reboot_content_changed": "charge settings"
        }
    }
}
