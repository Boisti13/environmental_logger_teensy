void loop(void) {
  display.clearDisplay();
  display.setTextSize(1.5);
  display.setTextColor(SSD1306_WHITE);

  time_loop();
  //BMP180();
  BME280_loop();
  DS18B20();
  rain();

  sd_logger();

  displayinfo();
  display.display();
}