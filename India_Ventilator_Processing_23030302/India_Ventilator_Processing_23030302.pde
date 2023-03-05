/* 13 Jun 2021. Add functionality to display the negative pressure level in the cuirass. */

import meter.*;
import controlP5.*;
import processing.serial.*; //library
Serial port; //do not change
String val;     // Data received from the serial port
String previous_val;
ControlP5 cp5; //create ControlP5 object
PFont font; //do not change
Textlabel myTextlabel0;
Textlabel myTextlabel1;
Textlabel myTextlabelA;
Textlabel myTextlabelB;
PrintWriter output;
int d = day();    // Values from 1 - 31
int m = month();  // Values from 1 - 12
int y = year();   // 2003, 2004, 2005, etc.
int Heartbeat_time = 0;
int Run_Start_Time = 0;
Logger loggerObject;  // don't use new here please
boolean Start_Heartbeat_Detection = false;
boolean Unintended_Stop = false;
boolean Running = false;
int Total_Run_Time_Today = 0;
int Elapsed_From_Filename;
int Time_Since_Last_Heartbeat = 0;
int Time_Of_Last_Heartbeat = 0;


String FileName = "Kabako Ventilator Log 0000 Seconds ";
String NewFileName;

int but_run=0;
String[] list;
int value_for_meter = 0;
Meter voltage_meter;

void setup() { //same as arduino program

  size(1366, 768); //window size, (width, height)
  port = new Serial(this, "COM7", 115200); //connected arduino port
  cp5 = new ControlP5(this); //do not change
  font = createFont("Georgia Bold", 20); //font for buttons and title
  voltage_meter = new Meter(this, 750,10);
  voltage_meter.setMinScaleValue(0);
  voltage_meter.setMaxScaleValue(5);
  Use_Same_Name_All_Day();
  /*  int Year_Short = year() - 2000;
   String Month = "0";
   int Month_Lead_Zero = month();
   if (Month_Lead_Zero < 10) {
   Month = Month + str(Month_Lead_Zero);
   } else {
   Month = str(Month_Lead_Zero);
   }
   
   String Day = "0";
   int Day_Lead_Zero = day();
   if (Day_Lead_Zero < 10) {
   Day = Day + str(Day_Lead_Zero);
   } else {
   Day = str(Day_Lead_Zero);
   }
   
   FileName = FileName + Year_Short + Month + Day + "01.csv";
   loggerObject  = new Logger (sketchPath("") + "\\Logs\\" + FileName);  // use new here please
   */
  cp5.addSlider("Inhale")
    .setPosition(300, 400)
    .setSize(60, 200)
    .setRange(0, 3)
    .setNumberOfTickMarks(7)
    .setFont(createFont("Georgia", 30))
    .setValue(2)
    ;

  cp5.addSlider("Exhale")
    .setPosition(500, 200)
    .setSize(60, 400)
    .setRange(0, 6)
    .setNumberOfTickMarks(13)
    .setFont(createFont("Georgia", 30))
    .setValue(3)
    ;

  cp5.addButton("L") //Light turn on and off. Toggle
    .setPosition(100, 650) //x and y upper left corner of button
    .setSize(70, 70) //(width, height)
    .setFont(font) //font
    .setColorBackground(color(255, 0, 0)) //background r,g,b
    .setColorForeground(color(0, 255, 0)) //mouse over color r,g,b
    .setColorLabel(color(0, 0, 0)) //text color r,g,b
    ;
  myTextlabel0 = cp5.addTextlabel("labelLight")
    .setText("LIGHT")
    .setPosition(100, 720)
    .setColorValue(0xffffff00)
    .setFont(createFont("Georgia", 20))
    ;

  cp5.addButton("D") // Get EEPROM data
    .setPosition(100, 550) //x and y upper left corner of button
    .setSize(70, 70) //(width, height)
    .setFont(font) //font
    .setColorBackground(color(255, 0, 0)) //background r,g,b
    .setColorForeground(color(0, 255, 0)) //mouse over color r,g,b
    .setColorLabel(color(0, 0, 0)) //text color r,g,b
    ;
  myTextlabel0 = cp5.addTextlabel("labelData")
    .setText("DATA")
    .setPosition(100, 620)
    .setColorValue(0xffffff00)
    .setFont(createFont("Georgia", 20))
    ;


  cp5.addButton("R") //Run the inhale and exhale cycles
    .setPosition(100, 50) //x and y upper left corner of button
    .setSize(120, 70) //(width, height)
    .setFont(font) //font
    .setColorBackground(color(255, 0, 0)) //background r,g,b
    .setColorForeground(color(0, 255, 0)) //mouse over color r,g,b
    .setColorLabel(color(0, 0, 0)) //text color r,g,b
    ;
  myTextlabel0 = cp5.addTextlabel("labelRun")
    .setText("RUN")
    .setPosition(132, 125)
    .setColorValue(0xffffff00)
    .setFont(createFont("Georgia", 20))
    ;

  cp5.addButton("S") //Stop the ventilator
    .setPosition(100, 150) //x and y upper left corner of button
    .setSize(120, 70) //(width, height)
    .setFont(font) //font
    .setColorBackground(color(255, 0, 0)) //background r,g,b
    .setColorForeground(color(0, 255, 0)) //mouse over color r,g,b
    .setColorLabel(color(0, 0, 0)) //text color r,g,b
    ;
  myTextlabel1 = cp5.addTextlabel("labelStop")
    .setText("STOP")
    .setPosition(132, 225)
    .setColorValue(0xffffff00)
    .setFont(createFont("Georgia", 20))
    ;

  cp5.addButton("I") //Jog up in Inhale/Vacuum direction
    .setPosition(1200, 510) //x and y upper left corner of button
    .setSize(60, 35) //(width, height)
    .setFont(font) //font
    .setColorBackground(color(255, 0, 0)) //background r,g,b
    .setColorForeground(color(0, 255, 0)) //mouse over color r,g,b
    .setColorLabel(color(0, 0, 0)) //text color r,g,b
    ;
  myTextlabelA = cp5.addTextlabel("labelVacJog")
    .setText("Jog Up In Vacuum Direction")
    .setPosition(1100, 550)
    .setColorValue(0xffffff00)
    .setFont(createFont("Georgia", 20))
    ;
  cp5.addButton("E") //Jog down in Exhale/Return direction
    .setPosition(1200, 580)
    .setSize(60, 35)
    .setFont(font)
    .setColorBackground(color(255, 0, 0))
    .setColorForeground(color(0, 255, 0))
    .setColorLabel(color(0, 0, 0))
    ;
  myTextlabelB = cp5.addTextlabel("labelRetJog")
    .setText("Jog Down In Return Direction")
    .setPosition(1090, 620)
    .setColorValue(0xffffff00)
    .setFont(createFont("Georgia", 20))
    ;
}
          
