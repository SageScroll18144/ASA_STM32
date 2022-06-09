double altitude(){
  ll delta_time = millis()-init_time;
  return accel*delta_time*delta_time;
}
