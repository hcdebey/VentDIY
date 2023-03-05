void loop() {
  Serial.println("In loop");
  long run_status = EEPROMReadlong(run_status_address);
  if (run_status == last_status_was) {
    
  }
  long Cycles = 12340;
  int address = 0;
//  digitalWrite(motor_direction, HIGH);
  int val = 0;
//  val = 'R';
//  float inhale_time = 2000;
//  float exhale_time = 3000;
  float inhale_time = 1000;
  float exhale_time = 1000;
//  float inhale_time = 500;
//  float exhale_time = 500;
  do {
    if(Serial.available()){ //id data available
      
      val = Serial.read();
      #ifdef DEBUG #endif
      Serial.print("val here =  ");
      Serial.println( val);
      #endif
      switch (val) {
        case 'r': //Run
          break;
        case 's': //Stop
          break;
        case 'i': //Jog Up in Vacuum Direction
          Serial.println("I jog");
          vacuum_jog();
          break; 
        case 'e': //Jog Down in Return Direction
          Serial.println("E jog");
          return_jog();
          break;
        case 'R': //Run
          break;
        case 'S': //Stop
          break;
         case 'I': //Jog Up in Vacuum / exhale Direction
          Serial.println("I jog");
          vacuum_jog();
          break;
        case 'E': //Jog Down in Return / Exhale Direction
          Serial.println("E jog");
          return_jog();
          break;
        default:
          // if nothing else matches, do the default
          // default is optional
          if(val >= 110 && val <= 122) { // Calculate the Inhale time.
            exhale_time = val;
            exhale_time -= 110;
            exhale_time = exhale_time / 2 ;
            exhale_time = exhale_time * 1000 ; //Change to milliseconds.
            delay(exhale_time);
          } else if (val >= 100 && val <= 106) { // Calculate the Exhale time.
            inhale_time = val;
            inhale_time -= 100;
            inhale_time = inhale_time / 2 ;
            inhale_time = inhale_time * 1000 ; //Change to milliseconds.
            delay(inhale_time);
          }
          Serial.println(" Inhale / Exhale times have changed. ");
        break;
      }
      
    }
  } while (val != 'R' && val != 'r');
    #ifdef DEBUG 
    Serial.println("After the while");
    #endif
  val = 'R';

  int run_time;
  do {
   move_to_vac_start_position(exhale_time);

   if(Serial.available()){ //Check for "S" Stop signal.
     val = Serial.read();
     if (val == 'S'){
       break;
     }
   }
   create_vacuum_new(inhale_time);
  } while (val == 'R');
}
