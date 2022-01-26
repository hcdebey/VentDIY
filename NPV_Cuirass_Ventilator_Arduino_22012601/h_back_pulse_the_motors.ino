void back_pulse_the_motors(int msec, bool reverse_motor_direction) {
    //if (serial_enabled) Serial.println("In back pulse.");
   // if (serial_enabled) Serial.println(msec);
   // if (serial_enabled) Serial.println(reverse_motor_direction);

  int period = msec;
  unsigned long time_now = 0;
  digitalWrite(motor_direction, reverse_motor_direction);
  while(millis() < time_now + period){
    if(digitalRead(Over_Run_Interrupt) == 0) { //A zero voltage level inidicates that a limit switch has been tripped. The motor will be turned off and the program will be halted.
      digitalWrite(enable_motor, LOW);  
      halt();
    }
  }

  
}
