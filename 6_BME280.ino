void BME280_setup() {

  if (!bme.begin(0x76)) {
    display.setCursor(10, 30);
    display.println("BME280 not conected");
  } else {
    display.setCursor(10, 30);
    display.println("BME280 connected");
  }
  display.display();
  delay(bootTime);
}

////////////////////


void BME280_loop() {

  tempBme = bme.readTemperature();            //C
  //Serial.println(tempBme);
  pressureBme = bme.readPressure() / 100.0F;  //hPa
                                              //Altitude = bmp.readAltitude();                  //m
                                              //sealevelPressure = bmp.readSealevelPressure();  //Pa
  //realAltitude = bmp.readAltitude(101500);        //m
  humidityBme = bme.readHumidity();  // %
}