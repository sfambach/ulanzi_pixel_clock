# Ulanzi Pixel Clock (TC001) – experiments

One folder per test on the Ulanzi TC001 Smart Pixel Clock (ESP32, 8 × 32 RGB LED matrix).

| Folder | Test |
|---|---|
| [00_backup_original_firmware](00_backup_original_firmware/) | Back up and restore the factory firmware (do this first) |
| [01_playground](01_playground/) | Own firmware with PlatformIO: scrolling text, buttons, buzzer, sensors |
| [02_awtrix_ng](02_awtrix_ng/) | AWTRIX NG (successor of AWTRIX 3) |
| [03_esphome](03_esphome/) | ESPHome with EspHoMaTriX v2 for Home Assistant |

## Hardware

| Part | Details |
|---|---|
| MCU | ESP32-WROOM-32D, 4 or 8 MB flash (depends on the unit), CH340 USB-serial on USB-C |
| Matrix | 256 × WS2812B-Mini, 32 × 8, data on GPIO32, serpentine rows |
| Buttons | left GPIO26, middle GPIO27, right GPIO14 (active low, pull-up) |
| Buzzer | GPIO15 (keep INPUT_PULLDOWN when idle, else it whines) |
| Light sensor | GL5516 LDR on GPIO35 (ADC) |
| Battery | 4400 mAh, voltage on GPIO34 (ADC) |
| I²C | SDA GPIO21, SCL GPIO22: SHT3x temp/humidity (0x44), DS1307 RTC (0x68) |

Source: [rroels/ulanzi_tc001_hardware](https://github.com/rroels/ulanzi_tc001_hardware)

## Blog

Article on [fambach.net](https://www.fambach.net) (German).

## License

Own code: PolyForm Noncommercial 1.0.0, see [LICENSE.md](LICENSE.md).
Commercial use only with the consent of Stefan Fambach (SteFam).
Third-party firmware and libraries keep their own licenses.

Trademarks: Ulanzi is a trademark of Shenzhen Ulanzi Technology Co., Ltd.; ESP32 is a trademark of Espressif Systems.

## AI disclosure

Parts of this repository (code and documentation) were created with the help of an AI assistant (Claude by Anthropic) and reviewed by the author.
