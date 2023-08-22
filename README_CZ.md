# LaskaKit ESPink-Shelf-213 ESP32 e-Paper 

Malá, designově povedá vývojová deska, která byla navržena především na co nejnižší spotřebu proudu a pohodlné programování.</br>
To je ESPink Shelf 213, deska osazené [ePaper o velikosti 2.13"](https://www.laskakit.cz/good-display-gdey0213b74-2-13--250x122-epaper-displej/).</br>

![Popis desky](https://github.com/LaskaKit/ESPink-Shelf/blob/main/img/ESP32-Shelf-213_desc.JPG)

A jak jsme dosáhli tak nízké, , 12,5 uA, spotřeby? ESP32 je výkonný čip umožňující se připojit na Wi-Fi a Bluetooth, ale kromě toho je velmi úsporný, cca 5 uA, i v režimu hlubokého spánku (tzv. deep-sleep mode).</br>
ePaper spotřebovává energii zejména při přepisu data na displeji, každá uA se ale počítá a tak jsme přidali na napájení MOSFET, kterým odpínáme napětí v případě, že ePaper není aktualizován. </br>
Tím ale ještě nekončíme - na desce je i[ uŠup konektor](https://blog.laskakit.cz/predstavujeme-univerzalni-konektor-pro-propojeni-modulu-a-cidel-%CE%BCsup/), to je 4 pinový konektor ke kterému máme bohaté příslušenství a má standardní rozměr a pinout. 3,3V napájení, GND a a I2C sběrnici. Mezi příslušenství patří [kabely různých délek zakončené steným konektorem](https://www.laskakit.cz/--sup--stemma-qt--qwiic-jst-sh-4-pin-kabel-10cm/), [kabely zakončený dupont dutinkami](https://www.laskakit.cz/--sup--stemma-qt--qwiic-jst-sh-4-pin-kabel-dupont-samice/) nebo [kabely zakončené háčky](https://www.laskakit.cz/--sup--stemma-qt--qwiic-jst-sh-4-pin-kabel-s-testovacim-hackem/) pro rychlé a spolehlivé testování.  </br>

Napájení I2C konektoru lze také odpojit napájení stejně jako ePaperu - MOSFET spínače jsou řízení GPIO2. </br>

A jaké moduly to mohou být? Třeba čidlo [SCD41 pro měření CO2, teploty a vlhkosti vzduchu](https://www.laskakit.cz/laskakit-scd41-senzor-co2--teploty-a-vlhkosti-vzduchu/), čidla SHT41 [teploty a vlhkosti vzduchu](https://www.laskakit.cz/laskakit-sht40-senzor-teploty-a-vlhkosti-vzduchu/) a [čidla tlaku, teploty a vlhkosti vzduchu BME280](https://www.laskakit.cz/arduino-senzor-tlaku--teploty-a-vlhkosti-bme280/), [RTC Hodiny reálného času](https://www.laskakit.cz/laskakit-ds3231-orig--rtc-hodiny-realneho-casu/) s DS3231 nebo [OLED displej o velikosti 1.3" a rozlišení 128x64px](https://www.laskakit.cz/laskakit-oled-displej-128x64-1-3--i2c/?variantId=11903).

Deska lze samozřejmě kompletně vypnout díky integrovanému přepínači. USB-C konektor umístěný na desce slouží jak pro programování, tak i nabíjení akumulátoru, který můžete samozřejmě připojit. </br>
Pro pohodlné programování slouží osazený USB-UART převodník CH9102F, který vyniká jak rychlostí, tak i nízkou vlastní spotřebou.</br>
V případě potřeby větší paměti pak máme osazený ještě slot pro microSD kartu, kam můžeš uložit ikony nebo obrázky. </br>

Na desce je osazen i dělič napětí, který je připojen na akumulátor a ESP32 může měřit napětí. Na základě napětí pak provést nějakou akci - například upozornit na nízký stav napětí baterie. Dělič je připojen na pin GPIO34.</br>

K této desce jsme připravili několik vzorových kódů, které můžeš využít. Nejzajímavější je kód nazvaný "[Date_BusConnection_WeatherForecast](https://github.com/LaskaKit/ESPink-Shelf/tree/main/SW/Date_BusConnection_WeatherForecast)", kde kromě zobrazení aktuálního data je zobrazena i předpověd počasí a následující odjezdy MHD - třeba autobusů nebo tramvají. 

Vývojovou desku najdeš na našem e-shopu https://www.laskakit.cz/laskakit-espink-shelf-213-esp32-e-paper/

![Autobusy](https://github.com/LaskaKit/ESPink-Shelf/blob/main/SW/Date_BusConnection_WeatherForecast/Date_BusConnection_WeatherForecast.jpg)
