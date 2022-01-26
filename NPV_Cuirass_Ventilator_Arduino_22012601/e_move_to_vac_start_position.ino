void move_to_vac_start_position(int exhale_time){
  int period = 100;
  unsigned long time_now = 0;
  bool return_limit_switch_value = read_return_limit_sensor();
  E_write(20);
    digitalWrite(motor_direction, !MOTOR_DIRECTION_TO_CREATE_A_VACUUM);
    E_write(21);
    last_time = millis(); 
    int start_time = millis();
    TCNT1 = 0 ; //Reset Timer/Counter to zero
    start_interrupt_timer();
    digitalWrite(enable_motor, MTR_RUN);
    E_write(22);
    last_time = millis(); 
    do {
      return_limit_switch_value = read_return_limit_sensor();
    } while(!return_limit_switch_value);
    E_write(25);
       //if (serial_enabled) Serial.println("We saw the return sensor.");            

    last_time = millis(); 
    digitalWrite(motor_direction, MOTOR_DIRECTION_TO_CREATE_A_VACUUM);
    last_time = millis(); 
    time_now = millis();
    E_write(26);
    while(millis() < time_now + period){
/*      if(digitalRead(Over_Run_Interrupt) == 0) {
        digitalWrite(enable_motor, MTR_STOP);  //A zero voltage level inidicates that a limit switch has been tripped. The motor will be turned off and the program will be halted.
        halt();
      }*/
    }   
    E_write(27);
    digitalWrite(enable_motor, MTR_STOP);
    temporarily_disable_ISR = true;
    E_write(28);
    last_time = millis(); 
    int end_time = millis();
    int remain_exhale_time = exhale_time - (end_time - start_time);
    if (remain_exhale_time > 0) delay(remain_exhale_time);    
//    if (serial_enabled) Serial.println("Leaving Vacuum Direction");
}
