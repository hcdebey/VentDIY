void vacuum_jog(){    
//HD 13  digitalWrite(13, HIGH); //turn on  
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
  
  int proximityADC = analogRead(Vacuum_Limit_Sensor);
  Serial.print("V raw = ");
  Serial.println(proximityADC);
  float proximityV = (float)proximityADC * 5.0 / 4095.0;
  Serial.print("V cal = ");
  Serial.println(proximityV);

//HD 13  digitalWrite(13, LOW); //turn on  
}
void return_jog(){     
//HD 13  digitalWrite(13, HIGH); //turn on  
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
  Serial.print("Cycles xxx = ");
  Serial.println(Cycles);
//HD 13  digitalWrite(13, LOW); //turn on  
}
