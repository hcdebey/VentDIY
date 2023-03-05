  void move_to_vac_start_position(int exhale_time){
//  Serial.println();
  Serial.println("Going to Motor End");
  static unsigned long cycle_count_ME = 0;
  int period = 100;
  unsigned long time_now = 0;
  digitalWrite(motor_direction, !MOTOR_DIRECTION_TO_CREATE_A_VACUUM);
  int start_time = millis();
  timerWrite(timer, 0); //reset timer 
  timerAlarmEnable(timer);
  unsigned long phase_start = millis();
  digitalWrite(enable_motor, MTR_RUN);
//  Serial.println("Go to Wait for the sensor.");
  cycle_count_ME = wait_for_End_sensor(Return_Limit_Sensor);
//  Serial.println("We are done waiting. Give brake pulse.");
  digitalWrite(motor_direction, MOTOR_DIRECTION_TO_CREATE_A_VACUUM);
  time_now = millis();
  while(millis() < time_now + period){
    }   
  digitalWrite(enable_motor, MTR_STOP);
  timerAlarmDisable(timer);
  Serial.print("Cycles =   "); Serial.println(Cycles); 
 
   #ifdef DEBUG

   #endif
   Cycles = Cycles + 1;
   if((Cycles % 10) == 0){
     EEPROMWritelong(address,Cycles);
     EEPROM.commit();
   }    
    int end_time = millis();
    int remain_exhale_time = exhale_time - (end_time - start_time);
    if (remain_exhale_time > 0) delay(remain_exhale_time);    
//    Serial.println("Done with going to Motor End.");
}
