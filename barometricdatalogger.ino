#include <SD.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bme;
#define SEALEVELPRESSURE_HPA (1013.25)

File data;

int meteoCount = 1;

void setup() {
  Serial.begin(9600);
  bme.begin(0x76);
  pinMode(4, OUTPUT);
  SD.begin(4);

  data = SD.open("MetData.txt", FILE_WRITE);
  data.println("Count:,Temperature:,Pressure:,Altitude (by pressure):");
  data.close();
}

void loop() {
  data = SD.open("MetData.txt", FILE_WRITE);
  data.print(meteoCount);
  data.print(",");
  data.print(bme.readTemperature());
  data.print(",");
  Serial.println("----------");
  Serial.print("Sicaklik:");
  Serial.println(bme.readTemperature());
  data.print(bme.readPressure()/100);
  data.print(",");
  Serial.print("Basinc:");
  Serial.println(bme.readPressure()/100);
  data.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.print("Yukseklik:");
  Serial.println(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println("----------");
  data.println("");
  data.close();  
  meteoCount++;
  
  delay(1000);
  
}
