#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_NeoPixel.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

#define DHTPIN 2 // Broche de signal du capteur DHT
#define DHTTYPE DHT22 // Type de capteur DHT

#define LED_COUNT 16 // Nombre de LEDs dans chaque bandeau
#define LED_RED_PIN 4 // Broche de contrôle du bandeau LED pour la température (rouge)

#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Adafruit_BME280 bmp;

Adafruit_NeoPixel stripRed(LED_COUNT, LED_RED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);

  if (!bmp.begin(0x76)) {
    Serial.println(F("Capteur BMP280 non détecté, vérifiez le câblage !"));
    while (1);
  }


  stripRed.begin();
  stripRed.show();
  stripRed.setBrightness(50); // Ajustez la luminosité selon vos besoins

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Échec de l'initialisation de l'écran OLED"));
    for (;;);
  }

  display.display();
  delay(2000);
  display.clearDisplay();
}

void loop() {
  float temperature = bmp.readTemperature();
  float humidity = bmp.readHumidity();
  float pressure = bmp.readPressure() / 100.0F;

  updateNeoPixels(stripRed, map(temperature, 10, 30, 0, LED_COUNT), 64, 0, 0);
  delay(1000);
  updateNeoPixels(stripRed, map(humidity, 0, 100, 0, LED_COUNT ),0, 0, 64);
  delay(1000);
  updateNeoPixels(stripRed, map(pressure, 900, 1100, 0, LED_COUNT),64, 64 , 0);
  delay(1000);


  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print(F("Temp: "));
  display.print(temperature);
  display.println(F(" C"));

  display.print(F("Humidité: "));
  display.print(humidity);
  display.println(F("%"));

  display.print(F("Pression: "));
  display.print(pressure);
  display.println(F(" hPa"));
  
  display.display();
}

void updateNeoPixels(Adafruit_NeoPixel &strip, int ledCount, uint8_t red, uint8_t green, uint8_t blue) {
  strip.clear();
  for (int i = 0; i < ledCount; i++) {
    strip.setPixelColor(i, red, green, blue);
  }
  strip.show();
}



