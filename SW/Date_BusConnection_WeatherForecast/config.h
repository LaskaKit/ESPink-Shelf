/*------- NTP ----------*/
const char* ntpServer = "europe.pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;

/*------- Arduino JSON config ----------*/
const char* jsonurl = "https://lovecka.info/YrNoProvider1/yrno/forecast?lat=YOUR_LAT&lon=YOUR_LOG&alt=50&mode=1"; // write your location - lat and log

/*------- Wi-Fi credentials ----------*/
char ssid[] = "SSID";
char pass[] = "PASSWORD";

/*------- Sleep duration ----------*/
const int sleepDuration = 600;