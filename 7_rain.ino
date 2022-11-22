void rain_setup() {

  pinMode(rainDigitalPin, INPUT);
  pinMode(rainAnalogPin, INPUT);
}

/////////


void rain() {
  rainStatus = digitalRead(rainDigitalPin);
  rainAnalog = analogRead(rainAnalogPin);
  
  //Serial.println(rainAnalog);
  /*
  if (rainAnalog > 100) {
     rainStatus = digitalRead(rainDigitalPin);
  } else {
    Serial.println("No Rain");
  }
  */
}