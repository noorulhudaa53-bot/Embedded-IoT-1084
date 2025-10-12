#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED screen configuration
#define WIDTH 128
#define HEIGHT 64
#define RESET_PIN -1
#define I2C_ADDR 0x3C

Adafruit_SSD1306 oled(WIDTH, HEIGHT, &Wire, RESET_PIN);

void setup() {
  Serial.begin(9600);

  // OLED initialize
  if (!oled.begin(SSD1306_SWITCHCAPVCC, I2C_ADDR)) {
    Serial.println(F("OLED not found!"));
    while (true);
  }

  oled.clearDisplay(); // remove old data

  // text settings
  oled.setTextSize(2);  // thoda bada font
  oled.setTextColor(SSD1306_WHITE);
  oled.setCursor(12, 18); // thoda upar aur left shift

  // display name and ID
  oled.println("Noor Ul Huda");
  oled.setTextSize(1);  
  oled.setCursor(15, 38);
  oled.println("Roll: 22-NTU-CS-1084");

  // border rectangle 
  oled.drawRect(8, 10, 110, 45, SSD1306_WHITE);

  // decorative small box (extra touch)
  oled.fillRect(5, 5, 5, 5, SSD1306_WHITE); // small corner dot

  oled.display(); // update screen
}

void loop() {
  // Static display (no loop actions)
}