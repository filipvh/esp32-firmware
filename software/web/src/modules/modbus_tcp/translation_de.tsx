/** @jsxImportSource preact */
import { h } from "preact";
let x = {
    "modbus_tcp": {
        "navbar": {
            "modbus_tcp": "Modbus/TCP"
        },
        "content": {
            "disabled": "Deaktiviert",
            "read_only": "Nur Lesezugriff",
            "full_access": "Lese-/Schreibzugriff",
            "table": "Registertabelle",
            "tf": "WARP Charger",
            "bender_emulate": "Kompatibel zu Bender CC613",
            "keba_emulate": "Kompatibel zu Keba C-Series",
            "modbus_tcp": "Modbus/TCP",
            "enable": "Modbus/TCP-Modus",
            "port": "Port",
            "port_muted": "typischerweise 502",
            "table_docu": "WARP Register-Dokumentation",
            "table_content": <>
                <thead class="thead-light">
                    <tr>
                        <th scope="col">Registeradresse</th>
                        <th scope="col">Name</th>
                        <th scope="col">Typ</th>
                        <th scope="col">Benötigtes Feature</th>
                        <th scope="col">Beschreibung</th>
                    </tr>
                </thead>
                <thead>
                    <tr>
                        <th colSpan={5}>Input Registers</th>
                    </tr>
                </thead>
                <tbody>
                    <tr>
                        <td>0</td>
                        <td>Version der Registertabelle</td>
                        <td>uint32</td>
                        <td>---</td>
                        <td>Aktuelle Version: 2</td>
                    </tr>
                    <tr>
                        <td>2</td>
                        <td>Firmware-Version Major</td>
                        <td>uint32</td>
                        <td>---</td>
                        <td>Beispielsweise 2 für Firmware 2.0.8-​63218f23</td>
                    </tr>
                    <tr>
                        <td>4</td>
                        <td>Firmware-Version Minor</td>
                        <td>uint32</td>
                        <td>---</td>
                        <td>Beispielsweise 0 für Firmware 2.0.8-​63218f23</td>
                    </tr>
                    <tr>
                        <td>6</td>
                        <td>Firmware-Version Patch</td>
                        <td>uint32</td>
                        <td>---</td>
                        <td>Beispielsweise 8 für Firmware 2.0.8-​63218f23</td>
                    </tr>
                    <tr>
                        <td>8</td>
                        <td>Zeitstempel der Firmware</td>
                        <td>uint32</td>
                        <td>---</td>
                        <td>Unix-Timestamp des Zeitpunktes an dem eine Firmware gebaut wurde. Beispielsweise 0x63218f23 für
                            Firmware 2.0.8-​63218f23 (in Dezimal 1663143715), entspricht dem 14. September 2022 08:21:55 UTC.</td>
                    </tr>
                    <tr>
                        <td>10</td>
                        <td>Charger-ID</td>
                        <td>uint32</td>
                        <td>---</td>
                        <td>Dekodierte Form der Base58-UID, die für Standard-Hostnamen, -SSID usw. genutzt wird. Zum Beispiel
                            185460 für X8A</td>
                    </tr>
                    <tr>
                        <td>12</td>
                        <td>Uptime (s)</td>
                        <td>uint32</td>
                        <td>---</td>
                        <td>Zeit in Sekunden seit dem Start der Wallbox-Firmware.</td>
                    </tr>
                    <tr>
                        <td>1000</td>
                        <td>IEC-61851-Zustand</td>
                        <td>uint32</td>
                        <td>evse</td>
                        <td>
                            <ul>
                                <li>0: A</li>
                                <li>1: B</li>
                                <li>2: C</li>
                                <li>3: D</li>
                                <li>4: E/F</li>
                            </ul>
                        </td>
                    </tr>
                    <tr>
                        <td>1002</td>
                        <td>Fahrzeugstatus</td>
                        <td>uint32</td>
                        <td>evse</td>
                        <td>
                            <ul>
                                <li>0: Nicht verbunden</li>
                                <li>1: Warte auf Freigabe</li>
                                <li>2: Ladebereit</li>
                                <li>3: Lädt</li>
                                <li>4: Fehler</li>
                            </ul>
                        </td>
                    </tr>
                    <tr>
                        <td>1004</td>
                        <td>User-ID</td>
                        <td>uint32</td>
                        <td>evse</td>
                        <td>ID des Benutzers der den Ladevorgang gestartet hat. 0 falls eine Freigabe ohne Nutzerzuordnung erfolgt
                            ist. 0xFFFFFFFF falls gerade kein Ladevorgang läuft.</td>
                    </tr>
                    <tr>
                        <td>1006</td>
                        <td>Start-Zeitstempel (min)</td>
                        <td>uint32</td>
                        <td>evse</td>
                        <td>Ein Unix-Timestamp in <strong>Minuten</strong>, der den Startzeitpunkt des Ladevorgangs angibt. 0
                            falls zum Startzeitpunkt keine Zeitsynchronisierung verfügbar war.</td>
                    </tr>
                    <tr>
                        <td>1008</td>
                        <td>Ladedauer (s)</td>
                        <td>uint32</td>
                        <td>evse</td>
                        <td>Dauer des laufenden Ladevorgangs in Sekunden. Auch ohne Zeitsynchronisierung verfügbar</td>
                    </tr>
                    <tr>
                        <td>1010</td>
                        <td>Erlaubter Ladestrom</td>
                        <td>uint32</td>
                        <td>evse</td>
                        <td>Maximal erlaubter Ladestrom, der dem Fahrzeug zur Verfügung gestellt wird. Dieser Strom ist das Minimum
                            der Stromgrenzen aller Ladeslots.</td>
                    </tr>
                    <tr>
                        <td>1012 bis 1052</td>
                        <td>Ladestromgrenzen (mA)</td>
                        <td>uint32 (x20)</td>
                        <td>evse</td>
                        <td>Aktueller Wert der Ladestromgrenzen in Milliampere. 0xFFFFFFFF falls eine Stromgrenze nicht aktiv
                            ist. 0 falls eine Stromgrenze blockiert. Sonst zwischen 6000 (6A) und 32000 (32A).</td>
                    </tr>
                    <tr>
                        <td>2000</td>
                        <td>Stromzählertyp</td>
                        <td>uint32</td>
                        <td>meter</td>
                        <td>
                            <ul>
                                <li>0: Kein Stromzähler verfügbar</li>
                                <li>1: SDM72 (nur WARP1)</li>
                                <li>2: SDM630</li>
                                <li>3: SDM72 V2</li>
                            </ul>
                        </td>
                    </tr>
                    <tr>
                        <td>2002</td>
                        <td>Ladeleistung (W)</td>
                        <td>float32</td>
                        <td>meter</td>
                        <td>Die aktuelle Ladeleistung in Watt</td>
                    </tr>
                    <tr>
                        <td>2004</td>
                        <td>absolute Energie (kWh)</td>
                        <td>float32</td>
                        <td>meter</td>
                        <td>Die geladene Energie seit der Herstellung des Stromzählers.</td>
                    </tr>
                    <tr>
                        <td>2006</td>
                        <td>relative Energie (kWh)</td>
                        <td>float32</td>
                        <td>meter</td>
                        <td>Die geladene Energie seit dem letzten Reset. (siehe Holding Register 2000)</td>
                    </tr>
                    <tr>
                        <td>2008</td>
                        <td>Energie des Ladevorgangs</td>
                        <td>float32</td>
                        <td>meter</td>
                        <td>Die während des laufenden Ladevorgangs geladene Energie</td>
                    </tr>
                    <tr>
                        <td>2100 bis 2270</td>
                        <td>weitere Stromzähler-Werte</td>
                        <td>float32 (x85)</td>
                        <td>all_values</td>
                        <td>Siehe <a href="https://www.warp-charger.com/api.html#meter_all_values">API-Dokumentation</a></td>
                    </tr>
                    <tr>
                        <td>3000</td>
                        <td>CP-Unterbrechung</td>
                        <td>uint32</td>
                        <td>cp_disc</td>
                        <td>Noch nicht implementiert!</td>
                    </tr>
                    <tr>
                        <td>4000</td>
                        <td>ID des letzten NFC-Tags</td>
                        <td>uint32 (x5)</td>
                        <td>nfc</td>
                        <td>Die ID des zuletzt erkannten NFC-Tags als ASCII-kodierter Hex-String.</td>
                    </tr>
                    <tr>
                        <td>4010</td>
                        <td>Alter des letzten NFC-Tags</td>
                        <td>uint32</td>
                        <td>nfc</td>
                        <td>Zeit in Millisekunden seitdem das zuletzt erkannten NFC-Tag das letzte mal erkannt wurde. Zeiten &lt;
                            1000 ms bedeuten typischerweise, dass das Tag gerade an die Wallbox gehalten wird.</td>
                    </tr>
                </tbody>
                <thead>
                    <tr>
                        <th colSpan={5}>Holding Registers</th>
                    </tr>
                </thead>
                <tbody>
                    <tr>
                        <td>0</td>
                        <td>Reboot</td>
                        <td>uint32</td>
                        <td>---</td>
                        <td>Startet die Wallbox (bzw. den ESP-Brick) neu, um beispielsweise Konfigurationsänderungen
                            anzuwenden. Password 0x012EB007</td>
                    </tr>
                    <tr>
                        <td>1000</td>
                        <td>Ladefreigabe</td>
                        <td>uint32</td>
                        <td>evse</td>
                        <td><strong>Veraltet. Stattdessen Coil 1000 verwenden!</strong> 0 zum Blockieren des Ladevorgangs; ein
                            Wert ungleich 0 zum Freigeben</td>
                    </tr>
                    <tr>
                        <td>1002</td>
                        <td>Erlaubter Ladestrom (mA)</td>
                        <td>uint32</td>
                        <td>evse</td>
                        <td>0 mA oder 6000 mA bis 32000 mA. Andere Ladestromgrenzen können den Strom weiter verringern!</td>
                    </tr>
                    <tr>
                        <td>1004</td>
                        <td>Front-LED-Blinkmuster</td>
                        <td>uint32</td>
                        <td>evse</td>
                        <td>Steuert die LED des Tasters in der Wallbox-Front. <ul>
                                <li>-1: EVSE kontrolliert LED</li>
                                <li>0: LED aus</li>
                                <li>1-254: LED gedimmt</li>
                                <li>255: LED an</li>
                                <li>1001: bekanntes NFC-Tag erkannt</li>
                                <li>1002: unbekanntes NFC-Tag erkannt</li>
                                <li>1003: NFC-Tag notwendig</li>
                                <li>2001-2010: Fehlerblinken 1-10</li>
                            </ul>
                        </td>
                    </tr>
                    <tr>
                        <td>1006</td>
                        <td>Front-LED-Blinkdauer</td>
                        <td>uint32</td>
                        <td>evse</td>
                        <td>Die Dauer in Millisekunden für die das in Register 1004 gesetzte Blinkmuster angezeigt werden soll.
                            Maximal 65535ms werden unterstützt.</td>
                    </tr>
                    <tr>
                        <td>2000</td>
                        <td>Relative Energie zurücksetzen</td>
                        <td>uint32</td>
                        <td>meter</td>
                        <td>Setzt den relativen Energiewert zurück (Input Register 2006). Password 0x3E12E5E7</td>
                    </tr>
                    <tr>
                        <td>3000</td>
                        <td>CP-Trennung auslösen</td>
                        <td>uint32</td>
                        <td>cp_disc</td>
                        <td>Noch nicht implementiert!</td>
                    </tr>
                </tbody>
                <thead>
                    <tr>
                        <th colSpan={5}>Discrete Inputs</th>
                    </tr>
                </thead>
                <tbody>
                    <tr>
                        <td>0</td>
                        <td>Feature "evse" verfügbar</td>
                        <td>bool</td>
                        <td>---</td>
                        <td>Ein Ladecontroller steht zur Verfügung. Dieses Feature sollte bei allen WARP Chargern, deren Hardware
                            funktionsfähig ist, vorhanden sein.</td>
                    </tr>
                    <tr>
                        <td>1</td>
                        <td>Feature "meter" verfügbar</td>
                        <td>bool</td>
                        <td>---</td>
                        <td>Ein Stromzähler und Hardware zum Auslesen desselben über RS485 ist verfügbar. Dieses Feature wird erst
                            gesetzt, wenn ein Stromzähler mindestens einmal erfolgreich über Modbus ausgelesen wurde.</td>
                    </tr>
                    <tr>
                        <td>2</td>
                        <td>Feature "phases" verfügbar</td>
                        <td>bool</td>
                        <td>---</td>
                        <td>Der verbaute Stromzähler kann Energie und weitere Messwerte einzelner Phasen messen.</td>
                    </tr>
                    <tr>
                        <td>3</td>
                        <td>Feature "all_values" verfügbar</td>
                        <td>bool</td>
                        <td>---</td>
                        <td>Der verbaute Stromzähler kann weitere Messwerte auslesen. </td>
                    </tr>
                    <tr>
                        <td>4</td>
                        <td>Feature "cp_disc" verfügbar</td>
                        <td>bool</td>
                        <td>---</td>
                        <td>Noch nicht implementiert!</td>
                    </tr>
                    <tr>
                        <td>5</td>
                        <td>Feature "nfc" verfügbar</td>
                        <td>bool</td>
                        <td>---</td>
                        <td>Ein NFC-Bricklet ist verbaut und aktiv.</td>
                    </tr>
                    <tr>
                        <td>2100</td>
                        <td>Phase L1 angeschlossen</td>
                        <td>bool</td>
                        <td>phases</td>
                        <td></td>
                    </tr>
                    <tr>
                        <td>2101</td>
                        <td>Phase L2 angeschlossen</td>
                        <td>bool</td>
                        <td>phases</td>
                        <td></td>
                    </tr>
                    <tr>
                        <td>2102</td>
                        <td>Phase L3 angeschlossen</td>
                        <td>bool</td>
                        <td>phases</td>
                        <td></td>
                    </tr>
                    <tr>
                        <td>2103</td>
                        <td>Phase L1 aktiv</td>
                        <td>bool</td>
                        <td>phases</td>
                        <td></td>
                    </tr>
                    <tr>
                        <td>2104</td>
                        <td>Phase L2 aktiv</td>
                        <td>bool</td>
                        <td>phases</td>
                        <td></td>
                    </tr>
                    <tr>
                        <td>2105</td>
                        <td>Phase L3 aktiv</td>
                        <td>bool</td>
                        <td>phases</td>
                        <td></td>
                    </tr>
                </tbody>
                <thead>
                    <tr>
                        <th colSpan={5}>Coils</th>
                    </tr>
                </thead>
                <tbody>
                    <tr>
                        <td>1000</td>
                        <td>Ladefreigabe</td>
                        <td>bool</td>
                        <td>evse</td>
                        <td>false bzw. 0 zum Blockieren des Ladevorgangs. true bzw. 1 zum Freigeben. (Identisch zu Holding
                            Register 1000)</td>
                    </tr>
                    <tr>
                        <td>1001</td>
                        <td>Manuelle Ladefreigabe</td>
                        <td>bool</td>
                        <td>evse</td>
                        <td>false bzw. 0 zum Blockieren des Ladevorgangs. true bzw. 1 zum Freigeben. Setzt die Ladefreigabe, die
                            auch (je nach Konfiguration) vom Taster, den Start/Stop-Buttons auf der Webinterface-Statusseite
                            und der evse/[start/stop]_charging-API verwendet wird.</td>
                    </tr>
                </tbody>

            </>
        },
        "script": {
            "save_failed": "Speichern der Modbus/TCP-Einstellungen fehlgeschlagen.",
            "reboot_content_changed": "Modbus/TCP-Einstellungen"
        }
    }
}
