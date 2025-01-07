
/* Display test for LaskaKit ESPink-Shelf-213 ESP32 e-Paper
 * example from GxEPD2 library is used
 * 
 * Board:   LaskaKit ESPink-Shelf-2.9 ESP32 e-Paper     https://www.laskakit.cz/laskakit-espink-shelf-2-9-esp32-e-paper/   
 *
 * Email:podpora@laskakit.cz
 * Web:laskakit.cz
 */

// Display Library example for SPI e-paper panels from Dalian Good Display.
// Requires Adafruit_GFX and https://github.com/ZinggJM/GxEPD2 Author: Jean-Marc Zingg

#define ENABLE_GxEPD2_GFX 0

#include <GxEPD2_4C.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include "bitmaps/Bitmaps168x384.h" // 2.9"  b/w

#define DC    17 
#define RST   16  
#define BUSY  4 
#define POWER 2

#define SLEEP_SEC 15         // Measurement interval (seconds)

GxEPD2_4C<GxEPD2_290c_GDEY029F51H, GxEPD2_290c_GDEY029F51H::HEIGHT> display(GxEPD2_290c_GDEY029F51H(SS, DC, RST, BUSY)); // ESPink-Shelf-2.9 GDEY029F51H  168x384, JD79667 (FPC-H004 22.03.24)

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println("setup");
  delay(100);

// turn on power to display
  pinMode(POWER, OUTPUT);
  digitalWrite(POWER, HIGH);   // turn the Display on (HIGH is the voltage level)
  Serial.println("Display power ON");
  delay(1000);   
  
  display.init(115200, true, 2, false); // USE THIS for Waveshare boards with "clever" reset circuit, 2ms reset pulse
  if (display.pages() > 1)
  {
    delay(100);
    Serial.print("pages = "); Serial.print(display.pages()); Serial.print(" page height = "); Serial.println(display.pageHeight());
    delay(1000);
  }
  helloWorld();
  delay(1000);
  display.fillScreen(GxEPD_WHITE);  // white background
  display.display(false); // update 

  delay(100);
  digitalWrite(POWER, LOW); // disable power supply for ePaper

  // deep sleep mode
  esp_sleep_enable_timer_wakeup(300 * 1000000);
  delay(200);
  esp_deep_sleep_start();

  display.powerOff();

  Serial.println("setup done");

}


void loop()
{
}

const char HelloWorld[] = "Hello World!";
const char HelloArduino[] = "Hello Arduino!";
const char HelloEpaper[] = "Hello E-Paper!";

void helloWorld()
{
  //Serial.println("helloWorld");
  display.setRotation(1);
  display.setFont(&FreeMonoBold9pt7b);
  if (display.epd2.WIDTH < 104) display.setFont(0);
  display.setTextColor(GxEPD_BLACK);
  int16_t tbx, tby; uint16_t tbw, tbh;
  display.getTextBounds(HelloWorld, 0, 0, &tbx, &tby, &tbw, &tbh);
  // center bounding box by transposition of origin:
  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  uint16_t y = ((display.height() - tbh) / 2) - tby;
  display.setFullWindow();
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(x, y);
    display.print(HelloWorld);
  }
  while (display.nextPage());
  Serial.println("helloWorld done");
}