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


void setup() { //same as arduino program

  size(1366, 768); //window size, (width, height)
  port = new Serial(this, "COM6", 115200); //connected arduino port
  cp5 = new ControlP5(this); //do not change
  font = createFont("Georgia Bold", 20); //font for buttons and title
  output = createWriter("positions.txt");



cp5.addSlider("Inhale")
     .setPosition(300,400)
     .setSize(60,200)
     .setRange(0,3)
     .setNumberOfTickMarks(7)
     .setFont(createFont("Georgia",30))
     .setValue(2)
     ;
  
cp5.addSlider("Exhale")
     .setPosition(500,200)
     .setSize(60,400)
     .setRange(0,6)
     .setNumberOfTickMarks(13)
     .setFont(createFont("Georgia",30))
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
                    .setPosition(100,720)
                    .setColorValue(0xffffff00)
                    .setFont(createFont("Georgia",20))
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
                    .setPosition(100,620)
                    .setColorValue(0xffffff00)
                    .setFont(createFont("Georgia",20))
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
                    .setPosition(132,125)
                    .setColorValue(0xffffff00)
                    .setFont(createFont("Georgia",20))
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
                    .setPosition(132,225)
                    .setColorValue(0xffffff00)
                    .setFont(createFont("Georgia",20))
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
                    .setPosition(1100,550)
                    .setColorValue(0xffffff00)
                    .setFont(createFont("Georgia",20))
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
                    .setPosition(1090,620)
                    .setColorValue(0xffffff00)
                    .setFont(createFont("Georgia",20))
                    ;


}

void draw() {

  background(0, 0, 0); // background color of window (r, g, b)
  
  if ( port.available() > 0) 
  {  // If data is available,
  val = port.readStringUntil('\n');         // read it and store it in val
  } 
  if (val != null) {
    if (val.equals(previous_val)) {
//    println("Yes, the values are the same."); 
    } else {
      println(val); //print it out in the console
      point(mouseX, mouseY);
      output.println(year() + "-" + month() + "-" + day() + " " + hour() + ":" + minute() + ":" + second() + " " + val); // Write the coordinate to the file
//      output.println(val); // Write the message to the file
      output.flush(); // Writes the remaining data to the file
    }

    previous_val = val;
  }
}

void R() {
  port.write('R');
}

void S() {
  port.write('S');
}

void I() {
  port.write('I');
}

void E() {
  port.write('E');
}

void L() {
  port.write('L');
}

void D() {
  port.write('D');
}

float previous_inhale_time = 0.0;
float previous_exhale_time = 0.0;

void Inhale(float time) {
  if (time != previous_inhale_time) {
    println("float time " + time);
    int inhale_time = (int) (time*2);
    inhale_time += 100;
    println(" int time " + inhale_time);
    port.write(inhale_time);  
  }
  previous_inhale_time = time;
}


void Exhale(float time) {
  if (time != previous_exhale_time) {
    println("float time " + time);
    int exhale_time = (int) (time*2);
    exhale_time += 110;
    println(" int time " + exhale_time);
    port.write(exhale_time);  
  }
  previous_exhale_time = time;
}
