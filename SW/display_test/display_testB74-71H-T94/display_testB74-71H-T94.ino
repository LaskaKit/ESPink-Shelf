
/* Display test for LaskaKit ESPink-Shelf-213 ESP32 e-Paper
 * example from GxEPD2 library is used
 * 
 * Board:   LaskaKit ESPink-Shelf-2.13 ESP32 e-Paper    https://www.laskakit.cz/laskakit-espink-shelf-213-esp32-e-paper/   
 *          LaskaKit ESPink-Shelf-2.9 ESP32 e-Paper     https://www.laskakit.cz/laskakit-espink-shelf-2-9-esp32-e-paper/   

 * Email:podpora@laskakit.cz
 * Web:laskakit.cz
 */

// Display Library example for SPI e-paper panels from Dalian Good Display.
// Requires Adafruit_GFX and https://github.com/ZinggJM/GxEPD2 Author: Jean-Marc Zingg

#define ENABLE_GxEPD2_GFX 0

#include <GxEPD2_BW.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include "bitmaps/Bitmaps168x384.h" // 2.9"  b/w
#include "bitmaps/Bitmaps128x296.h" // 2.9"  b/w
#include "bitmaps/Bitmaps128x250.h" // 2.13" b/w

#define DC    17 
#define RST   16  
#define BUSY  4 
#define POWER 2

#define SLEEP_SEC 15         // Measurement interval (seconds)
// select one and a LaskaKit ESPink-Shelf Boards:
// Black and white e-papers
GxEPD2_BW<GxEPD2_213_B74, GxEPD2_213_B74::HEIGHT> display(GxEPD2_213_B74(SS, DC, RST, BUSY));         // ESPink-Shelf-2.13 GDEM0213B74 -> 2.13" 122x250, SSD1680 
//GxEPD2_BW<GxEPD2_290_GDEY029T94, GxEPD2_290_GDEY029T94::HEIGHT> display(GxEPD2_290_GDEY029T94(SS, DC, RST, BUSY));  // ESPink-Shelf-2.9 GDEY029T94  128x296, SSD1680, (FPC-A005 20.06.15)
//GxEPD2_BW<GxEPD2_290_GDEY029T71H, GxEPD2_290_GDEY029T71H::HEIGHT> display(GxEPD2_290_GDEY029T71H(SS, DC, RST, BUSY)); // GDEY029T71H 168x384, SSD1685, (FPC-H004 22.03.24)

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
  drawBitmaps();
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
  //Serial.println("helloWorld done");
}


void drawBitmaps()
{
  display.setRotation(0);
  display.setFullWindow();
#ifdef _GxBitmaps80x128_H_
  drawBitmaps80x128();
#endif
#ifdef _GxBitmaps152x152_H_
  drawBitmaps152x152();
#endif
#ifdef _GxBitmaps104x212_H_
  drawBitmaps104x212();
#endif
#ifdef _GxBitmaps200x200_H_
  drawBitmaps200x200();
#endif
#ifdef _GxBitmaps128x250_H_
  drawBitmaps128x250();
#endif
#ifdef _GxBitmaps128x296_H_
  drawBitmaps128x296();
#endif
#ifdef _GxBitmaps168x384_H_
  drawBitmaps168x384();
#endif
#ifdef _GxBitmaps152x296_H_
  drawBitmaps152x296();
#endif
#ifdef _GxBitmaps240x320_H_
  drawBitmaps240x320();
#endif
#ifdef _GxBitmaps176x264_H_
  drawBitmaps176x264();
#endif
#ifdef _GxBitmaps240x416_H_
  drawBitmaps240x416();
#endif
#ifdef _GxBitmaps400x300_H_
  drawBitmaps400x300();
#endif
#ifdef _GxBitmaps640x384_H_
  drawBitmaps640x384();
#endif
#ifdef _GxBitmaps648x480_H_
  drawBitmaps648x480();
#endif
#if defined(ESP32) && defined(_GxBitmaps800x276_H_)
  drawBitmaps800x276();
#endif
#ifdef _GxBitmaps800x480_H_
  drawBitmaps800x480();
#endif
#ifdef _WS_Bitmaps800x600_H_
  drawBitmaps800x600();
#endif
#if defined(ESP32) && defined(_GxBitmaps960x640_H_)
  drawBitmaps960x640();
#endif
#if defined(ESP32) && defined(_GxBitmaps960x680_H_)
  drawBitmaps960x680();
#endif
#if defined(ESP32) && defined(_GxBitmaps1304x984_H_)
  drawBitmaps1304x984();
#endif
  // 3-color
#ifdef _GxBitmaps3c104x212_H_
  drawBitmaps3c104x212();
#endif
#ifdef _GxBitmaps3c200x200_H_
  drawBitmaps3c200x200();
#endif
#ifdef _GxBitmaps3c128x250_H_
  drawBitmaps3c128x250();
#endif
#ifdef _GxBitmaps3c128x296_H_
  drawBitmaps3c128x296();
#endif
#ifdef _GxBitmaps3c152x296_H_
  drawBitmaps3c152x296();
#endif
#ifdef _GxBitmaps3c176x264_H_
  drawBitmaps3c176x264();
#endif
#ifdef _GxBitmaps3c400x300_H_
  drawBitmaps3c400x300();
#endif
#ifdef _GxBitmaps3c648x480_H_
  drawBitmaps3c648x480();
#endif
#ifdef _GxBitmaps3c800x480_H_
  drawBitmaps3c800x480();
#endif
#ifdef _GxBitmaps3c880x528_H_
  drawBitmaps3c880x528();
#endif
#if defined(ESP32) && defined(_GxBitmaps3c960x640_H_)
  drawBitmaps3c960x640();
#endif
#if defined(ESP32) && defined(_GxBitmaps3c960x680_H_)
  drawBitmaps3c960x680();
#endif
#if defined(ESP32) && defined(_GxBitmaps1360x480_H_)
  drawBitmaps1360x480();
#endif
  // 3-color
#if defined(ESP32) && defined(_GxBitmaps3c800x276_H_)
  drawBitmaps3c800x276();
#endif
  // 4-color
#if defined(_GxBitmaps4c128x250_H_)
  drawBitmaps4c128x250();
#endif
#if defined(_WS_Bitmaps4c168x168_H_)
  drawBitmaps4c168x168();
#endif
#if defined(_GxBitmaps4c168x384_H_)
  drawBitmaps4c168x384();
#endif
#if defined(_GxBitmaps4c184x360_H_)
  drawBitmaps4c184x360();
#endif
#if defined(_GxBitmaps4c400x300_H_)
  drawBitmaps4c400x300();
#endif
#if defined(_GxBitmaps4c960x640_H_)
  drawBitmaps4c960x640();
#endif
#if defined(ESP32) && defined(_GxBitmaps4c792x272_H_)
  drawBitmaps4c792x272();
#endif
  // 7-color
#if defined(_GxBitmaps7c600x448_H_)
  drawBitmaps7c600x448();
#endif
#if defined(_WS_Bitmaps7c192x143_H_)
  drawBitmaps7c192x143();
#endif
#if defined(_GxBitmaps7c800x480_H_)
  drawBitmaps7c800x480();
#endif
#if defined(_WS_Bitmaps7c300x180_H_)
  drawBitmaps7c300x180();
#endif
#if defined(ESP32) && defined(_GxBitmaps3c1304x984_H_)
  drawBitmaps3c1304x984();
#endif
}

