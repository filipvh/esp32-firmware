/** @jsxImportSource preact */
import { h } from "preact";
let x = {
    "firmware_update": {
        "status": {

        },
        "navbar": {
            "flash": "Firmware Update"
        },
        "content": {
            "current_firmware": "Firmware version",
            "firmware_update": "Firmware Update",
            "firmware_update_label": "Firmware update",
            "firmware_update_desc": <><a href="{{{firmware_url}}}">firmware download</a></>,
            "browse": "Browse",
            "select_file": "Firmware file",
            "update": "Upload",
            "current_spiffs": "Configuration version",
            "factory_reset_desc": null,
            "factory_reset": "Factory reset",
            "factory_reset_modal_text": null,

            "config_reset_desc": null,
            "config_reset": "Reset configuration",

            "config_reset_modal_text": null,
            "confirm_config_reset": "Reset configuration",

            "abort_reset": "Abort",
            "confirm_factory_reset": "Reset to factory defaults",
            "reboot": "Reboot",
            "reboot_desc": null,
            "downgrade": "Firmware downgrade",
            "abort_downgrade": "Abort",
            "confirm_downgrade": "Downgrade firmware"
        },
        "script": {
            "flash_success": "Successfully updated; restarting...",
            "flash_fail": "Failed to update",
            "factory_reset_init": "Formatting configuration partition and restarting...",
            "factory_reset_error": "Initiating factory reset failed",
            "config_reset_init": "Resetting configuration and restarting...",
            "config_reset_error": "Failed to reset configuration",
            "vehicle_connected": "Can't update the firmware while a vehicle is connected.",
            "no_info_page": null,
            "info_page_corrupted": "Firmware file corrupted (checksum error)",
            "wrong_firmware_type": null,
            "downgrade": "Firmware file contains a downgrade to version %fw%. Installed is version %installed%.",
            "build_time_prefix": " (created ",
            "build_time_suffix": ")"
        }
    }
}
