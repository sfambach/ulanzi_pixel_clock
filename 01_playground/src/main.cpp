// Ulanzi TC001 playground: scrolling text, buttons, buzzer, light sensor, battery.
// Copyright (C) 2026 Stefan Fambach (SteFam), https://www.fambach.net
// License: PolyForm Noncommercial 1.0.0, see ../../LICENSE.md
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <FastLED.h>
#include <FastLED_NeoMatrix.h>

constexpr uint8_t PIN_MATRIX = 32;
constexpr uint8_t PIN_BUZZER = 15;
constexpr uint8_t PIN_LDR = 35;
constexpr uint8_t PIN_BATTERY = 34;
constexpr uint8_t PIN_BTN_LEFT = 26;
constexpr uint8_t PIN_BTN_MID = 27;
constexpr uint8_t PIN_BTN_RIGHT = 14;

constexpr uint8_t WIDTH = 32;
constexpr uint8_t HEIGHT = 8;

CRGB leds[WIDTH * HEIGHT];
// Rows are wired as a serpentine: even rows left to right, odd rows right to left.
FastLED_NeoMatrix matrix(leds, WIDTH, HEIGHT,
                         NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG);

enum class Mode : uint8_t { Text, Rainbow, Sensors, Count };
Mode mode = Mode::Text;

const char *message = "Hallo fambach.net!";
int16_t scrollX = WIDTH;
uint8_t hue = 0;
uint8_t brightness = 20;

struct Button {
  uint8_t pin;
  bool last;
  explicit Button(uint8_t p) : pin(p), last(true) {}
  bool pressed() {
    bool now = digitalRead(pin);
    bool fell = last && !now;
    last = now;
    return fell;
  }
};
Button btnLeft(PIN_BTN_LEFT), btnMid(PIN_BTN_MID), btnRight(PIN_BTN_RIGHT);

void beep(uint16_t freq, uint16_t ms) {
  tone(PIN_BUZZER, freq, ms);
  delay(ms);
  noTone(PIN_BUZZER);
  // Floating pin makes the buzzer whine.
  pinMode(PIN_BUZZER, INPUT_PULLDOWN);
}

void drawText() {
  matrix.fillScreen(0);
  matrix.setTextColor(matrix.Color(255, 160, 0));
  matrix.setCursor(scrollX, 0);
  matrix.print(message);
  int16_t textWidth = strlen(message) * 6;
  if (--scrollX < -textWidth) scrollX = WIDTH;
}

void drawRainbow() {
  for (uint8_t x = 0; x < WIDTH; x++) {
    CRGB c = CHSV(hue + x * 8, 255, 255);
    for (uint8_t y = 0; y < HEIGHT; y++) matrix.drawPixel(x, y, matrix.Color(c.r, c.g, c.b));
  }
  hue += 2;
}

void drawSensors() {
  matrix.fillScreen(0);
  matrix.setTextColor(matrix.Color(0, 200, 255));
  matrix.setCursor(1, 0);
  // Raw ADC values; calibration is up to you.
  if ((millis() / 2000) % 2 == 0) {
    matrix.print("L");
    matrix.print(analogRead(PIN_LDR));
  } else {
    matrix.print("B");
    matrix.print(analogRead(PIN_BATTERY));
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(PIN_BTN_LEFT, INPUT_PULLUP);
  pinMode(PIN_BTN_MID, INPUT_PULLUP);
  pinMode(PIN_BTN_RIGHT, INPUT_PULLUP);
  pinMode(PIN_BUZZER, INPUT_PULLDOWN);

  FastLED.addLeds<WS2812B, PIN_MATRIX, GRB>(leds, WIDTH * HEIGHT);
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(brightness);
  beep(2000, 60);
}

void loop() {
  if (btnLeft.pressed() && brightness > 5) brightness -= 10;
  if (btnRight.pressed() && brightness < 200) brightness += 10;
  if (btnMid.pressed()) {
    mode = static_cast<Mode>((static_cast<uint8_t>(mode) + 1) % static_cast<uint8_t>(Mode::Count));
    beep(1500, 30);
  }
  matrix.setBrightness(brightness);

  switch (mode) {
    case Mode::Text: drawText(); break;
    case Mode::Rainbow: drawRainbow(); break;
    case Mode::Sensors: drawSensors(); break;
    default: break;
  }
  matrix.show();
  delay(40);
}