#ifdef _GxBitmaps80x128_H_
void drawBitmaps80x128()
{
#if !defined(__AVR)
  const unsigned char* bitmaps[] =
  {
    Bitmap80x128_1, Bitmap80x128_2, Bitmap80x128_3, Bitmap80x128_4, Bitmap80x128_5
  };
#else
  const unsigned char* bitmaps[] =
  {
    Bitmap80x128_1, Bitmap80x128_2, Bitmap80x128_3, Bitmap80x128_4, Bitmap80x128_5
  };
#endif
  if ((display.epd2.WIDTH == 80) && (display.epd2.HEIGHT == 128))
  {
    for (uint16_t i = 0; i < sizeof(bitmaps) / sizeof(char*); i++)
    {
      display.firstPage();
      do
      {
        display.fillScreen(GxEPD_WHITE);
        display.drawInvertedBitmap(0, 0, bitmaps[i], 80, 128, GxEPD_BLACK);
      }
      while (display.nextPage());
      delay(2000);
    }
    display.firstPage();
    do
    {
      display.fillScreen(GxEPD_WHITE);
      display.drawBitmap(0, 0, WS_Bitmap80x128, 80, 128, GxEPD_BLACK);
    }
    while (display.nextPage());
    delay(2000);
  }
}
#endif

#ifdef _GxBitmaps152x152_H_
void drawBitmaps152x152()
{
#if !defined(__AVR)
  const unsigned char* bitmaps[] =
  {
    Bitmap152x152_1, Bitmap152x152_2, Bitmap152x152_3
  };
#else
  const unsigned char* bitmaps[] =
  {
    Bitmap152x152_1, Bitmap152x152_2, Bitmap152x152_3
  };
#endif
  if ((display.epd2.WIDTH == 152) && (display.epd2.HEIGHT == 152))
  {
    for (uint16_t i = 0; i < sizeof(bitmaps) / sizeof(char*); i++)
    {
      display.firstPage();
      do
      {
        display.fillScreen(GxEPD_WHITE);
        display.drawInvertedBitmap(0, 0, bitmaps[i], 152, 152, GxEPD_BLACK);
      }
      while (display.nextPage());
      delay(2000);
    }
  }
}
#endif

#ifdef _GxBitmaps200x200_H_
void drawBitmaps200x200()
{
#if defined(ARDUINO_AVR_PRO)
  const unsigned char* bitmaps[] =
  {
    logo200x200
  };
#elif defined(__AVR)
  const unsigned char* bitmaps[] =
  {
    logo200x200, //first200x200
  };
#elif defined(_BOARD_GENERIC_STM32F103C_H_) || defined(STM32F1xx)
  const unsigned char* bitmaps[] =
  {
    logo200x200, first200x200, second200x200, third200x200, //fourth200x200, fifth200x200, sixth200x200, senventh200x200, eighth200x200
  };
#else
  const unsigned char* bitmaps[] =
  {
    logo200x200, first200x200, second200x200, third200x200, fourth200x200, fifth200x200, sixth200x200, senventh200x200, eighth200x200
    //logo200x200, first200x200, second200x200, fourth200x200, third200x200, fifth200x200, sixth200x200, senventh200x200, eighth200x200 // ED037TC1 test
  };
#endif
  if (display.epd2.hasColor) return; // to avoid many long refreshes
  if ((display.epd2.WIDTH == 200) && (display.epd2.HEIGHT == 200) && !display.epd2.hasColor)
  {
    bool m = display.mirror(true);
    for (uint16_t i = 0; i < sizeof(bitmaps) / sizeof(char*); i++)
    {
      display.firstPage();
      do
      {
        display.fillScreen(GxEPD_WHITE);
        display.drawInvertedBitmap(0, 0, bitmaps[i], 200, 200, GxEPD_BLACK);
      }
      while (display.nextPage());
      delay(2000);
    }
    display.mirror(m);
  }
  //else
  {
    bool mirror_y = (display.epd2.panel != GxEPD2::GDE0213B1);
    display.clearScreen(); // use default for white
    int16_t x = (int16_t(display.epd2.WIDTH) - 200) / 2;
    int16_t y = (int16_t(display.epd2.HEIGHT) - 200) / 2;
    for (uint16_t i = 0; i < sizeof(bitmaps) / sizeof(char*); i++)
    {
      display.drawImage(bitmaps[i], x, y, 200, 200, false, mirror_y, true);
      delay(2000);
    }
  }
  bool mirror_y = (display.epd2.panel != GxEPD2::GDE0213B1);
  for (uint16_t i = 0; i < sizeof(bitmaps) / sizeof(char*); i++)
  {
    int16_t x = -60;
    int16_t y = -60;
    for (uint16_t j = 0; j < 10; j++)
    {
      display.writeScreenBuffer(); // use default for white
      display.writeImage(bitmaps[i], x, y, 200, 200, false, mirror_y, true);
      display.refresh(true);
      if (display.epd2.hasFastPartialUpdate)
      {
        // for differential update: set previous buffer equal to current buffer in controller
        display.epd2.writeScreenBufferAgain(); // use default for white
        display.epd2.writeImageAgain(bitmaps[i], x, y, 200, 200, false, mirror_y, true);
      }
      delay(2000);
      x += display.epd2.WIDTH / 4;
      y += display.epd2.HEIGHT / 4;
      if ((x >= int16_t(display.epd2.WIDTH)) || (y >= int16_t(display.epd2.HEIGHT))) break;
    }
    if (!display.epd2.hasFastPartialUpdate) break; // comment out for full show
    break; // comment out for full show
  }
  display.writeScreenBuffer(); // use default for white
  display.writeImage(bitmaps[0], int16_t(0), 0, 200, 200, false, mirror_y, true);
  display.writeImage(bitmaps[0], int16_t(int16_t(display.epd2.WIDTH) - 200), int16_t(display.epd2.HEIGHT) - 200, 200, 200, false, mirror_y, true);
  display.refresh(true);
  // for differential update: set previous buffer equal to current buffer in controller
  display.epd2.writeScreenBufferAgain(); // use default for white
  display.epd2.writeImageAgain(bitmaps[0], int16_t(0), 0, 200, 200, false, mirror_y, true);
  display.epd2.writeImageAgain(bitmaps[0], int16_t(int16_t(display.epd2.WIDTH) - 200), int16_t(display.epd2.HEIGHT) - 200, 200, 200, false, mirror_y, true);
  delay(2000);
}
#endif

#ifdef _GxBitmaps104x212_H_
void drawBitmaps104x212()
{
#if !defined(__AVR)
  const unsigned char* bitmaps[] =
  {
    WS_Bitmap104x212, Bitmap104x212_1, Bitmap104x212_2, Bitmap104x212_3
  };
#else
  const unsigned char* bitmaps[] =
  {
    WS_Bitmap104x212, Bitmap104x212_1, Bitmap104x212_2, Bitmap104x212_3
  };
#endif
  if ((display.epd2.WIDTH == 104) && (display.epd2.HEIGHT == 212) && !display.epd2.hasColor)
  {
    for (uint16_t i = 0; i < sizeof(bitmaps) / sizeof(char*); i++)
    {
      display.firstPage();
      do
      {
        display.fillScreen(GxEPD_WHITE);
        display.drawBitmap(0, 0, bitmaps[i], 104, 212, GxEPD_BLACK);
      }
      while (display.nextPage());
      delay(2000);
    }
  }
}
#endif

