//*************************************************************************************************
/*
Control of a cylinder and bellows powered by windshield wiper motors to create a vacuum for a negative pressure respiratory ventilator.
*/
// include library to read and write from flash memory
#include <EEPROM.h>
#define EEPROM_SIZE 64
// define the number of bytes you want to access
#define DEBUG
//#define EEPROM_SIZE 1
#define BaudRate 115200

int voltage[10] = {4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095};

const bool MOTOR_DIRECTION_TO_CREATE_A_VACUUM = false;
const bool MTR_RUN = HIGH;
const bool MTR_STOP = LOW;
const int Return_Limit_Sensor = A0;
const int Vacuum_Limit_Sensor = A3;
int motor_direction = 15;
int enable_motor = 2;
int analog_read_flag = 4;
int motor_on_time = 50;
int motor_off_time = 50;  
const bool OFF = false;
bool motor_state = OFF;
volatile bool temporarily_disable_ISR = false;
long Cycles = 0;
int address = 0;
int run_status_address = 10;
const int last_status_was = 15239;

// Variables for the interrupt timer.
volatile int interruptCounter;
int totalInterruptCounter;
hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

// Interrupt Service Routine (ISR)
void IRAM_ATTR onTimer() {
  portENTER_CRITICAL_ISR(&timerMux);
//  interruptCounter++;
  digitalWrite(enable_motor, MTR_STOP);
  Serial.println("Timer timed out.");
  Serial.println(digitalRead(motor_direction));
  halt();
  portEXIT_CRITICAL_ISR(&timerMux);
 
} 
 
void halt(){
    for (;;) {
     delay(1);
    }
}
