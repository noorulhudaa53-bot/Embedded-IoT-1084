#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  // initialize serial (optional)
  Serial.begin(9600);

  // OLED init
  if (!oled.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("OLED init failed"));
    for (;;);
  }

  oled.clearDisplay();

  // ---------- Avatar (head) ----------
  // head outline (circle)
  oled.drawCircle(64, 22, 16, SSD1306_WHITE);

  // hair (top filled semicircle simulated with filledRect + pixels)
  oled.fillRect(48, 8, 32, 8, SSD1306_WHITE); // simple hair block
  // hair fringe (a few pixels to make it less blocky)
  oled.fillRect(56, 15, 2, 2, SSD1306_WHITE);
  oled.fillRect(60, 15, 2, 2, SSD1306_WHITE);
  oled.fillRect(52, 15, 2, 2, SSD1306_WHITE);

  // ears (small circles)
  oled.fillCircle(47, 22, 3, SSD1306_WHITE);
  oled.fillCircle(81, 22, 3, SSD1306_WHITE);

  // eyes (white dots) and pupils (smaller black via skipping pixel)
  oled.fillCircle(58, 20, 3, SSD1306_WHITE); // left eye (white)
  oled.fillCircle(70, 20, 3, SSD1306_WHITE); // right eye
  // pupils (draw single pixel to look 'black' by not drawing)
  oled.drawPixel(58, 20, SSD1306_BLACK); // left pupil (simulate by clearing)
  oled.drawPixel(70, 20, SSD1306_BLACK); // right pupil

  // glasses (optional) - rectangle frames and bridge
  oled.drawRect(54, 17, 8, 6, SSD1306_WHITE);
  oled.drawRect(68, 17, 8, 6, SSD1306_WHITE);
  oled.drawLine(62, 20, 66, 20, SSD1306_WHITE); // bridge

  // nose (small vertical line)
  oled.drawLine(64, 22, 64, 25, SSD1306_WHITE);

  // mouth (curve made of pixels)
  oled.drawPixel(60, 27, SSD1306_WHITE);
  oled.drawPixel(61, 28, SSD1306_WHITE);
  oled.drawPixel(62, 29, SSD1306_WHITE);
  oled.drawPixel(63, 29, SSD1306_WHITE);
  oled.drawPixel(64, 29, SSD1306_WHITE);
  oled.drawPixel(65, 29, SSD1306_WHITE);
  oled.drawPixel(66, 28, SSD1306_WHITE);
  oled.drawPixel(67, 27, SSD1306_WHITE);

  // ---------- Torso (simple) ----------
  oled.fillRect(52, 34, 24, 18, SSD1306_WHITE); // shirt block
  oled.drawRect(52, 34, 24, 18, SSD1306_WHITE); // border

  // small collar lines
  oled.drawLine(64, 34, 64, 38, SSD1306_BLACK); // gap for collar (clear a pixel)
  oled.drawPixel(62, 36, SSD1306_BLACK);
  oled.drawPixel(66, 36, SSD1306_BLACK);

  // ---------- Name / caption ----------
  oled.setTextSize(1);
  oled.setTextColor(SSD1306_WHITE);
  oled.setCursor(10, 56);
  oled.println("Miss Noor"); // 

  oled.display();
}

void loop() {
  // static avatar
}