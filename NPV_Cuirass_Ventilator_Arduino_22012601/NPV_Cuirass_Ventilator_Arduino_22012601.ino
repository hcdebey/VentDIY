//*************************************************************************************************
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

 
//*************************************************************************************************

#include <EEPROM.h>
#include <binary.h>

/*
Control of a cylinder and bellows powered by windshield wiper motors to create a vacuum for a negative pressure respiratory ventilator.

*/
#include <avr/sleep.h>
bool serial_enabled = false; //Used to turn serial communications on and off.
const float Tmax=20;
const float coeff_pont = 0.82456;
byte value; byte val2; 
int E_address = 0; int R_address; 
int led = 13;
const bool NOT_REACHED = false;
/*const bool MOTOR_DIRECTION_TO_CREATE_A_VACUUM = true;
const bool MTR_RUN = LOW;
const bool MTR_STOP = HIGH;*/

const bool MOTOR_DIRECTION_TO_CREATE_A_VACUUM = false;
const bool MTR_RUN = HIGH;
const bool MTR_STOP = LOW;

//const int QRD1114_PIN = A0;
const int Return_Limit_Sensor = A0;
const int Vacuum_Limit_Sensor = A1;
const int Over_Run_Interrupt = 2;

int light_enable = 6;
bool light_state = HIGH; //Lights turn on when the light_state is LOW. 
int motor_direction = 10;
int enable_motor = 9;
int motor_on_time = 50;
int motor_off_time = 50;  
const bool ON = true;
const bool OFF = false;
bool motor_state = OFF;
char brake_time = 0; 
unsigned long last_time = 0;
volatile bool temporarily_disable_ISR = false;

//*************************************************************************************************
#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C
//Adafruit_BME280 bme(BME_CS); // hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI

unsigned long delayTime;

 
//*************************************************************************************************
// the setup routine runs once when you press reset:

 
// the loop routine runs over and over again forever:

/*
void test_direction() {
     digitalWrite(motor_direction, MOTOR_DIRECTION_TO_CREATE_A_VACUUM);
     digitalWrite(enable_motor, HIGH);
    for (;;) {
     // statement block
    }

}
*/

void halt(){
    for (;;) {
     // statement block
    }
}
