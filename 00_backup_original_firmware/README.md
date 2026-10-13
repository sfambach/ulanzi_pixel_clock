# 00 – Back up the original firmware

Do this before flashing anything else. Without a backup the only way back is Ulanzi's update package.

```sh
pip install esptool
esptool.py --port /dev/ttyUSB0 flash_id          # should report 8 MB
esptool.py --port /dev/ttyUSB0 --baud 921600 read_flash 0x0 0x800000 tc001-original.bin
```

Restore:

```sh
esptool.py --port /dev/ttyUSB0 --baud 921600 write_flash 0x0 tc001-original.bin
```

- Windows: use `COM3` (or similar) instead of `/dev/ttyUSB0`; a CH340 driver may be needed.
- `*.bin` is ignored by git on purpose: the factory firmware is not ours to publish.
