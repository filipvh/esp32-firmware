/** @jsxImportSource preact */
import { h } from "preact";
let x = {
    "energy_manager": {
        "status": {
            "mode": "Charging mode",
            "mode_fast": "Fast",
            "mode_off": "Off",
            "mode_pv": "PV",
            "mode_min_pv": "Min + PV",
            "phase_switching": "Phase switching",
            "single_phase": "Single-phase",
            "three_phase":"Three-phase",
            "external_control_state": "External control",
            "external_control_state_available": "Available",
            "external_control_state_disabled": "Disabled",
            "external_control_state_unavailable": "Unavailable",
            "external_control_state_switching": "Switching now",
            "external_control_request": "External phase request",
            "external_control_request_none": "None",
            "status": "Energy manager",
            "error_ok": "OK",
            "error_network": "Network error",
            "error_contactor": "Contactor error",
            "error_config": "Incomplete configuration",
            "error_internal": "Internal error",
            "config_error_phase_switching": "Phase switching or contactor not configured",
            "config_error_no_max_current": "No maximum current configured for chargers",
            "config_error_no_chargers": "No chargers configured",
            "config_error_excess_no_meter": "Excess charging enabled but no meter configured",
            "config_error_no_cm": "Charge Management not available",

            "no_bricklet": "Internal error, bricklet not found"
        },
        "navbar": {
            "energy_manager": "Settings"
        },
        "content": {
            "page_header": "Energy Manager",

            "header_phase_switching": "Phase switching",
            "contactor_installed": "Contactor installed",
            "contactor_installed_desc": "The energy manager is connected to a contactor that it can use to switch its managed chargers between single-phase and three-phase connection.",
            "phase_switching_mode": "Switching mode",
            "fixed_single_phase": "Fixed single-phase connection",
            "fixed_three_phases": "Fixed three-phase connection",
            "automatic": "Automatic",
            "always_single_phase": "Always single-phase",
            "always_three_phases": "Always three-phase",
            "pv1p_fast3p": "Single-phase PV mode, three-phase Fast mode",
            "external_control": "External control (EVCC)",
            "external_control_notification": "External control for phase switching is active. This will disable all settings related to PV excess charging.",

            "header_load_management": "Dynamic load management",
            "load_management_explainer": "The energy manager adjusts the power consumption of controlled chargers to avoid exceeding the maximum allowed current on any phase of the building's mains connection. (Coming soon: This feature is currently in development.)",

            "header_excess_charging": "Photovoltaic excess charging",
            "enable_excess_charging": "Excess charging enabled",
            "enable_excess_charging_muted": <><a href="{{{manual_url}}}">see manual for details</a></>,
            "enable_excess_charging_desc": "The energy manager will adjust the power consumption of controlled chargers, depending on the power generation of a photovoltaic system and the charge mode.",
            "default_mode": "Default charging mode",
            "default_mode_muted": "will be used after energy manager reboot",
            "auto_reset_charging_mode": "Daily reset",
            "auto_reset_charging_mode_desc": "Automatically sets the charging mode back to the default.",
            "auto_reset_time": "Reset at",
            "guaranteed_power": "Min + PV: Minimum charging power",
            "guaranteed_power_muted": "Charging power that is allowed to be drawn from the grid to charge vehicles.",
            "target_power_from_grid": "Target grid power draw",
            "target_power_from_grid_muted": "target grid draw for excess charging",
            "control_behavior": "Control behavior",
            "control_behavior_muted": <><a href="{{{manual_url}}}">see manual for details</a></>,
            "target_power_n200": "Very conservative (− 200 W)",
            "target_power_n100": "Conservative (− 100 W)",
            "target_power_n50": "Slightly conservative (− 50 W) – charges battery bank first",
            "target_power_0": "Balanced (± 0 W) – recommended with no battery bank",
            "target_power_p50": "Slightly aggressive (+ 50 W) – uses battery bank to charge vehicle",
            "target_power_p100": "Aggressive (+ 100 W)",
            "target_power_p200": "Very aggressive (+ 200 W)",
            "cloud_filter": "Cloud filter",
            "cloud_filter_muted": "reduces influence of partly cloudy weather",
            "cloud_filter_off": "None",
            "cloud_filter_weak": "Weak",
            "cloud_filter_medium": "Medium",
            "cloud_filter_strong": "Strong",

            "relay": "Relay",
            "single_phase": "Single-phase",
            "three_phase": "Three-phase",
            "input3_rule_then": "Mode",
            "input4_rule_then": "Mode",
            "relay_config": "Mode",
            "relay_manual": "Manually controlled or unused",
            "relay_rules": "Rule-based",
            "relay_rule_when": "When",
            "relay_rule_is": "Is",
            "relay_config_then": "Then",
            "relay_config_close": "Close relay",
            "low": "Open",
            "high": "Closed",
            "contactor_fail": "Tripped, contactor failed",
            "contactor_ok": "Not tripped, contactor OK",
            "power_available": "Power available",
            "power_sufficient": "Sufficient for charging",
            "power_insufficient": "Insufficient for charging",
            "grid_draw": "Grid power draw",
            "grid_gt0": "Drawing power from grid",
            "grid_le0": "Feeding power to grid",

            "input3": "Input 3",
            "input4": "Input 4",
            "input_unused": "Unused",
            "contactor_check": "Contactor monitoring",
            "block_charging": "Block charging",
            "limit_max_current": "Limit charge current",
            "limit_to_current": "Limit to",
            "input_when": "When",
            "input_low": "Input open",
            "input_high": "Input closed",
            "phase_switching": "Phase switching",
            "input_switch_mode": "Switch charge mode",
            "input_when_closing": "When closing input",
            "input_when_opening": "When opening input",
            "input_switch_to_prefix": "To ",
            "input_switch_to_suffix": "",
            "input_mode_nothing": "Don't switch",

            "header_expert_settings": "Expert settings",
            "hysteresis_time": "Hysteresis time",
            "hysteresis_time_muted": "Minimum delay before phase switches or starting or stopping a charge, to avoid excessive wear on the vehicle's charge electronics by switching too often."
        },
        "script": {
            "save_failed": "Failed to save energy manager settings.",
            "reboot_content_changed": "energy manager settings",
            "mode_change_failed": "Failed to change charging mode."
        }
    }
}
