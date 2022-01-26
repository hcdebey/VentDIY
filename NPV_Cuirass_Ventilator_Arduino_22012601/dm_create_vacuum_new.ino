void create_vacuum_new(int inhale_time){  
  int period = 100;
  unsigned long time_now = 0;
  bool vacuum_limit_switch_value = read_vacuum_limit_sensor();
  E_write(0);
  digitalWrite(motor_direction, MOTOR_DIRECTION_TO_CREATE_A_VACUUM); //HD
  E_write(1);
    last_time = millis(); 
    int start_time = millis();
//    OCR1A = 15624;// = (16*10^6) / (1*1024) - 1 (must be <65536)
//    sei();//allow interrupts
    TCNT1 = 0 ; //Reset Timer/Counter to zero
    start_interrupt_timer();
    digitalWrite(enable_motor, MTR_RUN);
  E_write(2);
    last_time = millis(); 
//    int loop_count = 0;
    do {
      vacuum_limit_switch_value = read_vacuum_limit_sensor();
 //   E_write(3);
//        Serial.print(bme.readPressure() / 100.0F);

    } while(!vacuum_limit_switch_value);
    E_write(5);
      // if (serial_enabled) Serial.println("We saw the vacuum sensor.");            

    last_time = millis(); 
    digitalWrite(motor_direction, !MOTOR_DIRECTION_TO_CREATE_A_VACUUM);
    last_time = millis(); 
    time_now = millis();
    E_write(6);
//    halt();
    while(millis() < time_now + period){
/*      if(digitalRead(Over_Run_Interrupt) == 0) {
        digitalWrite(enable_motor, MTR_STOP);  //A zero voltage level inidicates that a limit switch has been tripped. The motor will be turned off and the program will be halted.
        halt();
      }*/
    } 
    E_write(7);    
    digitalWrite(enable_motor, MTR_STOP);
    temporarily_disable_ISR = true;
    E_write(8);
    last_time = millis();
    int end_time = millis();
    int remain_inhale_time = inhale_time - (end_time - start_time);
    if (remain_inhale_time > 0) delay(remain_inhale_time);    
}
