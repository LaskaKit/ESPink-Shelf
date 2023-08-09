
#define SLEEP_SEC 15         // Measurement interval (seconds)

void setup(void)
{
  Serial.begin(115200);

  goToSleep();
}

void loop(void) 
{

}

void goToSleep(){

  Serial.println("I'm mot sleeping");
  delay(3000);
  Serial.println("going to sleep 15 sek");
  // ESP Deep Sleep 
  Serial.println("ESP in sleep mode");
  Serial.flush(); 
  esp_sleep_enable_timer_wakeup(SLEEP_SEC * 1000000);
  esp_deep_sleep_start();
}
