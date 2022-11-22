/*
void BMP180_setup() {

  if (!bmp.begin()) {
    display.setCursor(10, 50);
    display.println("BMP180 not found");
  } else {
    display.setCursor(10, 50);
    display.println("BMP180 found");
  }
  display.display();
  delay(bootTime);
}

////////////////////


void BMP180() {

  tempBmp = bmp.readTemperature();            //C
  airPressure = bmp.readPressure();               //Pa
  Altitude = bmp.readAltitude();                  //m
  sealevelPressure = bmp.readSealevelPressure();  //Pa
  realAltitude = bmp.readAltitude(101500);        //m
}
*/