#ifdef _GxBitmaps128x250_H_
void drawBitmaps128x250()
{
#if !defined(__AVR)
  const unsigned char* bitmaps[] =
  {
    Bitmap128x250_1, logo128x250, first128x250, second128x250, third128x250
  };
#else
  const unsigned char* bitmaps[] =
  {
    Bitmap128x250_1, logo128x250, first128x250, second128x250, third128x250
  };
#endif
  if ((display.epd2.WIDTH == 128) && (display.epd2.HEIGHT == 250) && !display.epd2.hasColor)
  {
    bool m = display.mirror(true);
    for (uint16_t i = 0; i < sizeof(bitmaps) / sizeof(char*); i++)
    {
      display.firstPage();
      do
      {
        display.fillScreen(GxEPD_WHITE);
        display.drawInvertedBitmap(0, 0, bitmaps[i], 128, 250, GxEPD_BLACK);
      }
      while (display.nextPage());
      delay(2000);
    }
    display.mirror(m);
  }
}
#endif

#ifdef _GxBitmaps128x296_H_
void drawBitmaps128x296()
{
#if !defined(__AVR)
  const unsigned char* bitmaps[] =
  {
    Bitmap128x296_1, logo128x296, first128x296, second128x296, third128x296
  };
#else
  const unsigned char* bitmaps[] =
  {
    Bitmap128x296_1, logo128x296 //, first128x296, second128x296, third128x296
  };
#endif
  if ((display.epd2.WIDTH == 128) && (display.epd2.HEIGHT == 296) && !display.epd2.hasColor)
  {
    bool m = display.mirror(true);
    for (uint16_t i = 0; i < sizeof(bitmaps) / sizeof(char*); i++)
    {
      display.firstPage();
      do
      {
        display.fillScreen(GxEPD_WHITE);
        display.drawInvertedBitmap(0, 0, bitmaps[i], 128, 296, GxEPD_BLACK);
      }
      while (display.nextPage());
      delay(2000);
    }
    display.mirror(m);
  }
}
#endif

#ifdef _GxBitmaps168x384_H_
void drawBitmaps168x384()
{
#if !defined(__AVR)
  const unsigned char* bitmaps[] =
  {
    Bitmap168x384_1, Bitmap168x384_2, Bitmap168x384_3, Bitmap168x384_4, Bitmap168x384_5
  };
#else
  const unsigned char* bitmaps[] =
  {
    Bitmap168x384_1
  };
#endif
  if ((display.epd2.WIDTH == 168) && (display.epd2.HEIGHT == 384) && !display.epd2.hasColor)
  {
    bool mirrored = display.mirror(true);
    for (uint16_t i = 0; i < sizeof(bitmaps) / sizeof(char*); i++)
    {
      display.firstPage();
      do
      {
        display.fillScreen(GxEPD_WHITE);
        display.drawInvertedBitmap(0, 0, bitmaps[i], 168, 384, GxEPD_BLACK);
      }
      while (display.nextPage());
      delay(2000);
    }
    display.mirror(mirrored);
  }
}
#endif

#ifdef _GxBitmaps152x296_H_
void drawBitmaps152x296()
{
#if !defined(__AVR)
  const unsigned char* bitmaps[] =
  {
    Bitmap152x296_1, Bitmap152x296_2, Bitmap152x296_3
  };
#else
  const unsigned char* bitmaps[] =
  {
    Bitmap152x296_1, Bitmap152x296_2, Bitmap152x296_3
  };
#endif
  if ((display.epd2.WIDTH == 152) && (display.epd2.HEIGHT == 296) && !display.epd2.hasColor)
  {
    for (uint16_t i = 0; i < sizeof(bitmaps) / sizeof(char*); i++)
    {
      display.firstPage();
      do
      {
        display.fillScreen(GxEPD_WHITE);
        display.drawInvertedBitmap(0, 0, bitmaps[i], 152, 296, GxEPD_BLACK);
      }
      while (display.nextPage());
      delay(2000);
    }
  }
}
#endif

#ifdef _GxBitmaps240x320_H_
void drawBitmaps240x320()
{
#if !defined(__AVR)
  const unsigned char* bitmaps[] =
  {
    Bitmap240x320_1, Bitmap240x320_2, Bitmap240x320_3, Bitmap240x320_4, Bitmap240x320_5
  };
#else
  const unsigned char* bitmaps[] =
  {
    Bitmap240x320_1, Bitmap240x320_2
  };
#endif
  if ((display.epd2.WIDTH == 240) && (display.epd2.HEIGHT == 320) && !display.epd2.hasColor)
  {
    for (uint16_t i = 0; i < sizeof(bitmaps) / sizeof(char*); i++)
    {
      display.firstPage();
      do
      {
        display.fillScreen(GxEPD_WHITE);
        display.drawInvertedBitmap(0, 0, bitmaps[i], 240, 320, GxEPD_BLACK);
      }
      while (display.nextPage());
      delay(2000);
    }
  }
}
#endif

#ifdef _GxBitmaps176x264_H_
void drawBitmaps176x264()
{
#if !defined(__AVR)
  const unsigned char* bitmaps[] =
  {
    Bitmap176x264_1, Bitmap176x264_2, Bitmap176x264_3, Bitmap176x264_4, Bitmap176x264_5
  };
#else
  const unsigned char* bitmaps[] =
  {
    Bitmap176x264_1, Bitmap176x264_2 //, Bitmap176x264_3, Bitmap176x264_4, Bitmap176x264_5
  };
#endif
  if ((display.epd2.WIDTH == 176) && (display.epd2.HEIGHT == 264) && !display.epd2.hasColor)
  {
    for (uint16_t i = 0; i < sizeof(bitmaps) / sizeof(char*); i++)
    {
      display.firstPage();
      do
      {
        display.fillScreen(GxEPD_WHITE);
        display.drawInvertedBitmap(0, 0, bitmaps[i], 176, 264, GxEPD_BLACK);
      }
      while (display.nextPage());
      delay(2000);
    }
  }
}
#endif

#ifdef _GxBitmaps240x416_H_
void drawBitmaps240x416()
{
#if !defined(__AVR)
  const unsigned char* bitmaps[] =
  {
    Bitmap240x416_1, Bitmap240x416_2, Bitmap240x416_3
  };
#else
  const unsigned char* bitmaps[] =
  {
    Bitmap240x460_1, Bitmap240x460_2, Bitmap240x460_3
  };
#endif
  if ((display.epd2.WIDTH == 240) && (display.epd2.HEIGHT == 416) && !display.epd2.hasColor)
  {
    for (uint16_t i = 0; i < sizeof(bitmaps) / sizeof(char*); i++)
    {
      display.firstPage();
      do
      {
        display.fillScreen(GxEPD_WHITE);
        display.drawInvertedBitmap(0, 0, bitmaps[i], 240, 416, GxEPD_BLACK);
      }
      while (display.nextPage());
      delay(2000);
    }
  }
}
#endif

