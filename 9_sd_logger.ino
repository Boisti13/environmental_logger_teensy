void sd_logger_setup() {

  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    display.setCursor(10, 10);
    display.println("SD not initialized");
    return;

  } else {
    display.setCursor(10, 10);
    display.println("SD initialized");
  }
}

/////////


void sd_logger() {

  unsigned long currentMillis = millis();

  dtostrf(tempIndoor1, 4, 2, tempIndoor1Str);    //OneWire
  dtostrf(tempOutdoor1, 4, 2, tempOutdoor1Str);  //OneWire

  //dtostrf(tempBmp, 4, 2, tempBmpStr);   //BMP
  //dtostrf(airPressure, 4, 0, bmpPresStr);       //BMP

  dtostrf(pressureBme, 6, 2, presBmeStr);  //BME air pressure
  dtostrf(tempBme, 4, 2, tempBmeStr);      //BME temp
  dtostrf(humidityBme, 5, 2, humBmeStr);   //BME temp

  if (!SD.begin(chipSelect)) {
    display.setCursor(1, 10);
    display.println("SD Error");
    display.display();
  } else {
    if ((year() >= 2022) && (year() <= 2030)) {
      sprintf(logFileName, "%02d_%02d_%04d.CSV", day(), month(), year());

      if (!SD.exists(logFileName)) {
        dataFile = SD.open(logFileName, FILE_WRITE);
        dataFile.println("Date;Time;0=Rain / 1=No Rain;Pressure [hPa];Humidity [%];Temp Indoor [C];Temp BME [C];Temp Outdoor [C]");
        display.setCursor(1, 10);
        display.println("File created");
      } else {
        dataFile = SD.open(logFileName, FILE_WRITE);
        display.setCursor(1, 10);
        display.println("File available");
      }
    }
    //Log String
    sprintf(logString, "%02d.%02d.%04d;%02d:%02d:%02d;%01d;%s;%s;%s;%s;%s", day(), month(), year(), hour(), minute(), second(), rainStatus, presBmeStr, humBmeStr, tempIndoor1Str, tempBmeStr, tempOutdoor1Str);


    if (currentMillis - previousMillis >= logSpeed) {
      previousMillis = currentMillis;
      if (dataFile) {
        dataFile.println(logString);
        dataFile.close();
        display.fillRect(100, 9, 10, 10, SSD1306_WHITE);
      } else {
        // if the file isn't open, pop up an error
        display.setCursor(90, 10);
        display.println("ERROR");
      }
    }
  }
}