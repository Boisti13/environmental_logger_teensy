void setup() {
  Serial.begin(9600);
  
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  display.clearDisplay();
  display.setTextSize(1);
  //display.setFont(&Roboto_Mono_Thin_5Bitmaps);
  display.setTextColor(SSD1306_WHITE);
display.setCursor(10, 0);
display.println("System Check");
display.display();
delay(bootTime);
  

  sd_logger_setup();
  display.display();
  delay(bootTime);

  DS18B20_setup();
  display.display();
  delay(bootTime);

  rain_setup();

  //BMP180_setup();
  BME280_setup();

  delay(bootTime);

  time_setup();
  display.display();
  delay(bootTime);

}