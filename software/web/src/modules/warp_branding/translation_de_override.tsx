/** @jsxImportSource preact */
import { h } from "preact";
let x = {
    "charge_manager": {
        "status": {
            "charge_manager": "Lastmanager"
        },
        "navbar": {
            "charge_manager": "Lastmanagement"
        },
        "content": {
            "charge_manager": "Lastmanagement"
        }
    },
    "ethernet": {
        "content": {
            "enable_desc": "Die Wallbox verbindet sich automatisch beim Start oder wenn ein Kabel eingesteckt wird"
        }
    },
    "event_log": {
        "content": {
            "debug_report_desc_muted": "kompletter Report aller Statusinformationen der Wallbox außer Passwörtern"
        }
    },
    "firmware_update": {
        "content": {
            "factory_reset_modal_text": <>Hiermit wird die gesamte Konfiguration auf den Werkszustand zurückgesetzt. Alle aufgezeichneten Ladevorgänge gehen verloren. <b>Diese Aktion kann nicht rückgängig gemacht werden!</b> Die Wallbox öffnet dann wieder einen eigenen WLAN-Access-Point mit dem Netzwerknamen (SSID) und der Passphrase aus der beiliegenden Betriebsanleitung. Fortfahren</>,
            "config_reset_modal_text": <>Hiermit wird nur die Konfiguration auf den Werkszustand zurückgesetzt. Aufgezeichnete Ladevorgänge bleiben erhalten. <b>Diese Aktion kann nicht rückgängig gemacht werden!</b> Die Wallbox öffnet dann wieder einen eigenen WLAN-Access-Point mit dem Netzwerknamen (SSID) und der Passphrase aus der beiliegenden Betriebsanleitung. Fortfahren</>,
            "reboot_desc": "ein laufender Ladevorgang wird nicht unterbrochen",
            "factory_reset_desc": "löscht die Konfiguration und alle aufgezeichneten Ladevorgänge",
            "config_reset_desc": "aufgezeichnete Ladevorgänge bleiben erhalten"
        },
        "script": {
            "no_info_page": "Firmware-Datei ist beschädigt oder für WARP 1 (Firmware-Info-Seite fehlt)",
            "wrong_firmware_type": "Firmware-Datei passt nicht zu diesem Wallbox-Typ"
        }
    },
    "network": {
        "content": {
            "enable_mdns_desc": "Erlaubt es anderen Geräten in diesem Netzwerk die Wallbox zu finden"
        }
    },
    "mqtt": {
        "content": {
            "enable_mqtt_desc": <>Hierdurch kann die Wallbox über den konfigurierten MQTT-Broker kontrolliert werden. <a href="{{{apidoc_url}}}">MQTT-API-Dokumentation</a></>
        }
    },
    "util": {
        "event_connection_lost_title": "Verbindung zur Wallbox verloren!"
    },
    "wifi": {
        "content": {
            "sta_enable_sta_desc": "Die Wallbox verbindet sich beim Start automatisch zum konfigurierten Netzwerk",
            "ap_hide_ssid_desc_pre": "Die Wallbox ist unter der BSSID ",
            "confirm_content": <>Soll der WLAN-Access-Point wirklich komplett deaktiviert werden? Falls zukünftig keine Verbindung zu einem konfigurierten Netzwerk möglich ist, <b>kann nicht mehr auf die Wallbox zugegriffen werden</b>. Die Wallbox muss dann auf den Werkszustand zurückgesetzt werden. <a href="{{{manual_url}}}">Siehe Betriebsanleitung für Details.</a></>
        }
    },
    "charge_tracker": {
        "content": {
            "charge_tracker_remove_modal_text": <>Alle aufgezeichneten Ladevorgänge und der Benutzernamen-Verlauf werden gelöscht. <b>Diese Aktion kann nicht rückgängig gemacht werden!</b> Danach wird die Wallbox neugestartet.</>
        }
    },
    "meter": {
        "status": {
            "charge_history": "Ladeverlauf"
        }
    }
}
