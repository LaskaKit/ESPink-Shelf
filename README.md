# LaskaKit ESPink-Shelf-213 ESP32 e-Paper 

A small development board that has been designed primarily for lowest power consumption and convenient programming.</br>
This is the ESPink Shelf 213, a board equipped with [ePaper with 2.13" dimension](https://www.laskakit.cz/good-display-gdey0213b74-2-13--250x122-epaper-displej/).</br>

![Description](https://github.com/LaskaKit/ESPink-Shelf/blob/main/img/ESP32-Shelf-213_desc.JPG)

And how did we achieve such a low power consumption - 12.5 uA? The ESP32 is a powerful chip that allows you to connect to Wi-Fi and Bluetooth, but it is also very power efficient, about 5 uA, even in deep-sleep mode.
The ePaper consumes power especially during the update of the display, but every uA counts so we added a MOSFET to the power supply to disconnect from source the ePaper when it is not updated.

But we don't stop there - there is also i [uŠup connector](https://blog.laskakit.cz/predstavujeme-univerzalni-konektor-pro-propojeni-modulu-a-cidel-%CE%BCsup/), this is a 4 pin connector to which we have a wide range of accessories and has a standard size and pinout. 3.3V power supply, GND and I2C bus. Accessories include [cables with variable length](https://www.laskakit.cz/--sup--stemma-qt--qwiic-jst-sh-4-pin-kabel-10cm/), [the cables with female duponts](https://www.laskakit.cz/--sup--stemma-qt--qwiic-jst-sh-4-pin-kabel-dupont-samice/) or [the cables with hooks](https://www.laskakit.cz/--sup--stemma-qt--qwiic-jst-sh-4-pin-kabel-s-testovacim-hackem/) for fast debug.  </br>

The I2C connector power supply can also be disconnected just like the ePaper - the MOSFET switches are GPIO2 control.

And what another modules you can use? For example the sensor [SCD41 for measurement of CO2, temperature and humidity](https://www.laskakit.cz/laskakit-scd41-senzor-co2--teploty-a-vlhkosti-vzduchu/), sensor SHT41 [temperature nad humidity](https://www.laskakit.cz/laskakit-sht40-senzor-teploty-a-vlhkosti-vzduchu/) and [sensor of pressure, temperature, humidity BME280](https://www.laskakit.cz/arduino-senzor-tlaku--teploty-a-vlhkosti-bme280/), [RTC - Real Time Clock](https://www.laskakit.cz/laskakit-ds3231-orig--rtc-hodiny-realneho-casu/) with DS3231 or [OLED display with 1.3" dimension and 128x64px resolution](https://www.laskakit.cz/laskakit-oled-displej-128x64-1-3--i2c/?variantId=11903).

The board can be disconnected from source thanks to switch. The USB-C connector located on the board is used for both programming and charging the battery, which you can of course plug in. 
For convenient programming, the fitted USB-UART converter CH9102F is used, which excels both in speed and low self-consumption.
If you need more memory, there is also a microSD card slot where you can store icons or images. 

There is also a voltage divider on the board that is connected to the battery and the ESP32 can measure the voltage. It can then perform an action based on the voltage - for example, to warn of a low battery voltage. The divider is connected to the GPIO34 pin.

We have prepared some sample codes for you to use with this board. The most interesting is the code called "[Date_BusConnection_WeatherForecast](https://github.com/LaskaKit/ESPink-Shelf/tree/main/SW/Date_BusConnection_WeatherForecast)", where, in addition to displaying the current date, the weather forecast and the next public transport departures - such as buses or trams - are also displayed. 

You can find the development board on our e-shop https://www.laskakit.cz/laskakit-espink-shelf-213-esp32-e-paper/

![Bus](https://github.com/LaskaKit/ESPink-Shelf/blob/main/SW/Date_BusConnection_WeatherForecast/Date_BusConnection_WeatherForecast.jpg)
