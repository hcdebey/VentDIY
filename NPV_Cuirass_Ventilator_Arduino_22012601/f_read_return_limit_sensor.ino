bool read_return_limit_sensor() {
  bool switch_value;
  // Read in the ADC and convert it to a voltage:
  int proximityADC = analogRead(Return_Limit_Sensor);
  float proximityV = (float)proximityADC * 5.0 / 1023.0;
  if (serial_enabled) Serial.print("Ret "); 
  if (serial_enabled) Serial.println(proximityV);
//if (serial_enabled) Serial.println("#A");   

  if(proximityV > 2.0) { //Originally set at 1.0
    switch_value = false;
  } 
  else {
    switch_value = true;

  }
//if (serial_enabled) Serial.println("#B");   
//    if (serial_enabled) Serial.println((String)"Voltage of return sensor = "+ proximityV);

  return(switch_value);
}