#ifdef _GxBitmaps400x300_H_
void drawBitmaps400x300()
{
#if !defined(__AVR)
  const unsigned char* bitmaps[] =
  {
    Bitmap400x300_1, Bitmap400x300_2
  };
#else
  const unsigned char* bitmaps[] = {}; // not enough code space
#endif
  if ((display.epd2.WIDTH == 400) && (display.epd2.HEIGHT == 300) && !display.epd2.hasColor)
  {
    for (uint16_t i = 0; i < sizeof(bitmaps) / sizeof(char*); i++)
    {
      display.firstPage();
      do
      {
        display.fillScreen(GxEPD_WHITE);
        display.drawInvertedBitmap(0, 0, bitmaps[i], 400, 300, GxEPD_BLACK);
      }
      while (display.nextPage());
      delay(2000);
    }
  }
}
#endif

#ifdef _GxBitmaps640x384_H_
void drawBitmaps640x384()
{
#if !defined(__AVR)
  const unsigned char* bitmaps[] =
  {
    Bitmap640x384_1, Bitmap640x384_2
  };
#else
  const unsigned char* bitmaps[] = {}; // not enough code space
#endif
  if ((display.epd2.WIDTH == 640) && (display.epd2.HEIGHT == 384))
  {
    for (uint16_t i = 0; i < sizeof(bitmaps) / sizeof(char*); i++)
    {
      display.firstPage();
      do
      {
        display.fillScreen(GxEPD_WHITE);
        display.drawInvertedBitmap(0, 0, bitmaps[i], 640, 384, GxEPD_BLACK);
      }
      while (display.nextPage());
      delay(2000);
    }
  }
}
#endif

#ifdef _GxBitmaps648x480_H_
void drawBitmaps648x480()
{
#if !defined(__AVR)
  const unsigned char* bitmaps[] =
  {
    Bitmap648x480_1, Bitmap648x480_2, Bitmap648x480_3
  };
#else
  const unsigned char* bitmaps[] = {}; // not enough code space
#endif
  if ((display.epd2.WIDTH == 648) && (display.epd2.HEIGHT == 480) && !display.epd2.hasColor)
  {
    for (uint16_t i = 0; i < sizeof(bitmaps) / sizeof(char*); i++)
    {
      display.firstPage();
      do
      {
        display.fillScreen(GxEPD_WHITE);
        display.drawBitmap(0, 0, bitmaps[i], 648, 480, GxEPD_BLACK);
      }
      while (display.nextPage());
      delay(2000);
    }
  }
}
#endif

#if defined(ESP32) && defined(_GxBitmaps800x276_H_)
void drawBitmaps800x276()
{
  if ((display.epd2.WIDTH == 792) && (display.epd2.HEIGHT == 272) && !display.epd2.hasColor)
  {
    display.drawImage(Bitmap800x276_1, 0, 0, 800, 272, true, false, true); delay(2000);
    display.drawImage(Bitmap800x276_2, 0, 0, 800, 272, true, false, true); delay(2000);
    display.drawImage(Bitmap800x276_3, 0, 0, 800, 272, true, false, true); delay(2000);
    display.clearScreen();
    int16_t wp = display.epd2.WIDTH / 5;
    int16_t hp = display.epd2.HEIGHT / 5;
    for (int16_t i = 0; i < 5; i++)
    {
      for (int16_t j = 0; j < 5; j++)
      {
        display.writeImagePart(Bitmap800x276_1, i * wp, j * hp, 800, 272, i * wp, j * hp, wp, hp, true, false, true);
        display.refresh(true);
        display.epd2.writeImagePartAgain(Bitmap800x276_1, i * wp, j * hp, 800, 272, i * wp, j * hp, wp, hp, true, false, true);
        delay(500);
      }
    }
  }
}
#endif

#ifdef _GxBitmaps800x480_H_
void drawBitmaps800x480()
{
#if defined(ARDUINO_UNOR4_MINIMA) || defined(ARDUINO_UNOR4_WIFI)
  const unsigned char* bitmaps[] =
  {
    Bitmap800x480_3, Bitmap800x480_4
  };
#elif !defined(__AVR)
  const unsigned char* bitmaps[] =
  {
    Bitmap800x480_1, Bitmap800x480_2, Bitmap800x480_3, Bitmap800x480_4
  };
#else
  const unsigned char* bitmaps[] = {}; // not enough code space
#endif
  if ((display.epd2.WIDTH == 800) && (display.epd2.HEIGHT == 480) && !display.epd2.hasColor)
  {
    for (uint16_t i = 0; i < sizeof(bitmaps) / sizeof(char*); i++)
    {
      display.firstPage();
      do
      {
        display.fillScreen(GxEPD_WHITE);
        display.drawBitmap(0, 0, bitmaps[i], 800, 480, GxEPD_BLACK);
      }
      while (display.nextPage());
      delay(2000);
    }
    if ((display.epd2.panel == GxEPD2::GDEW075T7) || (display.epd2.panel == GxEPD2::GDEY075T7))
    {
      // avoid ghosting caused by OTP waveform
      display.clearScreen();
      display.refresh(false); // full update
    }
  }
}
#endif

#if defined(ESP32) && defined(_GxBitmaps960x640_H_)
void drawBitmaps960x640()
{
  if ((display.epd2.WIDTH == 960) && (display.epd2.HEIGHT == 640) && !display.epd2.hasColor)
  {
    display.drawImage(Bitmap960x640_1, 0, 0, 960, 640, false, true, true); delay(5000);
    display.drawImage(Bitmap960x640_2, 0, 0, 960, 640, false, true, true); delay(5000);
    display.drawImage(Bitmap960x640_3, 0, 0, 960, 640, false, true, true); delay(5000);
  }
}
#endif

#if defined(ESP32) && defined(_GxBitmaps960x680_H_)
void drawBitmaps960x680()
{
  if ((display.epd2.WIDTH == 960) && (display.epd2.HEIGHT == 680) && !display.epd2.hasColor)
  {
    display.drawImage(Bitmap960x680_1, 0, 0, 960, 680, false, true, true); delay(5000);
    display.drawImage(Bitmap960x680_2, 0, 0, 960, 680, false, true, true); delay(5000);
  }
}
#endif

#ifdef _WS_Bitmaps800x600_H_
void drawBitmaps800x600()
{
#if defined(ESP8266) || defined(ESP32)
  if ((display.epd2.panel == GxEPD2::ED060SCT) || (display.epd2.panel == GxEPD2::ED060KC1) || (display.epd2.panel == GxEPD2::ED078KC2))
  {
    //    Serial.print("sizeof(WS_zoo_800x600) is "); Serial.println(sizeof(WS_zoo_800x600));
    display.drawNative(WS_zoo_800x600, 0, 0, 0, 800, 600, false, false, true);
    delay(2000);
    //    Serial.print("sizeof(WS_pic_1200x825) is "); Serial.println(sizeof(WS_pic_1200x825));
    //    display.drawNative((const uint8_t*)WS_pic_1200x825, 0, 0, 0, 1200, 825, false, false, true);
    //    delay(2000);
    //    Serial.print("sizeof(WS_acaa_1024x731) is "); Serial.println(sizeof(WS_acaa_1024x731));
    //    display.drawNative(WS_acaa_1024x731, 0, 0, 0, 1024, 731, false, false, true);
    //    delay(2000);
  }
#endif
}
#endif

#if defined(ESP32) && defined(_GxBitmaps1304x984_H_)
void drawBitmaps1304x984()
{
  if (display.epd2.panel == GxEPD2::GDEW1248T3)
  {
    display.drawImage(Bitmap1304x984, 0, 0, display.epd2.WIDTH, display.epd2.HEIGHT, false, false, true);
  }
}
#endif

