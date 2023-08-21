/* Example code for LaskaKit ESPInk-Shelf
 * where are shown the date, bus departure and weather forecast
 * 
 * Board:   LaskaKit ESPink-Shelf https://www.laskakit.cz/laskakit-espink-shelf-213-esp32-e-paper/
 * Display: Good Display GDEW0213T5D         
 * 
 * Email:podpora@laskakit.cz
 * Web:laskakit.cz
 *
 *  Libraries:
 *  ArduinoJSON https://arduinojson.org/
 *  NTP https://github.com/arduino-libraries/NTPClient
 *  GxEPD2 https://github.com/ZinggJM/GxEPD2
 *
 *  Used Forecast data from https://github.com/petrbrouzda/YrNoProvider
 *
 *	What customer shall change:
 *  Bus.h -> fill your departure time, working days, saturday and sunday are split
 *  config.h -> fill your location, Wi-Fi credentials
 */



#define ENABLE_GxEPD2_GFX 0

#include <WiFi.h>
#include <HTTPClient.h>

/*------- CONFIGURATION ----------*/
#include "config.h"

/*------- Arduino JSON ----------*/
#include <ArduinoJson.h>

/*------- BUS connection ----------*/
#include "Bus.h"

/*------- NTP ----------*/
#include "time.h"

/*------- ePaper ----------*/
#include <GxEPD2_BW.h>
#include <GxEPD2_3C.h>
#include <GxEPD2_7C.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMonoBold18pt7b.h>
#include <Fonts/FreeMonoBold24pt7b.h>

GxEPD2_BW<GxEPD2_213_T5D, GxEPD2_213_T5D::HEIGHT> display(GxEPD2_213_T5D(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4)); // GDEW0213T5D 104x212, UC8151D

/*------- NTP ----------*/
struct tm timeinfo;

/*------- Arduino JSON config ----------*/
StaticJsonDocument<10000> doc;

void setup()
{
  Serial.begin(115200);
  delay(100);

  WiFi.begin(ssid, pass);
  Serial.println("Connecting");
  int count = 0;
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    count++;
    if(count >= 20) // wait max 20s, if it is not connected, go to sleep
    {
      Serial.flush();
      esp_sleep_enable_timer_wakeup(sleepDuration * 1000000); // sleep for 10 minutes
      esp_deep_sleep_start(); 
    }
  }
  Serial.println();

  // WiFi connected
  if(WiFi.status()== WL_CONNECTED)
  {
    // turn on power to display
    pinMode(2, OUTPUT);
    digitalWrite(2, HIGH);   // turn on the ePaper
    delay(1000);   
    
    display.init(); // ePaper init
    display.setRotation(0);
    display.setTextColor(GxEPD_BLACK); // Set text color
    display.fillScreen(GxEPD_WHITE); // set the background to white (fill the buffer with value for white)

	/*------- Forecast ----------*/
    updateForecastData(jsonurl);
	
    /*------- NTP ----------*/
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    
    if(!getLocalTime(&timeinfo))
    {
      Serial.flush();
      esp_sleep_enable_timer_wakeup(sleepDuration * 1000000); 
      esp_deep_sleep_start();
      Serial.println("Failed to obtain time");
      return;
    }
    Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
    Serial.println(timeinfo.tm_wday);

    display.setFont(&FreeMonoBold9pt7b);
    display.setCursor(5, 15);
    display.print(&timeinfo, "%d.%b.");
    display.setCursor(5, 30);
    display.print(&timeinfo, "%A");
	
	  /*------- BUS connection ----------*/
	  updateBUSconnectionData();

    /*------- Update ePaper ----------*/
    display.display(false);

    display.powerOff();

    digitalWrite(2, LOW);   // turn off the ePaper
  }
  
  Serial.flush();
  esp_sleep_enable_timer_wakeup(sleepDuration * 1000000); 
  esp_deep_sleep_start(); 

}


void loop()
{
}

