void create_vacuum_new(int inhale_time){  
//  Serial.println();
  Serial.println("Going to Hose End");
  static unsigned long cycle_count_HE = 0;
  int period = 30;
  int val = 0;
  unsigned long time_now = 0;
  digitalWrite(motor_direction, MOTOR_DIRECTION_TO_CREATE_A_VACUUM); //HD
  int start_time = millis();
  timerWrite(timer, 0); //reset timer 
  timerAlarmEnable(timer);
  unsigned long phase_start = millis();
  digitalWrite(enable_motor, MTR_RUN);
//  Serial.println("Go to Wait for the sensor.");
  cycle_count_HE = wait_for_End_sensor(Vacuum_Limit_Sensor);
//  Serial.println("We are done waiting. Give brake pulse.");
  unsigned long phase_duration = millis() - phase_start;
  digitalWrite(motor_direction, !MOTOR_DIRECTION_TO_CREATE_A_VACUUM);
  time_now = millis();
  while(millis() < time_now + period){
  } 
  digitalWrite(enable_motor, MTR_STOP);
  timerAlarmDisable(timer);
  Serial.print("Cycles =   "); Serial.println(Cycles); 
  int end_time = millis();
  int remain_inhale_time = inhale_time - (end_time - start_time);
  if (remain_inhale_time > 0) delay(remain_inhale_time);    
//  Serial.println("Done with going to Hose End.");  
}
