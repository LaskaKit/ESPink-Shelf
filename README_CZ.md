# LaskaKit ESPink-Shelf-213 ESP32 e-Paper a ESPink-Shelf-29

Malá, designově povedá vývojová deska, která byla navržena především na co nejnižší spotřebu proudu a pohodlné programování.</br>
To je ESPink Shelf 213 a ESPink Shelf 29, deska osazené [ePaper o velikosti 2.13"](https://www.laskakit.cz/good-display-gdey0213b74-2-13--250x122-epaper-displej/) a [ePaper o velikosti 2.9"](https://www.laskakit.cz/laskakit-espink-shelf-2-9-esp32-e-paper/?variantId=14193).</br>
[LaskaKit ESPink-4.2 ESP32 e-Paper](https://www.laskakit.cz/laskakit-espink-42-esp32-e-paper-pcb-antenna/?variantId=13538) a [LaskaKit ESPink-Shelf-4.26 ESP32 e-Paper](https://www.laskakit.cz/laskakit-espink-4-26-esp32-s3-e-paper/).</br>
Pokud preferuješ samostatnou desku, pak máme v nabídce [velmi úsporný a univerzální ESPink](https://www.laskakit.cz/laskakit-espink-esp32-e-paper-pcb-antenna/?variantId=12419). Deska je menší a univerzálnější pro připojení jiných ePaper displejů. </br>

![Popis desky](https://github.com/LaskaKit/ESPink-Shelf/blob/main/img/ESP32-Shelf-213_desc.JPG)

A jak jsme dosáhli tak nízké, , 12,5 uA, spotřeby? ESP32 je výkonný čip umožňující se připojit na Wi-Fi a Bluetooth, ale kromě toho je velmi úsporný, cca 5 uA, i v režimu hlubokého spánku (tzv. deep-sleep mode).</br>
ePaper spotřebovává energii zejména při přepisu data na displeji, každá uA se ale počítá a tak jsme přidali na napájení MOSFET, kterým odpínáme napětí v případě, že ePaper není aktualizován. </br>
Tím ale ještě nekončíme - na desce je i[ uŠup konektor](https://blog.laskakit.cz/predstavujeme-univerzalni-konektor-pro-propojeni-modulu-a-cidel-%CE%BCsup/), to je 4 pinový konektor ke kterému máme bohaté příslušenství a má standardní rozměr a pinout. 3,3V napájení, GND a a I2C sběrnici. Mezi příslušenství patří [kabely různých délek zakončené steným konektorem](https://www.laskakit.cz/--sup--stemma-qt--qwiic-jst-sh-4-pin-kabel-10cm/), [kabely zakončený dupont dutinkami](https://www.laskakit.cz/--sup--stemma-qt--qwiic-jst-sh-4-pin-kabel-dupont-samice/) nebo [kabely zakončené háčky](https://www.laskakit.cz/--sup--stemma-qt--qwiic-jst-sh-4-pin-kabel-s-testovacim-hackem/) pro rychlé a spolehlivé testování.  </br>

Napájení I2C konektoru lze také odpojit napájení stejně jako ePaperu - MOSFET spínače jsou řízení GPIO2. </br>
GPIO2 tedy řídí/spíná jak napětí pro ePaper, tak i pro I2C čidla připojená na uŠup konektor. </br>

A jaké moduly to mohou být? Třeba čidlo [SCD41 pro měření CO2, teploty a vlhkosti vzduchu](https://www.laskakit.cz/laskakit-scd41-senzor-co2--teploty-a-vlhkosti-vzduchu/), čidla SHT41 [teploty a vlhkosti vzduchu](https://www.laskakit.cz/laskakit-sht40-senzor-teploty-a-vlhkosti-vzduchu/) a [čidla tlaku, teploty a vlhkosti vzduchu BME280](https://www.laskakit.cz/arduino-senzor-tlaku--teploty-a-vlhkosti-bme280/), [RTC Hodiny reálného času](https://www.laskakit.cz/laskakit-ds3231-orig--rtc-hodiny-realneho-casu/) s DS3231 nebo [OLED displej o velikosti 1.3" a rozlišení 128x64px](https://www.laskakit.cz/laskakit-oled-displej-128x64-1-3--i2c/?variantId=11903).

Deska lze samozřejmě kompletně vypnout díky integrovanému přepínači. USB-C konektor umístěný na desce slouží jak pro programování, tak i nabíjení akumulátoru, který můžete samozřejmě připojit. </br>
Pro pohodlné programování slouží osazený USB-UART převodník CH9102F, který vyniká jak rychlostí, tak i nízkou vlastní spotřebou.</br>
V případě potřeby větší paměti pak máme osazený ještě slot pro microSD kartu, kam můžeš uložit ikony nebo obrázky. </br>

Na desce je osazen i dělič napětí, který je připojen na akumulátor a ESP32 může měřit napětí. Na základě napětí pak provést nějakou akci - například upozornit na nízký stav napětí baterie. Dělič je připojen na pin GPIO34.</br>

Deska podporuje populární projekt Živý Obraz, který výrazně zjednodušuje použití ePaper displeje k zobrazení fotografií, (google, outlook, apple) kalendáře, kurzů, hodnot z meteostanic, předpovědi počasí a mnoho dalšího. Není nutné psát kód, stačí nahrát správný typ ePaper a desky skrze webové prostředí a dodržet postup popsaný v [dokumentaci](https://wiki.zivyobraz.eu/).</br>
Program nahraješ [přes webové prostředí na této stránce](https://zivyobraz.eu/?page=instalace) a stačí zvolit desku <b>LaskaKit ESPink 2.x</b> a typ ePaperu <b>GDEY029F51H, GDEY029T71H, GDEY029T94 nebo GDEY0213B74</b> - podle toho, co sis objednal. </br>

K této desce jsme připravili několik vzorových kódů, které můžeš využít. Nejzajímavější je kód nazvaný "[Date_BusConnection_WeatherForecast](https://github.com/LaskaKit/ESPink-Shelf/tree/main/SW/Date_BusConnection_WeatherForecast)", kde kromě zobrazení aktuálního data je zobrazena i předpověd počasí a následující odjezdy MHD - třeba autobusů nebo tramvají. 

Vývojovou desku najdeš na našem e-shopu https://www.laskakit.cz/laskakit-espink-shelf-213-esp32-e-paper/
 a https://www.laskakit.cz/laskakit-espink-shelf-2-9-esp32-e-paper/?variantId=14193

![Autobusy](https://github.com/LaskaKit/ESPink-Shelf/blob/main/SW/Date_BusConnection_WeatherForecast/Date_BusConnection_WeatherForecast.jpg)
