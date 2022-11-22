void time_setup() {

  Serial1.begin(9600);

  delay(100);

  myRTC.begin();
  setSyncProvider(myRTC.get);  // the function to get the time from the RTC
  display.setCursor(10, 40);

  int serial1Status = Serial1.available();

  if (serial1Status > 0) {
    display.println("GPS connected");
  } else {
    display.println("GPS not connected");
  }
  display.display();
  delay(bootTime);

  if (timeStatus() != timeSet) {
    Serial.println("Unable to sync with the RTC");
    display.setCursor(10, 50);
    display.println("Not snyced with RTC");
    display.display();
    delay(bootTime);
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("Check wiring!!");
    display.display();
    delay(bootTime);
    display.setCursor(0, 30);
    display.println("Shutting Down");
    display.display();
    delay(bootTime);
    display.clearDisplay();
    display.display();
    stop();

  } else {
    if (year() != 2000) {
      Serial.println("RTC has set the system time");
      display.setCursor(10, 50);
      display.println("Synced with RTC");
      display.display();
      delay(bootTime);

      display.setTextColor(0xFFFF, 0);
      display.setCursor(10, 50);
      display.println("                        ");
      display.display();
      display.setTextColor(SSD1306_WHITE);

      sprintf(rtcTimeandDateString, "%02d-%02d-%04d %02d:%02d:%02d", day(), month(), year(), hour(), minute(), second());
      display.setCursor(10, 50);
      display.println(rtcTimeandDateString);
      display.display();
      delay(bootTime);
    } else {
      display.setTextColor(0xFFFF, 0);
      display.setCursor(10, 50);
      display.println("                        ");
      display.display();
      display.setTextColor(SSD1306_WHITE);

      display.setCursor(10, 50);
      display.println("RTC needs syncing");
      display.display();
      delay(bootTime);
    }
  }
  display.display();
  delay(bootTime);
}

//////////////
void stop() {
  while (1)
    ;
}
/////////

void time_loop() {

  if (year() >= 2022) {
    sprintf(rtcTimeandDateString, "%02d-%02d-%04d %02d:%02d:%02d", day(), month(), year(), hour(), minute(), second());  //Time and Date String from RTC
    display.setCursor(5, 0);
    display.println(rtcTimeandDateString);
  } else {
    display.setCursor(1, 60);
    display.println("Time not synced yet");

    bool newData = false;
    for (unsigned long start = millis(); millis() - start < 1000;) {
      while (Serial1.available()) {
        char c = Serial1.read();
        //Serial.write(c); // uncomment this line if you want to see the GPS data flowing
        if (gps.encode(c))  // Did a new valid sentence come in?
          newData = true;
        
      }
    }

    if (newData) {
      gps_hour = gps.time.hour() + 1;
      gps_minute = gps.time.minute();
      gps_second = gps.time.second();
      gps_month = gps.date.month();
      gps_day = gps.date.day();
      gps_year = gps.date.year();

      sprintf(gpsTimeandDateString, "%02d-%02d-%04d %02d:%02d:%02d", gps_day, gps_month, gps_year, gps_hour, gps_minute, gps_second);  //Time and Date String from GPS
      //Serial.println(gpsTimeandDateString);
      if (gps.date.year() != 2000) {

        tmElements_t tm;

        tm.Hour = gps_hour;
        tm.Minute = gps_minute;
        tm.Second = gps_second;
        tm.Month = gps_month;
        tm.Day = gps_day;
        tm.Year = gps.date.year() - 18;

        myRTC.write(tm);
        setTime(myRTC.get());
        //Serial.println("RTC Set");
        display.setCursor(10, 50);
        //display.println(gpsTimeandDateString);

      } else {
        display.setCursor(1, 60);
        display.setTextSize(1);
        display.println("GPS sync");
        display.fillRect(20, 60, 50, 3, SSD1306_WHITE);
        //Serial1.begin();
      }
    }
  }
}