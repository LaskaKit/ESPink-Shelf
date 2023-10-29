/*
* This example code for Temperature and Humidity SHTxx module
* is used with ESPink Shelf 2.13".
* ESPink Shelf reads temperature and humidity from SHT40 sensor 
* and shows on ePaper 2.13"
*
* SDA - GPIO21
* SCL - GPIO22
* ENABLE voltage for ePaper and I2C sensor - GPIO2 (HIGH - turn on, LOW - turn off)
*
* Made by (c) laskakit.cz 2023
*
* Libraries
* https://github.com/adafruit/Adafruit_SHT4X
* https://github.com/ZinggJM/GxEPD2
*/
 
#include <Wire.h>

/*------- SHT40 ----------*/
#include "Adafruit_SHT4x.h"

Adafruit_SHT4x sht4 = Adafruit_SHT4x();

/*------- ePaper ----------*/
#include <GxEPD2_BW.h>
#include <Fonts/FreeMonoBold12pt7b.h>

GxEPD2_BW<GxEPD2_213_T5D, GxEPD2_213_T5D::HEIGHT> display(GxEPD2_213_T5D(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4)); // GDEW0213T5D 104x212, UC8151D

/*------- Sleep time ----------*/
const int sleepDuration = 60;
 
void setup() {
  Serial.begin(115200);

  /*------- Enable voltage for ePaper and I2C sensor ----------*/
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);   // turn on the ePaper
  delay(100);

  Wire.begin(21, 22);
  while (!Serial) 
  {
    ; // wait for serial
  }

  /*------- SHT40 ----------*/
  if (! sht4.begin()) 
  {
    Serial.println("SHT4x not found");
    Serial.println("Check the connection");
    while (1) delay(1);
  }
 
  sht4.setPrecision(SHT4X_HIGH_PRECISION); // highest resolution
  sht4.setHeater(SHT4X_NO_HEATER); // no heater

  /*------- ePaper init ----------*/
  display.init(); // ePaper init
  display.setRotation(1);
  display.setTextColor(GxEPD_BLACK); // Set text color
  display.fillScreen(GxEPD_WHITE); // set the background to white (fill the buffer with value for white)
 
  /*------- read SHT40 - temperature and humidty ----------*/
  sensors_event_t humidity, temp; // temperature and humidity variables
 
  sht4.getEvent(&humidity, &temp);
  Serial.print("Temperature: "); Serial.print(temp.temperature); Serial.println(" degC");
  Serial.print("Humidity: "); Serial.print(humidity.relative_humidity); Serial.println("% rH");

  /*------- Update ePaper ----------*/
  display.setFont(&FreeMonoBold12pt7b);
  display.setCursor(5, 30);
  display.print("Teplota: "); 
  display.print(temp.temperature); 
  display.setCursor(5, 60);
  display.print("Vlhkost: "); 
  display.print(humidity.relative_humidity); 

  display.display(false);

  display.powerOff();
 
  digitalWrite(2, LOW);   // turn off the ePaper

  // sleep for 60s
  Serial.flush();
  esp_sleep_enable_timer_wakeup(sleepDuration * 1000000); 
  esp_deep_sleep_start(); 

}
 
void loop() {

}
