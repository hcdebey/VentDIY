void loop() {
  Serial.println("In loop");
  int val = 0;
  float inhale_time = 2000;
  float exhale_time = 3000;
//  playground();
// voltage();
  do {
    if(Serial.available()){ //id data available
      
      val = Serial.read();
      Serial.print("val =  ");
      Serial.println( val);
      switch (val) {
        case 'R': //Run
          break;
        case 'S': //Stop
          break;
        case 'L': //Toggle the lights
          LightToggle();
          break;
        case 'D': //Read the contents of the EEPROM
          DataFromEEPROM();
          break;
        case 'I': //Jog Up in Vacuum / exhale Direction
          Serial.println("I jog");
          vacuum_jog();
          if (serial_enabled) Serial.println("executed");
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
            if (serial_enabled) Serial.println("aaaaa");
            if (serial_enabled) Serial.println(exhale_time);
            exhale_time -= 110;
            if (serial_enabled) Serial.println(exhale_time);
            exhale_time = exhale_time / 2 ;
            if (serial_enabled) Serial.println(exhale_time);
            exhale_time = exhale_time * 1000 ; //Change to milliseconds.
            if (serial_enabled) Serial.println(exhale_time);            
            if (serial_enabled) Serial.println("bbbbb");
//            digitalWrite(13, HIGH); //turn on   
            delay(exhale_time);
//            digitalWrite(13, LOW); //turn on   
          } else if (val >= 100 && val <= 106) { // Calculate the Exhale time.
            inhale_time = val;
            if (serial_enabled) Serial.println("yyyyy");
            if (serial_enabled) Serial.println(inhale_time);
            inhale_time -= 100;
            if (serial_enabled) Serial.println(inhale_time);
            inhale_time = inhale_time / 2 ;
            if (serial_enabled) Serial.println(inhale_time);
            inhale_time = inhale_time * 1000 ; //Change to milliseconds.
            if (serial_enabled) Serial.println(inhale_time);            
            if (serial_enabled) Serial.println("xxxxx");
//            digitalWrite(13, HIGH); //turn on   
            delay(inhale_time);
//            digitalWrite(13, LOW); //turn on   
          }
        break;
      }
    }
  } while (val != 'R');
  val = 'R';

  int run_time;
//  get_serial_data();

  do {
   move_to_vac_start_position(exhale_time);

   if(Serial.available()){ //Check for "S" Stop signal.
     val = Serial.read();
     if (val == 'S'){
       digitalWrite(13, HIGH); //turn on   
       break;
     }
   }
//   run_time = 101400;
   create_vacuum_new(inhale_time);
//   create_vacuum(run_time);
  } while (val == 'R');
// voltage();
}

void voltage(){
  unsigned int Vin= analogRead(A2);
  float V_relle = ((Vin*(Tmax/1024))/coeff_pont);
  if (serial_enabled) Serial.print("V_relle");
  if (serial_enabled) Serial.print(" : ");
  if (serial_enabled) Serial.println(V_relle);
}
