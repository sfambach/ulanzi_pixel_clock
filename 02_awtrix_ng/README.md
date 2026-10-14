# 02 – AWTRIX NG

[AWTRIX NG](https://github.com/Blueforcer/awtrix-ng) is the successor of AWTRIX 3 (AWTRIX 3 is archived).
No cloud, HTTP and MQTT API, Home Assistant MQTT discovery, Berry scripts running on the clock.
License: PolyForm Noncommercial 1.0.0 (AWTRIX 3: CC BY-NC-SA 4.0).

## Option 1: flash from the browser

1. Back up the original firmware first ([00](../00_backup_original_firmware/)).
2. Use a browser with Web Serial (Chrome, Chromium, Edge; reported to work in a current Firefox too). Connect the clock with a USB data cable.
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

1. The clock opens the hotspot `awtrixng-xxxxxx` (no password).
2. Join it; the setup page opens at `192.168.4.1`. Enter Wi-Fi (optionally a hostname), press **Save**, then **Reboot now**.
3. At start-up the display shows its IP address; open it in the browser (or `http://<hostname>.local`).
4. Enter the MQTT broker for Home Assistant discovery. Scripts, icons, automations: <https://awtrix.de>

## Notes

- Status: not tested yet
