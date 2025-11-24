/*
* This example code for Temperature and Humidity - SHTxx module
* or Temperature and Humidity and CO2 - SCD41 module
* or Temperature and Humidity and Pressure - BME280
* with ESPink Shelf 2.13".
* ESPink Shelf reads variables and shows on ePaper 2.13" based on conencted sensor
*
* SDA - GPIO21
* SCL - GPIO22
* ENABLE voltage for ePaper and I2C sensor - GPIO2 (HIGH - turn on, LOW - turn off)
*
* Made by (c) laskakit.cz 2024
*
* Libraries
* https://github.com/adafruit/Adafruit_SHT4X
* https://github.com/sparkfun/SparkFun_SCD4x_Arduino_Library
* https://github.com/adafruit/Adafruit_BME280_Library
* https://github.com/ZinggJM/GxEPD2
*
* Compilation: if you will select 40 MHz osc instead of 240 MHz (Wi-Fi is not used)
* you reduce the own consumption by (approx) 50%
*/
 
#include <WiFi.h>
#include <Wire.h>

  // SHT40/41/45
  #include "Adafruit_SHT4x.h"
Adafruit_SHT4x sht4 = Adafruit_SHT4x();
  //SCD40/41
  #include "SparkFun_SCD4x_Arduino_Library.h"
SCD4x SCD4(SCD4x_SENSOR_SCD41);
  //BME280
  #include <Adafruit_Sensor.h>
  #include <Adafruit_BME280.h>
Adafruit_BME280 bme;

/*------- ePaper ----------*/
#include <GxEPD2_BW.h>
#include <Fonts/FreeMonoBold12pt7b.h>

//#include "Monospaced_bolditalic_70.h"
#include "Monospaced_bolditalic_50.h"
#include "Monospaced_bolditalic_30.h"
#include "Monospaced_bold_15.h"

// select the correct type of ePaper on 2.13" ESPink shelf
//GxEPD2_BW<GxEPD2_213_T5D, GxEPD2_213_T5D::HEIGHT> display(GxEPD2_213_T5D(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4));         // ESPink-Shelf-213 GDEW0213T5D -> 2.13" 104x212, UC8151D
GxEPD2_BW<GxEPD2_213_B74, GxEPD2_213_B74::HEIGHT> display(GxEPD2_213_B74(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4));     // ESPink-Shelf-213 GDEM0213B74 -> 2.13" 122x250, SSD1680 

/*------- Analog Read ----------*/
#define deviderRatio 1.769
#define ADC 34

float temperature = 0.0;
int humidity = 0;
int co2 = 0;
int pressure = 0;

uint8_t checkSensors(void);

/*------- Sleep time ----------*/
const int sleepDuration = 60;
 
void setup() {
  //adc_power_off();
  WiFi.disconnect(true);  // Disconnect from the network
  WiFi.mode(WIFI_OFF);    // Switch WiFi off
  
  Serial.begin(115200);

  /*------- Enable voltage for ePaper and I2C sensor ----------*/
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);   // turn on the ePaper
  delay(100);
  // I2C init
  Wire.begin(21, 22);
 
  /*------- Battery voltage ----------*/
  float volt = 0.0;
  // battery voltage measurement
  volt = (analogReadMilliVolts(ADC) * deviderRatio / 1000);

  /*------- ePaper init ----------*/
  display.init(); // ePaper init
  display.setRotation(1);
  display.setTextColor(GxEPD_WHITE); // Set text color
  display.fillScreen(GxEPD_WHITE); // set the background to white (fill the buffer with value for white)

  display.fillRect(0, 90, 255, 90, GxEPD_BLACK);
  display.setFont(&Monospaced_bold_15);
  display.setCursor(180, 110);
  display.print(volt);
  display.print(" V");

  if(volt < 3.4)
  {
    display.setTextColor(GxEPD_BLACK);
    display.setFont(&Monospaced_bolditalic_30);
    display.setCursor(10, 60);
    display.print("VYBITA BATERIE");
  }
  else
  {
    if(volt < 3.7)
    {
      display.setTextColor(GxEPD_WHITE);
      display.setFont(&Monospaced_bold_15);
      display.setCursor(5, 110);
      display.print("VYBITA BATERIE");
    }

    display.setTextColor(GxEPD_BLACK); // Set text color

    uint8_t sensor = checkSensors();
    /*------- Update ePaper ----------*/
    /*------- SHT40 (temperature, humidity) ----------*/
    if(sensor == 1)
    {
      display.setFont(&Monospaced_bolditalic_50);
      display.setCursor(5, 60);
      display.print(String(temperature, 1));

      display.setCursor(180, 60);
      display.print(humidity); 
    }
    /*------- SCD41 (temperature, humidity, CO2) ----------*/
    else if(sensor == 2)
    {
      display.setFont(&Monospaced_bolditalic_50);
      display.setCursor(5, 60);
      display.print(co2);

      display.setFont(&Monospaced_bolditalic_30);
      display.setCursor(165, 30);
      display.print(String(temperature, 1)); 
      display.setCursor(165, 70);
      display.print(humidity); 
    }
    /*------- BME280 (temperature, humidity, pressure) ----------*/
    else if(sensor == 3)
    {
      display.setFont(&Monospaced_bolditalic_50);
      display.setCursor(5, 60);
      display.print(String(temperature, 1));

      display.setFont(&Monospaced_bolditalic_30);
      display.setCursor(165, 30);
      display.print(String(pressure)); 
      display.setCursor(165, 70);
      display.print(humidity); 
    }
    else
    {
      display.setFont(&Monospaced_bold_15);
      display.setCursor(0, 50);
      display.print("Cidlo nenalezeno");
    }
  }
    // ePaper refresh
    display.display(false);
    // SW turn off
    display.powerOff();
    // HW turn off
    digitalWrite(2, LOW); 

    // sleep
    Serial.flush();
    esp_sleep_enable_timer_wakeup(sleepDuration * 1000000); 
    esp_deep_sleep_start(); 
}
 
void loop() {

}

uint8_t checkSensors()
{
  // Check SHT40 OR SHT41 OR SHT45
  if (!sht4.begin())
  {
    Serial.println("SHT4x not found - maybe just not connected? Otherwise check its wiring.");
  }
  else
  {
    Serial.println("SHT4x FOUND");
    sht4.setPrecision(SHT4X_LOW_PRECISION); // highest resolution
    sht4.setHeater(SHT4X_NO_HEATER); // no heater


    sensors_event_t hum, temp; // temperature and humidity variables
    sht4.getEvent(&hum, &temp);

    temperature = temp.temperature;
    humidity = hum.relative_humidity;

    return 1;
  }

  // Check SCD40 OR SCD41
  if (!SCD4.begin(false, true, false))
  {
    Serial.println("SCD41 not found - maybe just not connected? Otherwise check its wiring.");
  }
  else
  {
    Serial.println("SCD4x FOUND");
    SCD4.measureSingleShot();

    while (SCD4.readMeasurement() == false) // wait for a new data (approx 30s)
    {
      Serial.println("Waiting for first measurement...");
      delay(1000);
    }

    temperature = SCD4.getTemperature()+2;
    humidity = SCD4.getHumidity();
    co2 = SCD4.getCO2();

    return 2;
  }

  // Check BME280
  if(!bme.begin())
  {
    Serial.println("BME280 not found - maybe just not connected? Otherwise check its wiring.");
  }
  else
  {
    Serial.println("BME280 FOUND");

    temperature = bme.readTemperature();
    humidity = bme.readHumidity();
    pressure = bme.readPressure() / 100.0F;

    return 3;
  }

  return 0;
}