void updateBUSconnectionData()
{
	    /*------- Bus connection ----------*/
    int firstDepartureHour = 4; // first hour of departure
    int lastDepartureHour = 22; // last hour of departure
    int maxDepartureCount = 3; // max visible departures

    /*   DO NOT CHANGE IT  */
    int currMin = timeinfo.tm_min; // current minute from NTP server
    int currHour = timeinfo.tm_hour; // current hour from NTP server
    int departureCount = 0; // temp variable
    int posY = 60; // px possition of the first bus on ePaper (Y axis)
    int posX = 5; // px possition of the first bus on ePaper (X axis)
    int posYmove = 20; // move the next departure by this px number on ePaper
    display.setCursor(posX, posY);
    display.setFont(&FreeMonoBold12pt7b);

    // if current hour is in the range of firstDepartureHour and lastDepartureHour
    if((currHour >= firstDepartureHour) && (currHour <= lastDepartureHour))
    {
      Serial.println("Following BUS connection");
      for(int i = 1; i <= 9; i++) // search BUS between 1 to 9 time slot , means firstConnectionInMinutes, secondConnectionInMinutes, ...
      {
          int minuteConnection = 0;
          
          minuteConnection = busDepartureWD[currHour-firstDepartureHour][i]; // Working day array
          if((timeinfo.tm_wday == 0) || (timeinfo.tm_wday == 6)) // if Sunday, choose different array
          {
            if(timeinfo.tm_wday == 0)
            {
              minuteConnection = busDepartureSun[currHour-firstDepartureHour][i];
              Serial.println("Sunday");
            }
            if(timeinfo.tm_wday == 6)
            {
              minuteConnection = busDepartureSat[currHour-firstDepartureHour][i];
              Serial.println("Saturday");
            }
          }
            
          if((minuteConnection) == -1) // if no connection, exit the loop 
          {
              Serial.print("No BUS connection in "); Serial.println(currHour);
              break;
          }
          else // else show folling connection
          {
              if(currMin <= (minuteConnection))
              {
                  display.setTextColor(GxEPD_BLACK);

                  char departure[10] = {0};
                  sprintf(departure, "%02d:%02d", currHour, minuteConnection);
                  display.setCursor(posX, posY);
                  display.println(departure);
                  Serial.print("Next BUS connection in "); Serial.print(currHour); Serial.print(":"); Serial.println(minuteConnection);
                  departureCount++;
                  posY = posY + posYmove;
                  if(departureCount >= maxDepartureCount) // show mayDepartureCount connection
                  {
                      break;
                  }
              }
          }
      }
    }
    // if no connection, show first morning connection
    else
    {
        display.setCursor(posX, posY);
        int minuteConnection = 0;
        minuteConnection = busDepartureWD[firstDepartureHour-firstDepartureHour][1];
        if((timeinfo.tm_wday == 0) || (timeinfo.tm_wday == 6)) // if Sunday, choose the array for Sunday
        {
          if(timeinfo.tm_wday == 0)
          {
            minuteConnection = busDepartureSun[firstDepartureHour-firstDepartureHour][1];
            Serial.println("Sunday");
          }
          if(timeinfo.tm_wday == 6)
          {
            minuteConnection = busDepartureSat[currHour-firstDepartureHour][1];
            Serial.println("Saturday");
          }
        }

        char departure[10] = {0};
        sprintf(departure, "%02d:%02d", firstDepartureHour, minuteConnection);
        display.println(departure);
        Serial.print("Next BUS connection in "); Serial.print(firstDepartureHour); Serial.print(":"); Serial.println(minuteConnection);
    }

    // if less connection than maxDepartureCount, search the connection in the next hour
    if((departureCount < maxDepartureCount) && ((currHour >= firstDepartureHour) && (currHour <= lastDepartureHour)))
    {
        currHour = currHour + 1; // current hour + 1
        currMin = 0;
        
        if((currHour >= firstDepartureHour) && (currHour <= lastDepartureHour)) // check the hour is in the range
        {
          for(int i = 1; i <= 9; i++) // search minutes of connetions (first, second, ...)
            {
              int minuteConnection = 0;
              minuteConnection = busDepartureWD[currHour-firstDepartureHour][i];
              if((timeinfo.tm_wday == 0) || (timeinfo.tm_wday == 6)) // if Sunday, choose the Sunday array
              {
                if(timeinfo.tm_wday == 0)
                {
                  minuteConnection = busDepartureSun[currHour-firstDepartureHour][i];
                  Serial.println("Sunday");
                }
                if(timeinfo.tm_wday == 6)
                {
                  minuteConnection = busDepartureSat[currHour-firstDepartureHour][i];
                  Serial.println("Saturday");
                }
              }
                
              if((minuteConnection) == -1) // if no connection in the hour+1, break it
              {
                  Serial.print("In "); Serial.print(currHour); Serial.println(" is not BUS connection");
                  break;
              }
              else // show the connection in hour+1
              {
                  if(currMin <= (minuteConnection))
                  {
                      display.setTextColor(GxEPD_BLACK);
                    
                      display.setCursor(posX, posY);
                      char departure[10] = {0};
                      sprintf(departure, "%02d:%02d", currHour, minuteConnection);
                      display.println(departure); 
                      Serial.print("Next BUS connection in "); Serial.print(currHour); Serial.print(":"); Serial.println(minuteConnection);
                      departureCount++;
                      posY = posY + posYmove;
                      currMin = (minuteConnection);
                      if(departureCount >= maxDepartureCount)
                      {
                          break;
                      }
                  }
              }
            }
        }
        else // if no connection, choose the first morning connection
        {
          display.setCursor(posX, posY);
          int minuteConnection = 0;
          minuteConnection = busDepartureWD[firstDepartureHour-firstDepartureHour][1];
          if((timeinfo.tm_wday == 0) || (timeinfo.tm_wday == 6)) // if Sunday, choose the Sunday array
          {
            if(timeinfo.tm_wday == 0)
            {
              minuteConnection = busDepartureSun[firstDepartureHour-firstDepartureHour][1];
              Serial.println("Sunday");
            }
            if(timeinfo.tm_wday == 6)
            {
              minuteConnection = busDepartureSat[currHour-firstDepartureHour][1];
              Serial.println("Saturday");
            }
          }

          char departure[10] = {0};
          sprintf(departure, "%02d:%02d", firstDepartureHour, minuteConnection);
          display.println(departure);
          Serial.print("Next BUS connection in "); Serial.print(firstDepartureHour); Serial.print(":"); Serial.println(minuteConnection);
        }
    }
    departureCount = 0; // clear temp variable 
}

