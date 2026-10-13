# 01 – Playground (own firmware)

Minimal PlatformIO project to get to know the hardware.

- Libraries: FastLED, FastLED NeoMatrix, Adafruit GFX (text, pixels, lines)
- Left / right button: brightness down / up
- Middle button: next mode → scrolling text, rainbow, raw sensor values (L = light, B = battery)
- Short beep on start and on mode change

## Build and flash

Open the folder in VS Code with PlatformIO and press *Upload*, or:

```sh
pio run -t upload
pio device monitor
```

## Status

- Build: OK (PlatformIO, espressif32, Arduino)
- On the clock: not tested yet

## Ideas

- Time from the DS1307 RTC (`RTClib`) or NTP over Wi-Fi
- Temperature/humidity from the SHT3x (`Adafruit SHT31`)
- Battery voltage calibration