#if defined(ESP32) && defined(_GxBitmaps1360x480_H_)
void drawBitmaps1360x480()
{
  if (display.epd2.panel == GxEPD2::GDEM1085T51)
  {
    display.drawImage(Bitmap1360x480_1, 0, 0, display.epd2.WIDTH, display.epd2.HEIGHT, false, false, true);
    delay(2000);
    display.drawImage(Bitmap1360x480_p1, 0, 0, display.epd2.WIDTH, display.epd2.HEIGHT, false, false, true);
    delay(1000);
    display.drawImage(Bitmap1360x480_p2, 0, 0, display.epd2.WIDTH, display.epd2.HEIGHT, false, false, true);
    delay(1000);
    display.drawImage(Bitmap1360x480_p3, 0, 0, display.epd2.WIDTH, display.epd2.HEIGHT, false, false, true);
    delay(1000);
    display.clearScreen();
    int16_t wp = display.epd2.WIDTH / 5;
    int16_t hp = display.epd2.HEIGHT / 5;
    for (int16_t i = 0; i < 5; i++)
    {
      for (int16_t j = 0; j < 5; j++)
      {
        display.writeImagePart(Bitmap1360x480_1, i * wp, j * hp, 1360, 480, i * wp, j * hp, wp, hp, false, false, true);
        display.refresh(true);
        delay(500);
      }
    }
  }
}
#endif

struct bitmap_pair
{
  const unsigned char* black;
  const unsigned char* red;
};

#ifdef _GxBitmaps3c200x200_H_
void drawBitmaps3c200x200()
{
  bitmap_pair bitmap_pairs[] =
  {
    //{Bitmap3c200x200_black, Bitmap3c200x200_red},
    {WS_Bitmap3c200x200_black, WS_Bitmap3c200x200_red}
  };
  if (display.epd2.panel == GxEPD2::GDEW0154Z04)
  {
    display.firstPage();
    do
    {
      display.fillScreen(GxEPD_WHITE);
      // Bitmap3c200x200_black has 2 bits per pixel
      // taken from Adafruit_GFX.cpp, modified
      int16_t byteWidth = (display.epd2.WIDTH + 7) / 8; // Bitmap scanline pad = whole byte
      uint8_t byte = 0;
      for (int16_t j = 0; j < display.epd2.HEIGHT; j++)
      {
        for (int16_t i = 0; i < display.epd2.WIDTH; i++)
        {
          if (i & 3) byte <<= 2;
          else
          {
#if defined(__AVR) || defined(ESP8266) || defined(ESP32)
            byte = pgm_read_byte(&Bitmap3c200x200_black[j * byteWidth * 2 + i / 4]);
#else
            byte = Bitmap3c200x200_black[j * byteWidth * 2 + i / 4];
#endif
          }
          if (!(byte & 0x80))
          {
            display.drawPixel(i, j, GxEPD_BLACK);
          }
        }
      }
      display.drawInvertedBitmap(0, 0, Bitmap3c200x200_red, display.epd2.WIDTH, display.epd2.HEIGHT, GxEPD_RED);
    }
    while (display.nextPage());
    delay(2000);
    for (uint16_t i = 0; i < sizeof(bitmap_pairs) / sizeof(bitmap_pair); i++)
    {
      display.firstPage();
      do
      {
        display.fillScreen(GxEPD_WHITE);
        display.drawInvertedBitmap(0, 0, bitmap_pairs[i].black, display.epd2.WIDTH, display.epd2.HEIGHT, GxEPD_BLACK);
        display.drawInvertedBitmap(0, 0, bitmap_pairs[i].red, display.epd2.WIDTH, display.epd2.HEIGHT, GxEPD_RED);
      }
      while (display.nextPage());
      delay(2000);
    }
  }
  if (display.epd2.hasColor)
  {
    display.clearScreen(); // use default for white
    int16_t x = (int16_t(display.epd2.WIDTH) - 200) / 2;
    int16_t y = (int16_t(display.epd2.HEIGHT) - 200) / 2;
    for (uint16_t i = 0; i < sizeof(bitmap_pairs) / sizeof(bitmap_pair); i++)
    {
      display.drawImage(bitmap_pairs[i].black, bitmap_pairs[i].red, x, y, 200, 200, false, false, true);
      delay(2000);
    }
    for (uint16_t i = 0; i < sizeof(bitmap_pairs) / sizeof(bitmap_pair); i++)
    {
      int16_t x = -60;
      int16_t y = -60;
      for (uint16_t j = 0; j < 10; j++)
      {
        display.writeScreenBuffer(); // use default for white
        display.writeImage(bitmap_pairs[i].black, bitmap_pairs[i].red, x, y, 200, 200, false, false, true);
        display.refresh();
        delay(1000);
        x += display.epd2.WIDTH / 4;
        y += display.epd2.HEIGHT / 4;
        if ((x >= int16_t(display.epd2.WIDTH)) || (y >= int16_t(display.epd2.HEIGHT))) break;
      }
    }
    display.writeScreenBuffer(); // use default for white
    display.writeImage(bitmap_pairs[0].black, bitmap_pairs[0].red, 0, 0, 200, 200, false, false, true);
    display.writeImage(bitmap_pairs[0].black, bitmap_pairs[0].red, int16_t(display.epd2.WIDTH) - 200, int16_t(display.epd2.HEIGHT) - 200, 200, 200, false, false, true);
    display.refresh();
    delay(2000);
  }
}
#endif

#ifdef _GxBitmaps3c104x212_H_
void drawBitmaps3c104x212()
{
#if !defined(__AVR)
  bitmap_pair bitmap_pairs[] =
  {
    {Bitmap3c104x212_1_black, Bitmap3c104x212_1_red},
    {Bitmap3c104x212_2_black, Bitmap3c104x212_2_red},
    {WS_Bitmap3c104x212_black, WS_Bitmap3c104x212_red}
  };
#else
  bitmap_pair bitmap_pairs[] =
  {
    {Bitmap3c104x212_1_black, Bitmap3c104x212_1_red},
    //{Bitmap3c104x212_2_black, Bitmap3c104x212_2_red},
    {WS_Bitmap3c104x212_black, WS_Bitmap3c104x212_red}
  };
#endif
  if (display.epd2.panel == GxEPD2::GDEW0213Z16)
  {
    for (uint16_t i = 0; i < sizeof(bitmap_pairs) / sizeof(bitmap_pair); i++)
    {
      display.firstPage();
      do
      {
        display.fillScreen(GxEPD_WHITE);
        display.drawInvertedBitmap(0, 0, bitmap_pairs[i].black, display.epd2.WIDTH, display.epd2.HEIGHT, GxEPD_BLACK);
        if (bitmap_pairs[i].red == WS_Bitmap3c104x212_red)
        {
          display.drawInvertedBitmap(0, 0, bitmap_pairs[i].red, display.epd2.WIDTH, display.epd2.HEIGHT, GxEPD_RED);
        }
        else display.drawBitmap(0, 0, bitmap_pairs[i].red, display.epd2.WIDTH, display.epd2.HEIGHT, GxEPD_RED);
      }
      while (display.nextPage());
      delay(2000);
    }
  }
}
#endif

