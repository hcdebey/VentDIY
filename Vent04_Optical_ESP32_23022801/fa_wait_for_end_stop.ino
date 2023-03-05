bool wait_for_End_sensor(int Sensor) {
  //  Serial.println("We are in the Wait.");
  const int number_samples_for_average = 3;
  const float multiple_of_average = 1.1;

  const int ME = 36;
  const int HE = 39;
  unsigned long average = 0;
  unsigned long cycle_count = 0;
  unsigned long sample[number_samples_for_average + 1] = {1, 2, 3};
  unsigned long overshoot_counter = 0;
  static unsigned long ME_overshoot_counter = 0;
  static unsigned long HE_overshoot_counter = 0;
  static unsigned long ME_average = 0;
  static unsigned long HE_average = 0;
  static unsigned long ME_cycle_count = 0;
  static unsigned long HE_cycle_count = 0;
  static unsigned long ME_sample[number_samples_for_average + 1] = {4, 5, 6};
  static unsigned long HE_sample[number_samples_for_average + 1] = {7, 8, 9};
  //    Serial.print("From the top "); Serial.print(sample[0]); Serial.print(" "); Serial.print(sample[1]); Serial.print(" "); Serial.print(sample[2]); Serial.println(" ");

  if (Sensor == ME) {
    overshoot_counter = ME_overshoot_counter;
    average = ME_average;
    cycle_count = ME_cycle_count;
    for (int i = 0; i < number_samples_for_average; i++)
    {
      sample[i] = ME_sample[i];
    }
  } else {
    overshoot_counter = HE_overshoot_counter;
    average = HE_average;
    cycle_count = HE_cycle_count;
    for (int i = 0; i < number_samples_for_average; i++)
    {
      sample[i] = HE_sample[i];
    }
  }
  /*  Serial.print("After ME/HE load "); Serial.print(sample[0]); Serial.print(" "); Serial.print(sample[1]); Serial.print(" "); Serial.print(sample[2]); Serial.println(" ");
    Serial.print(sample[0]); Serial.print(" "); Serial.print(sample[1]); Serial.print(" "); Serial.print(sample[2]); Serial.println(" ");
    Serial.print("average coming in is = "); Serial.println(average);*/
  Serial.print("cycle_count = "); Serial.println(cycle_count);

  const int GPIO_pin_count = 50; //34 is the number of pins for the ESP32. There is an array for each pin although we only use 2 pins. This allows for changing the pins.
  //  Serial.print("cycle_count-01 = "); Serial.println(cycle_count[Sensor][0]);
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
  do {
    proximityADC = analogRead(Sensor); // Read the sensor value.
    proximityV = (float)proximityADC * 3.3 / 4095.0; // Convert sensor value to voltage.
    duration_time = millis() - start_time;
    //    if(cycle_count[Sensor][0] >= number_samples_for_average +2) { // We now have enough duration samples to be able to compare the current duration with the average duration.
    if (cycle_count >= number_samples_for_average + 2) { // We now have enough duration samples to be able to compare the current duration with the average duration.
      if (first_entry) {
        first_entry = false;
      }
      if (duration_time > average * multiple_of_average) { // There was an overshoot.
        overshoot_counter++;
        Serial.print(Sensor); Serial.print(" Time too long at "); Serial.print(duration_time); Serial.print(". Average is "); Serial.print(average);
        Serial.print(" -overshoot_counter = "); Serial.println(overshoot_counter);
        Serial.println("DXDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD");
        int m = 0;
        int n = 0;
/*        do {
          do {
            Serial.print("D");
            n++;
          } while (n < 100);
          n = 0;
          Serial.println();
          m++;
        } while (m < 5);
        m = 0;*/
        cycle_count++;
        if (Sensor == ME) {
          ME_overshoot_counter = overshoot_counter;
          ME_average = average;
          ME_cycle_count = cycle_count;
          for (int i = 0; i < number_samples_for_average; i++)
          {
            ME_sample[i] = sample[i];
          }
        } else {
          HE_overshoot_counter = overshoot_counter;
          HE_average = average;
          HE_cycle_count = cycle_count;
          for (int i = 0; i < number_samples_for_average; i++)
          {
            HE_sample[i] = sample[i];
          }
        }
        return (true);
      }
    }
  } while (proximityV > trigger_voltage); // If this is true, then we have reached the trigger voltage and the travel can be stopped. But first we need to calculate the average duration_time.
  //#####################################################################################################################3
  Serial.print(Sensor); Serial.print(" _duration_time = "); Serial.println(duration_time);
  if (cycle_count < number_samples_for_average) {                        // For the first cycles, load the array of samples with samples. After that, we can start calculating the average duration.
    sample[cycle_count] = duration_time;
    //    Serial.print(sample[0]); Serial.print(" "); Serial.print(sample[1]); Serial.print(" "); Serial.print(sample[2]); Serial.println(" ");
  } else {
    j = 0;                                                                             // For each cycle, calculate the new average cycle time.
    sample_total = 0;
//    Serial.print(sample[0]); Serial.print(" "); Serial.print(sample[1]); Serial.print(" "); Serial.print(sample[2]); Serial.println(" ");
    do {
      sample_total = sample_total + sample[j+1];
//      Serial.print("ST = "); Serial.println(sample_total);
      sample[j] = sample[j + 1];
      j += 1;
    } while (j < number_samples_for_average - 1);
    sample[j] = duration_time;
    sample_total = sample_total + sample[j];
    average = int( float ((sample_total) / number_samples_for_average));
//        Serial.print(Sensor); Serial.print(" -sample_total = "); Serial.println(sample_total); 
//        Serial.print(", -duration_time = "); Serial.println(duration_time);
    Serial.print(Sensor); Serial.print(" -average = "); Serial.println(average); // Serial.println();
  }

  //  Serial.print("cycle_count of the Sensor = "); Serial.println(cycle_count[Sensor][0]);
  cycle_count++;
  if (Sensor == ME) {
    ME_overshoot_counter = overshoot_counter;
    ME_average = average;
    ME_cycle_count = cycle_count;
    for (int i = 0; i < number_samples_for_average; i++)
    {
      ME_sample[i] = sample[i];
    }
    Serial.print(Sensor); Serial.print(" -overshoot_counter = "); Serial.println(overshoot_counter); Serial.println(" "); //Serial.println("wjljle");
  } else {
    HE_overshoot_counter = overshoot_counter;
    HE_average = average;
    HE_cycle_count = cycle_count;
    for (int i = 0; i < number_samples_for_average; i++)
    {
      HE_sample[i] = sample[i];
    }
    Serial.print(Sensor); Serial.print(" -overshoot_counter = "); Serial.print(overshoot_counter); Serial.println(" "); Serial.println(" ");
  }
  //           Serial.print(sample[0]); Serial.print(" "); Serial.print(sample[1]); Serial.print(" "); Serial.print(sample[2]); Serial.println(" ");

  //  Serial.print(Sensor); Serial.print(" average going out is = "); Serial.println(average); Serial.println();

  return (true);
}
