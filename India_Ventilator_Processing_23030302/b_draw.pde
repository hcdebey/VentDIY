void draw() {
  int max_delay_between_heartbeats = 4000; // milliseconds
  //background(0, 0, 0); // background color of window (r, g, b)
  if ( port.available() > 0) 
  {  // If data is available,
    val = port.readStringUntil('\n');         // read it and store it in val
    val = trim(val);
    loggerObject.log(hour() + ":" + minute() + ":" + second() + "  " + val);
  } else {
    val = null;
  }

}