#ifdef _GxBitmaps3c128x250_H_
void drawBitmaps3c128x250()
{
  if ((display.epd2.WIDTH == 128) && (display.epd2.HEIGHT == 250) && display.epd2.hasColor)
  {
    bool mirrored = display.mirror(true);
    display.firstPage();
    do
    {
      display.fillScreen(GxEPD_WHITE);
      display.drawInvertedBitmap(0, 0, Bitmap3c128x250_1_black, 128, 250, GxEPD_BLACK);
      display.drawInvertedBitmap(0, 0, Bitmap3c128x250_1_red, 128, 250, GxEPD_RED);
    }
    while (display.nextPage());
    delay(2000);
#if !defined(__AVR)
    display.firstPage();
    do
    {
      display.fillScreen(GxEPD_WHITE);
      display.drawInvertedBitmap(0, 0, Bitmap3c128x250_2_black, 128, 250, GxEPD_BLACK);
      display.drawBitmap(0, 0, Bitmap3c128x250_2_red, 128, 250, GxEPD_RED);
    }
    while (display.nextPage());
    delay(2000);
#endif
    display.mirror(mirrored);
  }
}
#endif

#ifdef _GxBitmaps3c128x296_H_
void drawBitmaps3c128x296()
{
#if !defined(__AVR)
  bitmap_pair bitmap_pairs[] =
  {
    {Bitmap3c128x296_1_black, Bitmap3c128x296_1_red},
    {Bitmap3c128x296_2_black, Bitmap3c128x296_2_red},
    {WS_Bitmap3c128x296_black, WS_Bitmap3c128x296_red}
  };
#else
  bitmap_pair bitmap_pairs[] =
  {
    //{Bitmap3c128x296_1_black, Bitmap3c128x296_1_red},
    //{Bitmap3c128x296_2_black, Bitmap3c128x296_2_red},
    {WS_Bitmap3c128x296_black, WS_Bitmap3c128x296_red}
  };
#endif
  if ((display.epd2.WIDTH == 128) && (display.epd2.HEIGHT == 296) && display.epd2.hasColor)
  {
    for (uint16_t i = 0; i < sizeof(bitmap_pairs) / sizeof(bitmap_pair); i++)
    {
      display.firstPage();
      do
      {
        display.fillScreen(GxEPD_WHITE);
        display.drawInvertedBitmap(0, 0, bitmap_pairs[i].black, 128, 296, GxEPD_BLACK);
        if (bitmap_pairs[i].red == WS_Bitmap3c128x296_red)
        {
          display.drawInvertedBitmap(0, 0, bitmap_pairs[i].red, 128, 296, GxEPD_RED);
        }
        else display.drawBitmap(0, 0, bitmap_pairs[i].red, 128, 296, GxEPD_RED);
      }
      while (display.nextPage());
      delay(2000);
    }
  }
}
#endif

#ifdef _GxBitmaps3c152x296_H_
void drawBitmaps3c152x296()
{
  bitmap_pair bitmap_pairs[] =
  {
    {Bitmap3c152x296_black, Bitmap3c152x296_red}
  };
  if (display.epd2.panel == GxEPD2::GDEY0266Z90)
  {
    bool mirrored = display.mirror(true);
    for (uint16_t i = 0; i < sizeof(bitmap_pairs) / sizeof(bitmap_pair); i++)
    {
      display.firstPage();
      do
      {
        display.fillScreen(GxEPD_WHITE);
        display.drawBitmap(0, 0, bitmap_pairs[i].black, 152, 296, GxEPD_BLACK);
        display.drawInvertedBitmap(0, 0, bitmap_pairs[i].red, 152, 296, GxEPD_RED);
      }
      while (display.nextPage());
      delay(2000);
    }
    display.mirror(mirrored);
  }
}
#endif

#ifdef _GxBitmaps3c176x264_H_
void drawBitmaps3c176x264()
{
  bitmap_pair bitmap_pairs[] =
  {
    {Bitmap3c176x264_black, Bitmap3c176x264_red}
  };
  if (display.epd2.panel == GxEPD2::GDEW027C44)
  {
    for (uint16_t i = 0; i < sizeof(bitmap_pairs) / sizeof(bitmap_pair); i++)
    {
      display.firstPage();
      do
      {
        display.fillScreen(GxEPD_WHITE);
        display.drawBitmap(0, 0, bitmap_pairs[i].black, display.epd2.WIDTH, display.epd2.HEIGHT, GxEPD_BLACK);
        display.drawBitmap(0, 0, bitmap_pairs[i].red, display.epd2.WIDTH, display.epd2.HEIGHT, GxEPD_RED);
      }
      while (display.nextPage());
      delay(2000);
    }
  }
}
#endif

#ifdef _GxBitmaps3c400x300_H_
void drawBitmaps3c400x300()
{
#if !defined(__AVR)
  bitmap_pair bitmap_pairs[] =
  {
    {Bitmap3c400x300_1_black, Bitmap3c400x300_1_red},
    {Bitmap3c400x300_2_black, Bitmap3c400x300_2_red},
    {WS_Bitmap3c400x300_black, WS_Bitmap3c400x300_red},
    {Bitmap3c400x300_3_black, Bitmap3c400x300_3_red},
    {Bitmap3c400x300_4_black, Bitmap3c400x300_4_red},
  };
#else
  bitmap_pair bitmap_pairs[] = {}; // not enough code space
#endif
  if ((display.epd2.WIDTH == 400) && (display.epd2.HEIGHT == 300) && display.epd2.hasColor)
  {
    for (uint16_t i = 0; i < sizeof(bitmap_pairs) / sizeof(bitmap_pair); i++)
    {
      display.firstPage();
      do
      {
        display.fillScreen(GxEPD_WHITE);
        display.drawInvertedBitmap(0, 0, bitmap_pairs[i].black, display.epd2.WIDTH, display.epd2.HEIGHT, GxEPD_BLACK);
        display.drawInvertedBitmap(0, 0, bitmap_pairs[i].red, display.epd2.WIDTH, display.epd2.HEIGHT, GxEPD_RED);
      }
      while (display.nextPage());
      delay(2000);
    }
  }
}
#endif

#ifdef _GxBitmaps3c648x480_H_
void drawBitmaps3c648x480()
{
#if !defined(__AVR)
  bitmap_pair bitmap_pairs[] =
  {
    {Bitmap3c648x480_black, Bitmap3c648x480_red},
    {Bitmap3c648x480_black_2, Bitmap3c648x480_red_2}
  };
#else
  bitmap_pair bitmap_pairs[] = {}; // not enough code space
#endif
  if ((display.epd2.panel == GxEPD2::GDEW0583Z83) || (display.epd2.panel == GxEPD2::GDEQ0583Z31))
  {
    for (uint16_t i = 0; i < sizeof(bitmap_pairs) / sizeof(bitmap_pair); i++)
    {
      display.firstPage();
      do
      {
        display.fillScreen(GxEPD_WHITE);
        display.drawBitmap(0, 0, bitmap_pairs[i].black, 648, 480, GxEPD_BLACK);
        display.drawBitmap(0, 0, bitmap_pairs[i].red, 648, 480, GxEPD_RED);
      }
      while (display.nextPage());
      delay(2000);
    }
  }
}
#endif

