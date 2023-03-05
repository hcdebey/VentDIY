void setup() {
// pinMode(13, OUTPUT);
// pinMode(motor_direction, OUTPUT);
// pinMode(enable_motor, OUTPUT);
 pinMode(motor_direction, OUTPUT);
 pinMode(enable_motor, OUTPUT);
 pinMode(analog_read_flag, OUTPUT);
 digitalWrite(enable_motor, MTR_STOP);
 pinMode(Vacuum_Limit_Sensor, INPUT);
 pinMode(Return_Limit_Sensor, INPUT);
 Serial.begin(BaudRate);
 EEPROM.begin(EEPROM_SIZE);
 Serial.println("In setup"); //HD
 Cycles = EEPROMReadlong(address);


// Setup for Interrupt Timer. 
// See: https://techtutorialsx.com/2017/10/07/esp32-arduino-timer-interrupts/  
 timer = timerBegin(0, 80, true); //Timer base frequency is 80 MHz. The second argument, 80, prescales the timer to give a signal every 1 microsecond.
 timerAttachInterrupt(timer, &onTimer, true);
 timerAlarmWrite(timer, 2500000, true); //2,500,000 sets the timer to 2.5 seconds. An end-stop should be reached within 2.0 seconds so if longer than that the timer initiates the ISR routine.
// timerAlarmEnable(timer);
}
