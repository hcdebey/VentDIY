void start_interrupt_timer(){  
  TCCR1A = 0;
  TCCR1B = 5;
//  bitSet(TCCR1B, CS10 | CS12);  // 256 prescaler
// See https://forum.arduino.cc/index.php?topic=118105.0 for explanation of two lines below.
 TIFR1 = OCF1A; // HD clear timer1 compare interrupt
 TIFR1 = OCF1B; // HD
  bitSet(TIMSK1, TOIE1); // timer overflow interrupt
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, 1);
  temporarily_disable_ISR = false;
}
 
ISR(TIMER1_OVF_vect) {
    E_write(31);

  if (temporarily_disable_ISR == false) {
    digitalWrite(enable_motor, MTR_STOP);
    signal_interrupt_timed_out();   
  } else {
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));  
  }
}

void signal_interrupt_timed_out() {
  E_write(32);
  temporarily_disable_ISR = true;
   do {
      digitalWrite(13, HIGH); //turn on  
//      E_write(33);
      for (unsigned int i = 0; i <= 65530; i++) {
        digitalRead(12);
      }
      digitalWrite(13, LOW); //turn on  
      for (unsigned int i = 0; i <= 65530; i++) {
        digitalRead(12);
      }
    } while(1); 
}
 
