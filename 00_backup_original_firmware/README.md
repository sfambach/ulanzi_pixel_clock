# 00 – Back up the original firmware

Do this before flashing anything else. Without a backup the only way back is Ulanzi's update package.

```sh
sudo apt install pipx && pipx install esptool && pipx ensurepath   # then open a new terminal
esptool --port /dev/ttyUSB0 flash-id          # 4 MB or 8 MB depending on the unit
esptool --port /dev/ttyUSB0 --baud 921600 read-flash 0 ALL tc001-original.bin
```

Restore:

```sh
esptool --port /dev/ttyUSB0 --baud 921600 write-flash 0x0 tc001-original.bin
```

- Linux: add yourself to the `dialout` group for serial access (`sudo usermod -aG dialout $USER`, then log in again).
- Do not use the Debian/Ubuntu/Mint `esptool` apt package: it lacks the stub flasher and `flash_id` fails with `FileNotFoundError ... stub_flasher_32.json` (seen with 4.7.0). Workaround for the apt version: add `--no-stub` (much slower).
- The buzzer whines while the chip sits in download mode (GPIO15 floating). Harmless; replugging does not help because of the battery. Press the reset hole on the back with a paperclip, or run any successful esptool command (e.g. `chip_id`), which hard-resets the chip at the end.
- No `/dev/ttyUSB0` on Ubuntu/Mint? The `brltty` package often grabs the CH340 chip: `sudo apt remove brltty`, then replug.
- The backup contains your stored Wi-Fi password. Keep it private.
- Windows: use `COM3` (or similar) instead of `/dev/ttyUSB0`; a CH340 driver may be needed.
- `*.bin` is ignored by git on purpose: the factory firmware is not ours to publish.

## Official firmware download (no own backup)

Ulanzi publishes the factory firmware on its product page. It is not copied into this repository
on purpose: it contains Ulanzi's own code and no license allows redistribution.

| Version | Link | SHA-256 |
|---|---|---|
| 1.7.1 | [UCLOCK_0107013834aa_1.7.1.bin](https://cdn.shopify.com/s/files/1/0136/3119/3188/files/UCLOCK_0107013834aa_1.7.1.bin?v=1681377705) | `302b59c7c7d214cae65044b2f3cdc79dab2378637c3386ff4bb5603698eda671` |

Product page: <https://www.ulanzi.com/products/ulanzi-pixel-smart-clock-2882>

The file is an application image only (no bootloader, no partition table). Flashing it at the
application offset should work while the bootloader and partition table are still the original ones:

```sh
esptool --port /dev/ttyUSB0 --baud 921600 write-flash 0x10000 UCLOCK_0107013834aa_1.7.1.bin
```

Not tested yet. After another firmware has replaced the partition table, a full own backup
(see above) is the safe way back.
