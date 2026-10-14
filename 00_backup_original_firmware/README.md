# 00 – Back up the original firmware

Do this before flashing anything else. Without a backup the only way back is Ulanzi's update package.

```sh
sudo apt install esptool    # Debian/Ubuntu/Mint (command may be `esptool` instead of `esptool.py`)
# or: pipx install esptool   # newest version
esptool.py --port /dev/ttyUSB0 flash_id          # should report 8 MB
esptool.py --port /dev/ttyUSB0 --baud 921600 read_flash 0x0 0x800000 tc001-original.bin
```

Restore:

```sh
esptool.py --port /dev/ttyUSB0 --baud 921600 write_flash 0x0 tc001-original.bin
```

- Linux: add yourself to the `dialout` group for serial access (`sudo usermod -aG dialout $USER`, then log in again).
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
esptool.py --port /dev/ttyUSB0 --baud 921600 write_flash 0x10000 UCLOCK_0107013834aa_1.7.1.bin
```

Not tested yet. After another firmware has replaced the partition table, a full own backup
(see above) is the safe way back.
