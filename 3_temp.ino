void DS18B20_setup() {

  sensors.begin();
  deviceCount = sensors.getDeviceCount();
  sensors.setResolution(sensorOutdoor, 10);
  sensors.setResolution(sensorIndoor, 10);

  display.setCursor(10, 20);
  if (deviceCount >= 1) {
    display.println("1Wire Sensor found");
  } else {
    display.setCursor(10, 20);
    display.println("No 1Wire Sensor");
  }


  display.display();
  delay(bootTime);

  display.setTextColor(0xFFFF, 0);
  display.setCursor(10, 20);
  display.println("                     ");
  display.display();
  display.setTextColor(SSD1306_WHITE);

  if (sensors.isConnected(sensorOutdoor)) {
    //sprintf(oneWireDevices, "Tempsensors: %01d", deviceCount);
    //display.println(oneWireDevices);

    display.setCursor(10, 20);
    display.println("Outdoor Connected");
  } else {
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(10, 20);
    display.println("Error");
  }
  display.display();
  delay(bootTime);
  display.setTextColor(0xFFFF, 0);
  display.setCursor(10, 20);
  display.println("                     ");
  display.display();

  if (sensors.isConnected(sensorIndoor)) {
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(10, 20);
    display.println("Indoor Connected");
  } else {
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(10, 20);
    display.println("Error");
  }
}


void DS18B20() {
  //sensors.requestTemperatures();
  oneWire.begin(2);
  sensors.begin();
  delay(10);
  sensors.requestTemperaturesByAddress(sensorOutdoor);
  tempOutdoor1 = sensors.getTempC(sensorOutdoor);
  delay(50);
  oneWire.reset();
  oneWire.begin(2);
  sensors.begin();
  delay(10);
  sensors.requestTemperaturesByAddress(sensorIndoor);
  tempIndoor1 = sensors.getTempC(sensorIndoor);
}