#if defined(ESP32) && defined(_GxBitmaps3c800x276_H_)
void drawBitmaps3c800x276()
{
  if ((display.epd2.WIDTH == 792) && (display.epd2.HEIGHT == 272) && display.epd2.hasColor)
  {
    display.drawImage(Bitmap3c800x276_black_1, Bitmap3c800x276_red_1, 0, 0, 800, 272, true, false, true); delay(2000);
    display.drawImage(Bitmap3c800x276_black_2, Bitmap3c800x276_red_2, 0, 0, 800, 272, true, false, true); delay(2000);
    int16_t wp = display.epd2.WIDTH / 5;
    int16_t hp = display.epd2.HEIGHT / 5;
    int16_t n = 0;
    for (int16_t k = 0; k < 3; k++)
    {
      display.writeScreenBuffer();
      for (int16_t i = 0; i < 5; i++)
      {
        for (int16_t j = 0; j < 5; j++)
        {
          if ((n++ % 2) || (k == 2))
          {
            display.writeImagePart(Bitmap3c800x276_black_1, Bitmap3c800x276_red_1, i * wp, j * hp, 800, 272, i * wp, j * hp, wp, hp, true, false, true);
          }
        }
      }
      display.refresh(false);
      delay(2000);
    }
  }
}
#endif

#ifdef _GxBitmaps3c800x480_H_
void drawBitmaps3c800x480()
{
#if !defined(__AVR)
  bitmap_pair bitmap_pairs[] =
  {
    {Bitmap3c800x480_1_black, Bitmap3c800x480_1_red}
  };
#else
  bitmap_pair bitmap_pairs[] = {}; // not enough code space
#endif
  if (display.epd2.panel == GxEPD2::GDEW075Z08)
  {
    for (uint16_t i = 0; i < sizeof(bitmap_pairs) / sizeof(bitmap_pair); i++)
    {
      display.firstPage();
      do
      {
        display.fillScreen(GxEPD_WHITE);
        display.drawBitmap(0, 0, bitmap_pairs[i].black, display.epd2.WIDTH, display.epd2.HEIGHT, GxEPD_BLACK);
        display.drawBitmap(0, 0, bitmap_pairs[i].red, display.epd2.WIDTH, display.epd2.HEIGHT, GxEPD_RED);
      }
      while (display.nextPage());
      delay(2000);
    }
  }
}
#endif

#ifdef _GxBitmaps3c880x528_H_
void drawBitmaps3c880x528()
{
#if !defined(__AVR)
  bitmap_pair bitmap_pairs[] =
  {
    {Bitmap3c880x528_black, Bitmap3c880x528_red}
  };
#else
  bitmap_pair bitmap_pairs[] = {}; // not enough code space
#endif
  if (display.epd2.panel == GxEPD2::GDEH075Z90)
  {
    bool m = display.mirror(true);
    for (uint16_t i = 0; i < sizeof(bitmap_pairs) / sizeof(bitmap_pair); i++)
    {
      display.firstPage();
      do
      {
        display.fillScreen(GxEPD_WHITE);
        display.drawInvertedBitmap(0, 0, bitmap_pairs[i].black, 880, 528, GxEPD_BLACK);
        display.drawInvertedBitmap(0, 0, bitmap_pairs[i].red, 880, 528, GxEPD_RED);
      }
      while (display.nextPage());
      delay(2000);
    }
    display.mirror(m);
  }
}
#endif

#if defined(ESP32) && defined(_GxBitmaps3c960x640_H_)
void drawBitmaps3c960x640()
{
  if ((display.epd2.WIDTH == 960) && (display.epd2.HEIGHT == 640) && display.epd2.hasColor)
  {
    display.drawImage(Bitmap3c960x640_black, Bitmap3c960x640_red, 0, 0, 960, 640, false, false, true);
    delay(2000);
  }
}
#endif

#if defined(ESP32) && defined(_GxBitmaps3c960x680_H_)
void drawBitmaps3c960x680()
{
  if ((display.epd2.WIDTH == 960) && (display.epd2.HEIGHT == 680) && display.epd2.hasColor)
  {
    display.drawImage(Bitmap3c960x680_black, Bitmap3c960x680_red, 0, 0, 960, 680, false, true, true);
  }
  delay(2000);
}
#endif

#if defined(ESP32) && defined(_GxBitmaps3c1304x984_H_)
void drawBitmaps3c1304x984()
{
  if (display.epd2.panel == GxEPD2::GDEY1248Z51)
  {
    //display.drawImage(Bitmap3c1304x984_black, Bitmap3c1304x984_red, 0, 0, 1304, 984, false, false, true);
    display.writeImage(0, Bitmap3c1304x984_red, 0, 0, 1304, 984, true, false, true); // red bitmap is inverted
    display.drawImage(Bitmap3c1304x984_black, 0, 0, 0, 1304, 984, true, false, true); // black bitmap is normal
  }
}
#endif

#if defined(_GxBitmaps4c128x250_H_)
void drawBitmaps4c128x250()
{
  if (display.epd2.panel == GxEPD2::GDEY0213F51)
  {
    display.drawNative(Bitmap4c128x250, 0, 0, 0, 128, 250, false, false, true);
    delay(5000);
  }
}
#endif

#if defined(_WS_Bitmaps4c168x168_H_)
void drawBitmaps4c168x168()
{
  if ((display.epd2.panel == GxEPD2::Waveshare437inch4color) || (display.epd2.panel == GxEPD2::Waveshare3inch4color) ||
      (display.epd2.panel == GxEPD2::GDEY0579F51) || (display.epd2.panel == GxEPD2::GDEY116F51))
  {
    display.drawNative(WS_Bitmap4c168x168, 0, (display.epd2.WIDTH - 168) / 2, (display.epd2.HEIGHT - 168) / 2, 168, 168, false, false, true);
    delay(5000);
  }
}
#endif

#if defined(_WS_Bitmaps4c168x400_H_)
void drawBitmaps4c168x400()
{
  if (display.epd2.panel == GxEPD2::Waveshare3inch4color)
  {
    display.drawNative(WS_Bitmap4c168x400, 0, (display.epd2.WIDTH - 168) / 2, (display.epd2.HEIGHT - 400) / 2, 168, 400, false, false, true);
    delay(5000);
  }
}
#endif

#if defined(_GxBitmaps4c168x384_H_)
void drawBitmaps4c168x384()
{
  if (display.epd2.panel == GxEPD2::GDEY029F51H)
  {
    display.drawNative(Bitmap4c168x384, 0, (display.epd2.WIDTH - 168) / 2, (display.epd2.HEIGHT - 384) / 2, 168, 384, false, false, true);
    delay(5000);
  }
}
#endif

#if defined(_GxBitmaps4c184x360_H_)
void drawBitmaps4c184x360()
{
  if (display.epd2.panel == GxEPD2::GDEY0266F51H)
  {
    display.drawNative(Bitmap4c184x360, 0, (display.epd2.WIDTH - 184) / 2, (display.epd2.HEIGHT - 360) / 2, 184, 360, false, false, true);
    delay(5000);
  }
}
#endif

#if defined(_GxBitmaps4c400x300_H_)
void drawBitmaps4c400x300()
{
  if (display.epd2.panel == GxEPD2::GDEY0420F51)
  {
    display.drawNative(Bitmap4c400x300, 0, (display.epd2.WIDTH - 400) / 2, (display.epd2.HEIGHT - 300) / 2, 400, 300, false, false, true);
    delay(5000);
  }
}
#endif

