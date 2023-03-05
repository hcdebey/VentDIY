float previous_inhale_time = 0.0;
float previous_exhale_time = 0.0;

void Inhale(float time) {
  if (time != previous_inhale_time) {
//    println("float time " + time);
    int inhale_time = (int) (time*2);
    inhale_time += 100;
//    println(" int time " + inhale_time);
    port.write(inhale_time);  
  }
  previous_inhale_time = time;
}


void Exhale(float time) {
  if (time != previous_exhale_time) {
//    println("float time " + time);
    int exhale_time = (int) (time*2);
    exhale_time += 110;
//    println(" int time " + exhale_time);
    port.write(exhale_time);  
  }
  previous_exhale_time = time;
}
