# 03 – ESPHome (EspHoMaTriX v2)

[EspHoMaTriX v2](https://github.com/lubeda/EspHoMaTriXv2) (MIT) is an ESPHome component for 8 × 32 RGB matrices.
The clock becomes an ESPHome device in Home Assistant.

1. Back up the original firmware first ([00](../00_backup_original_firmware/)).
2. Pick the EspHoMaTriX branch that matches your ESPHome version (see its README) and set it as `ref` under `external_components`.
3. Start from the TC001 example by blakadder: <https://blakadder.com/esphome-pixel-clock/>.
   The pins there are correct, but the YAML is for v1 and must be adapted to v2.
4. Pins: matrix GPIO32, buzzer GPIO15, battery GPIO34, LDR GPIO35, buttons GPIO26/27/14, I²C SDA GPIO21 / SCL GPIO22.

Known limits: LDR and battery sensor are only partly supported.

## Notes

- Status: not tested yet, no YAML in this folder yet
