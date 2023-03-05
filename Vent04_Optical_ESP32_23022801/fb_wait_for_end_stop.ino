/*unsigned long wait_for_End_sensor(int Sensor, unsigned long cycle_count) {
  Serial.println("We are in the Wait.");
  const int ME = 36;
  const int HE = 39;
  const int number_samples_for_average = 3;  
  const float multiple_of_average = 1.3;
  unsigned long new_average = 0;
  static unsigned long ME_average = 0;
  static unsigned long HE_average = 0;
  if(Sensor = ME) {
    new_average = ME_average;
  }else{
    new_average = HE_average;
  }

  
  const int GPIO_pin_count = 50; //34 is the number of pins for the ESP32. There is an array for each pin although we only use 2 pins. This allows for changing the pins.
  static unsigned long sample[GPIO_pin_count][number_samples_for_average]{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
//  static unsigned long cycle_count[GPIO_pin_count][1]{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; 
  static unsigned long average[GPIO_pin_count][1]{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; 
// cycle_count = cycle_count_from_calling_routine;
  Serial.print("cycle_count-01 = "); Serial.println(cycle_count);
  int sample_total;
  int i = 0;
  int j = 0;
  static bool first_entry = true;
  unsigned long average_duration_time = 0;
  int proximityADC = 0;
  float proximityV = 0.0;
  unsigned long duration_time = 0; //Using unsigned variables and subtraction for the elapsed period the comparison will work even if/when millis() rolls over to zero https://forum.arduino.cc/t/using-millis-for-timing-a-beginners-guide/483573 
  unsigned long start_time = 0;
  float trigger_voltage = 1.0; // See "Ventilator 4 Acrylic Bring Up 23011601" for determination of voltage.
  start_time = millis();
  Serial.println("Before the do.");
  do {
    proximityADC = analogRead(Sensor); // Read the sensor value.
    proximityV = (float)proximityADC * 3.3 / 4095.0; // Convert sensor value to voltage.
    duration_time = millis() - start_time;
    Serial.print("cycle_count00 = "); Serial.println(cycle_count);
    if(cycle_count >= number_samples_for_average +2) { // We now have enough duration samples to be able to compare the current duration with the average duration.
      if (first_entry) {
        first_entry = false;
      }
      if (duration_time > average[Sensor][0] * multiple_of_average){ // The duration_time is longer than the average so we need to break out. Perhaps because the engager wasn't seen by the detector.
       Serial.println("Duration time was too long.");
       int m = 0;
       int n = 0;
       do {
         do {
           Serial.print("D");
           n++;
         } while (n<100);
         n=0;
         Serial.println();
         m++;
       } while (m < 5);
       m = 0;
       return(true); 
      }
    }
  } while(proximityV > trigger_voltage); // If this is true, then we have reached the trigger voltage and the travel can be stopped. But first we need to calculate the average duration_time.
  Serial.print("cycle_count01 = "); Serial.println(cycle_count);
  Serial.println("The trigger voltage has been detected.");
//  int sample_number = cycle_count;
//  sample[Sensor][sample_number] = duration_time;
  sample[Sensor][cycle_count] = duration_time;
  Serial.print("duration_time was = "); Serial.println(duration_time);
  Serial.print("cycle_count02 = "); Serial.println(cycle_count);
  if (cycle_count < number_samples_for_average +1) {                        // For the first cycles, load the array of samples with samples.
    Serial.print("cycle_count03a = "); Serial.println(cycle_count);
    sample[Sensor][cycle_count] = duration_time;
  } else {
    Serial.print("cycle_count03b = "); Serial.println(cycle_count);
    j = 0;                                                                             // For each cycle, calculate the new average cycle time.
    sample_total = 0;
    do {
      sample_total = sample_total + sample[Sensor][j];
      sample[Sensor][j] = sample[Sensor][j+1];
      j+=1;
    } while (j < number_samples_for_average);
    average[Sensor][0] = sample_total / number_samples_for_average;
  }
  Serial.print("cycle_count of the Sensor = "); Serial.println(cycle_count);
  cycle_count++;
  Serial.print("cycle_count of the Sensor after ++ = "); Serial.println(cycle_count);
  Serial.print(Sensor); Serial.print(", Average = "); Serial.println(average[Sensor][0]); 
  return(cycle_count);
}*/
