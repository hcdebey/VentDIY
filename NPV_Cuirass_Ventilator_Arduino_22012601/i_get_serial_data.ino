void get_serial_data() {

  if(Serial.available()){ //id data available
  
    int val = Serial.read();
    switch (val) {
      case 'I':
//        digitalWrite(13, HIGH); //turn on
        vacuum_jog();
        break;
      case 'E':
//        digitalWrite(13, LOW); //turn off
        return_jog();
        break;
      default:
        // if nothing else matches, do the default
        // default is optional
      break;
    }
  }
}

void LightToggle(){
  light_state = !light_state;
  digitalWrite(light_enable, light_state); //Toggle the LED strip light. 
//  digitalWrite(13, light_state); //turn on  LED  
}
/*
void DataFromEEPROM(){
  int R_address= E_address +1;
  for (E_address = 0; E_address < 10; E_address++ ) {
//    EEPROM.write(E_address, E_address+10);
byte value = EEPROM.read(E_address);
byte val2= EEPROM.read(R_address);
    if (serial_enabled) Serial.print(E_address);
    if (serial_enabled) Serial.print(": ");
    if (serial_enabled) Serial.println(value);
    if (serial_enabled) Serial.print(val2);
    
  }
  clear_EEPROM();
}
*/
void DataFromEEPROM(){
  for (E_address = 0; E_address < 60; ) {
//    EEPROM.write(E_address, E_address+10);
    if (serial_enabled) Serial.print(E_address);
    for (int i = 0; i < 10; i++) {
      value = EEPROM.read(E_address+i);  
      if (serial_enabled) Serial.print(": ");
      if (serial_enabled) Serial.print(value);
    }
    E_address += 10;
    if (serial_enabled) Serial.println(" ");
  }
  clear_EEPROM();
}

void vacuum_jog(){    
  digitalWrite(13, HIGH); //turn on  
  digitalWrite(motor_direction, MOTOR_DIRECTION_TO_CREATE_A_VACUUM);
  digitalWrite(enable_motor, MTR_RUN);
  int period = 50;
  unsigned long time_now = millis();
  while(millis() < time_now + period){
/*    if(digitalRead(Over_Run_Interrupt) == 0) { //A zero voltage level inidicates that a limit switch has been tripped. The motor will be turned off and the program will be halted.
      digitalWrite(enable_motor, MTR_STOP);  
      halt();
    }*/
  }
  digitalWrite(enable_motor, MTR_STOP);
  digitalWrite(13, LOW); //turn on  
}
void return_jog(){     
  digitalWrite(13, HIGH); //turn on  
  digitalWrite(motor_direction, !MOTOR_DIRECTION_TO_CREATE_A_VACUUM);
  digitalWrite(enable_motor, MTR_RUN);
  int period = 50;
  unsigned long time_now = millis();
  while(millis() < time_now + period){
/*    if(digitalRead(Over_Run_Interrupt) == 0) { //A zero voltage level inidicates that a limit switch has been tripped. The motor will be turned off and the program will be halted.
      digitalWrite(enable_motor, MTR_STOP);  
      halt();
    }*/
  }
  digitalWrite(enable_motor, MTR_STOP);
  digitalWrite(13, LOW); //turn on  
}

void clear_EEPROM(){
  for (E_address = 0; E_address < 256; E_address++) {
    EEPROM.write(E_address, 0);
  }
  
}
/*
void E_write(byte code_position){
 //if (serial_enabled) Serial.print("First into E_write and the Eaddress is: ");
// if (serial_enabled) Serial.println(E_address); 
int R_address= E_address +1;
 EEPROM.write(E_address+=1, code_position);
 EEPROM.write(R_address+=1, 255);
 if (E_address > 50) {E_address = 0;}
  //EEPROM.write(E_address, 255);
 //if (serial_enabled) Serial.print("We just wrote the position to EProm. Now the address is: ");
 //if (serial_enabled) Serial.println(E_address);
 //if (serial_enabled) Serial.print("We are now going to write 255 marker at Eaddress of: ");
//if (serial_enabled) Serial.println(E_address);
  
// EEPROM.write(E_address, 255);
 //if (serial_enabled) Serial.print("We wrote the marker of 255 to address: ");
// if (serial_enabled) Serial.println(E_address); 
// if (serial_enabled) Serial.println("We will now exit. Next time in, we should have the same address as above.");
 
 // if (E_address > 50) {E_address = 0;} 
  // if (serial_enabled) Serial.println(E_address);
  //EEPROM.write(E_address, 255); 
  //if (serial_enabled) Serial.println(E_address);

}
*/
void E_write(byte code_position){
  EEPROM.write(E_address, code_position);
  E_address = E_address + 1;
  if (E_address > 49) {E_address = 0;}
  EEPROM.write(E_address, 255);
  if (E_address > 49) {E_address = 0;}
}
/*
ISR(TIMER1_COMPA_vect){  //change the 0 to 1 for timer1 and 2 for timer2
  digitalWrite(enable_motor, MTR_STOP);
  do {
    digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);              // wait for a second
    digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
    delay(1000);              // wait for a second
  } while(1);
   //interrupt commands here
}
*/
