void setup() {
/*
cli();//stop interrupts

//set timer1 interrupt at 1Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 15624;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A); 

// sei();//allow interrupts
*/
 
  // initialize the digital pin as an output.
 pinMode(13, OUTPUT);
// digitalWrite(led, HIGH);
 //pinMode(vacuum_limit_switch, INPUT);
 //pinMode(return_limit_switch, INPUT);
 pinMode(motor_direction, OUTPUT);
 pinMode(enable_motor, OUTPUT);
 digitalWrite(enable_motor, MTR_STOP);
 pinMode(light_enable, OUTPUT);
 digitalWrite(light_enable, HIGH);
 
 pinMode(Vacuum_Limit_Sensor, INPUT);
 pinMode(Return_Limit_Sensor, INPUT);
 pinMode(Over_Run_Interrupt, INPUT);
// attachInterrupt(digitalPinToInterrupt(Over_Run_Interrupt), piston_over_run_interrupt, LOW); 
// attachInterrupt(0, piston_over_run_interrupt, LOW); 

 Serial.begin(115200);
 Serial.println("In setup"); //HD
//   playground();
//   initialize_piston_position();
}