void updateForecastData(const char *URL) {
  HTTPClient http;
  http.begin(URL);

  int httpCode = http.GET();
  if (httpCode == HTTP_CODE_OK) {
    int err = jsonDecoder(http.getString(), true);
    switch (err) {
      case 0:
        Serial.println("JSON parsing done!");
        break;
      case -1:
        Serial.println("Wrong JSON format");
        break;
      case -2:
        Serial.println("Low memory, increase the StaticJsonDocument");
        break;
      case -3:
        Serial.println("Error during parsing of JSON");
        break;
    }
  }
  http.end();
}

int jsonDecoder(String s, bool log) {
  DeserializationError e = deserializeJson(doc, s);
  if (e) {
    if (e == DeserializationError::InvalidInput) {
      return -1;
    } else if (e == DeserializationError::NoMemory) {
      return -2;
    } else {
      return -3;
    }
  } else {

    int temp_min = doc["sections"][0]["temp_min"]; // decimal number is ignored
    int temp_max = doc["sections"][0]["temp_max"]; // decimal number is ignored
    float rain_sum = doc["sections"][0]["rain_sum"];

    Serial.print("Temp min: "); Serial.println(temp_min);
    Serial.print("Temp max: "); Serial.println(temp_max);
    Serial.print("Rain_sum: "); Serial.println(rain_sum); 

    /*------- Show weather forecast ----------*/
    display.setCursor(5, 130);
    display.setFont(&FreeMonoBold12pt7b);
    display.print(temp_min);
    display.setFont(&FreeMonoBold9pt7b);
    display.print(" degC");

    display.setCursor(5, 160);
    display.setFont(&FreeMonoBold12pt7b);
    display.print(temp_max);
    display.setFont(&FreeMonoBold9pt7b);
    display.print(" degC");

    display.setCursor(5, 190);
    display.setFont(&FreeMonoBold12pt7b);
    display.print(rain_sum);
    display.setFont(&FreeMonoBold9pt7b);
    display.print(" mm");

    }
    return 0;
}
