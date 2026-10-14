# 02 – AWTRIX NG

[AWTRIX NG](https://github.com/Blueforcer/awtrix-ng) is the successor of AWTRIX 3 (AWTRIX 3 is archived).
No cloud, HTTP and MQTT API, Home Assistant MQTT discovery, Berry scripts running on the clock.
License: PolyForm Noncommercial 1.0.0 (AWTRIX 3: CC BY-NC-SA 4.0).

## Option 1: flash from the browser

1. Back up the original firmware first ([00](../00_backup_original_firmware/)).
2. Use a browser with Web Serial (Chrome, Chromium, Edge; worked in Firefox on Linux too). Connect the clock with a USB data cable.
3. Open <https://blueforcer.github.io/awtrix-ng/esp32/getting-started/flashing/>, press **Fresh install**, pick `/dev/ttyUSB0` and wait for **Done**.
   *Fresh install* clears settings and Wi-Fi; *Update AWTRIX NG* keeps them.

## Option 2: download the image and flash with esptool

Download `usb-awtrix-ng.zip` from the releases and use `usb-awtrix-ng-4mb.bin` (complete image, written at 0x0):

```sh
wget https://github.com/Blueforcer/awtrix-ng/releases/latest/download/usb-awtrix-ng.zip
unzip usb-awtrix-ng.zip usb-awtrix-ng-4mb.bin
esptool --chip esp32 --port /dev/ttyUSB0 --baud 460800 write-flash 0x0 usb-awtrix-ng-4mb.bin
```

Use 460800 baud: according to the AWTRIX NG docs, a write at 921600 stops partway on a TC001.
Look for `Hash of data verified.`

## First boot

1. After flashing the clock restarts, lights up in colours (setup mode) and opens the hotspot `awtrixng-xxxxxx` (no password; the suffix is the end of the MAC address).
2. Join it and open `http://192.168.4.1`. Under **Wi-Fi** press **Scan**, pick your network, enter the password (optionally a hostname).
3. Press **Save**, then **Reboot** under **Maintenance**.
4. After the start animation the display shows its IP for a few seconds only. Missed it: replug, open `http://<hostname>.local` (default `awtrixng-xxxxxx.local`; Linux needs avahi-daemon) or check the router. The router usually hands out the same IP as before (same MAC). `AP MODE` on the display means joining failed (wrong password, 5 GHz only).
5. Enter the MQTT broker for Home Assistant discovery. Scripts, icons, automations: <https://awtrix.de>

## Notes

- Status: flashed with the web flasher (Firefox, Linux), Wi-Fi setup works. MQTT / Home Assistant not tested yet.
- The buzzer whines while the clock is in download mode (GPIO15 floats); it stops after the restart.
- Tested version 1.2.2. Default rotation: time (calendar icon, weekday bar), date, temperature, humidity, battery.
- The internal temperature reads high (32 °C here, sensor inside the case); correct it with `tempOffset`.

## Scrolling text

No text field in the web UI; use the HTTP API. Text that does not fit scrolls by itself.

```sh
# one-off notification, scrolled twice
curl -X POST http://clock.local/api/v1/notifications -H 'Content-Type: application/json' \
  -d '{"text":"Hello from fambach.net","repeat":2}'
# app that stays in the rotation until the next restart
curl -X PUT http://clock.local/api/v1/apps/pushed/scrolltext -H 'Content-Type: application/json' \
  -d '{"text":"Hello from fambach.net","textColor":"#00AAFF"}'
```