#if defined(_GxBitmaps4c960x640_H_)
void drawBitmaps4c960x640()
{
  if (display.epd2.panel == GxEPD2::GDEY116F51)
  {
    display.drawNative(Bitmap4c960x640, 0, (display.epd2.WIDTH - 960) / 2, (display.epd2.HEIGHT - 640) / 2, 960, 640, true, false, true);
    delay(5000);
  }
}
#endif

#if defined(ESP32) && defined(_GxBitmaps4c792x272_H_)
void drawBitmaps4c792x272()
{
  if (display.epd2.panel == GxEPD2::GDEY0579F51)
  {
    display.drawNative(Bitmap4c792x272, 0, (display.epd2.WIDTH - 792) / 2, (display.epd2.HEIGHT - 272) / 2, 792, 272, true, false, true);
    delay(5000);
#if defined(GxEPD2_DRIVER_CLASS) && defined(IS_GxEPD2_DRIVER_4C)
#if IS_GxEPD2_DRIVER_4C(GxEPD2_DRIVER_CLASS)
    int16_t wp = display.epd2.WIDTH / 5;
    int16_t hp = display.epd2.HEIGHT / 5;
    int16_t n = 0;
    for (int16_t k = 0; k < 3; k++)
    {
      display.writeScreenBuffer();
      for (int16_t i = 0; i < 5; i++)
      {
        for (int16_t j = 0; j < 5; j++)
        {
          if ((n++ % 2) || (k == 2))
          {
            display.epd2.writeNativePart(Bitmap4c792x272, 0, i * wp, j * hp, 792, 272, i * wp, j * hp, wp, hp, true, false, true);
          }
        }
      }
      display.refresh(false);
      delay(2000);
    }
#endif
#endif
  }
}
#endif

#if defined(_GxBitmaps7c600x448_H_)
void drawBitmaps7c600x448()
{
  if (display.epd2.panel == GxEPD2::GDEP0565D90)
  {
    display.epd2.drawDemoBitmap(Bitmap7c600x448, 0, 0, 0, 600, 448, 1, false, true);
    delay(5000);
  }
}
#endif

#if defined(_WS_Bitmaps7c192x143_H_)
void drawBitmaps7c192x143()
{
  if (display.epd2.panel == GxEPD2::ACeP565)
  {
    display.drawNative(WS_Bitmap7c192x143, 0, (display.epd2.WIDTH - 192) / 2, (display.epd2.HEIGHT - 143) / 2, 192, 143, false, false, true);
    delay(5000);
  }
}
#endif

#if defined(_GxBitmaps7c800x480_H_)
void drawBitmaps7c800x480()
{
  if ((display.epd2.panel == GxEPD2::GDEY073D46) || (display.epd2.panel == GxEPD2::ACeP730) || (display.epd2.panel == GxEPD2::GDEP0565D90) || (display.epd2.panel == GxEPD2::GDEP073E01))
  {
    display.epd2.drawDemoBitmap(Bitmap7c800x480, 0, 0, 0, 800, 480, 0, false, true); // special format
    delay(5000);
    display.epd2.drawDemoBitmap(Bitmap7c800x480_2, 0, 0, 0, 800, 480, 1, false, true); // special format mode 1
    delay(5000);
  }
}
#endif

#if defined(_WS_Bitmaps7c300x180_H_)
void drawBitmaps7c300x180()
{
  if ((display.epd2.panel == GxEPD2::GDEY073D46) || (display.epd2.panel == GxEPD2::ACeP730) || (display.epd2.panel == GxEPD2::GDEP0565D90))
  {
    display.drawNative(WS_Bitmap7c300x180, 0, (display.epd2.WIDTH - 300) / 2, (display.epd2.HEIGHT - 180) / 2, 300, 180, false, false, true);
    delay(5000);
  }
}
#endif

void draw7colors()
{
  display.setRotation(0);
  uint16_t h = display.height() / 7;
  display.firstPage();
  do
  {
    display.fillRect(0, 0, display.width(), h, GxEPD_BLACK);
    display.fillRect(0, h, display.width(), h, GxEPD_WHITE);
    display.fillRect(0, 2 * h, display.width(), h, GxEPD_GREEN);
    display.fillRect(0, 3 * h, display.width(), h, GxEPD_BLUE);
    display.fillRect(0, 4 * h, display.width(), h, GxEPD_RED);
    display.fillRect(0, 5 * h, display.width(), h, GxEPD_YELLOW);
    display.fillRect(0, 6 * h, display.width(), h, GxEPD_ORANGE);
  }
  while (display.nextPage());
}

void draw7colorlines()
{
  display.setRotation(0);
  uint16_t h = 2;
  display.firstPage();
  do
  {
    uint16_t y = 0;
    do
    {
      display.fillRect(0, y, display.width(), h, GxEPD_BLACK); y += h;
      display.fillRect(0, y, display.width(), h, GxEPD_WHITE); y += h;
      display.fillRect(0, y, display.width(), h, GxEPD_GREEN); y += h;
      display.fillRect(0, y, display.width(), h, GxEPD_WHITE); y += h;
      display.fillRect(0, y, display.width(), h, GxEPD_BLUE); y += h;
      display.fillRect(0, y, display.width(), h, GxEPD_WHITE); y += h;
      display.fillRect(0, y, display.width(), h, GxEPD_RED); y += h;
      display.fillRect(0, y, display.width(), h, GxEPD_WHITE); y += h;
      display.fillRect(0, y, display.width(), h, GxEPD_YELLOW); y += h;
      display.fillRect(0, y, display.width(), h, GxEPD_WHITE); y += h;
      display.fillRect(0, y, display.width(), h, GxEPD_ORANGE); y += h;
      display.fillRect(0, y, display.width(), h, GxEPD_WHITE); y += h;
    }
    while ((y + 12 * h) < uint16_t(display.height()));
    //display.drawPixel(0, y, GxEPD_BLACK); display.drawPixel(10, y, GxEPD_GREEN);
    //display.drawPixel(20, y, GxEPD_BLUE); display.drawPixel(30, y, GxEPD_RED);
    //display.drawPixel(40, y, GxEPD_YELLOW); display.drawPixel(50, y, GxEPD_ORANGE);
    display.fillRect(0, y, 2, 2, GxEPD_BLACK); display.fillRect(10, y, 2, 2, GxEPD_GREEN);
    display.fillRect(20, y, 2, 2, GxEPD_BLUE); display.fillRect(30, y, 2, 2, GxEPD_RED);
    display.fillRect(40, y, 2, 2, GxEPD_YELLOW); display.fillRect(50, y, 2, 2, GxEPD_ORANGE);
  }
  while (display.nextPage());
}

void drawGraphics()
{
  display.setRotation(0);
  display.firstPage();
  do
  {
    display.drawRect(display.width() / 8, display.height() / 8, display.width() * 3 / 4, display.height() * 3 / 4, GxEPD_BLACK);
    display.drawLine(display.width() / 8, display.height() / 8, display.width() * 7 / 8, display.height() * 7 / 8, GxEPD_BLACK);
    display.drawLine(display.width() / 8, display.height() * 7 / 8, display.width() * 7 / 8, display.height() / 8, GxEPD_BLACK);
    display.drawCircle(display.width() / 2, display.height() / 2, display.height() / 4, GxEPD_BLACK);
    display.drawPixel(display.width() / 4, display.height() / 2 , GxEPD_BLACK);
    display.drawPixel(display.width() * 3 / 4, display.height() / 2 , GxEPD_BLACK);
  }
  while (display.nextPage());
  delay(1000);
}
