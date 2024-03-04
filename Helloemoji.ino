#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  // Initialisation de l'écran
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 initialization failed"));
    for(;;);
  }
  
  // Effacer l'écran
  display.clearDisplay();

  // Afficher "Hello World" en haut de l'écran
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Hello World!");

  // Dessiner le bonhomme souriant
  // Dessiner les yeux
  display.drawPixel(30, 20, SSD1306_WHITE);
  display.drawPixel(35, 20, SSD1306_WHITE);
  
  // Dessiner la bouche
  display.drawPixel(28, 25, SSD1306_WHITE);
  display.drawPixel(29, 26, SSD1306_WHITE);
  display.drawPixel(30, 27, SSD1306_WHITE);
  display.drawPixel(31, 28, SSD1306_WHITE);
  display.drawPixel(32, 27, SSD1306_WHITE);
  display.drawPixel(33, 26, SSD1306_WHITE);
  display.drawPixel(34, 25, SSD1306_WHITE);

  // Mettre à jour l'écran
  display.display();
}

void loop() {
  // Rien à faire ici, tout est affiché dans le setup()
}

