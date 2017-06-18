//DHT11 hőmérséklet és páratartalom szenzor értékeinek PCD8544 Nokia 3310 LCD-re

#include <DHT.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

#define DHTPIN 4 //DHT szenzor PIN
#define DHTTYPE DHT11//nekem most csak ez van

DHT dht(DHTPIN, DHTTYPE);

//Nokia LCD bekötése
const int8_t RST_PIN = 8;
const int8_t CE_PIN = 10;
const int8_t DC_PIN = 9;
const int8_t DIN_PIN = 11;
const int8_t CLK_PIN = 13;
const int8_t BL_PIN = 7;

Adafruit_PCD8544 display = Adafruit_PCD8544(DC_PIN, CE_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(BL_PIN, OUTPUT);
  digitalWrite(BL_PIN, HIGH);
  display.begin();
  display.setContrast(60);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0,0);
  display.println("Zoli DHT test");
  Serial.println("Zoli DHT test");
  display.display();
}

void loop() {
  //a tényleges program, ismételjük a lépéseket
  delay(3000); //kicsit várunk az elöző mérés után
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("Zoli homero");
  float paratartalom = dht.readHumidity(); //páratartalom
  float homerseklet = dht.readTemperature(); //hőmérséklet Celsiusban

// későbbi hibaüzenethez kell majd, ha nincs érték akkor valamit azért böfögjünk
  if (isnan(paratartalom) || isnan(homerseklet)) {
    Serial.println("DHT nem talalhato"); 
    return;  
    }
  display.println("Paratartalom:");
  display.print(paratartalom);
  display.println(" %");
  Serial.print("Paratartalom: ");
  Serial.print(paratartalom);
  Serial.print(" %\t");
  display.println("Homerseklet:");
  display.print(homerseklet);
  display.println(" Celsius");
  Serial.print("Homerseklet: ");
  Serial.print(homerseklet);
  Serial.println(" *C");
  display.display();
}
