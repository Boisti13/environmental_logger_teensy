void displayinfo() {

  display.setCursor(1, 20);
  sprintf(bmeTemp, "BME Temp: %s *C", tempBmeStr);
  display.println(bmeTemp); //BMP

  display.setCursor(1, 30);
  sprintf(bmePres, "BME Pres: %s hPa", presBmeStr);
  display.println(bmePres);

  display.setCursor(1, 40);
  sprintf(inTemp, "Indoor: %s *C", tempIndoor1Str);
  display.println(inTemp);

  display.setCursor(1, 50);
  sprintf(outTemp, "Outdoor: %s *C", tempOutdoor1Str);
  display.println(outTemp);
  
}