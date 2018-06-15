void vib_on(){
  analogWrite(TRIL_MOTOR1, vib_intensity);
  analogWrite(TRIL_MOTOR2, vib_intensity);
  vib_status = 1;
  timer0_counter = 0;
  return;
}

void vib_off(){
  analogWrite(TRIL_MOTOR1, LOW);
  analogWrite(TRIL_MOTOR2, LOW);
  vib_status = 0;
  timer0_counter = 0;
  return;
}

void vib_toggle(){
  if(vib_status == 1){
    vib_on();
    vib_status = 0;
  }else
  {
    vib_off();
    vib_status = 1;
  }
}

void set_vib_intensity(int ints){
  vib_intensity = (255 * ints/100);

    if(vib_status == 1){
      vib_on();
    }
   
}

void vib_manager(char c, int ints){
  switch(c) {
    case 'o':
      vib_on();
      break;
    case 'f':
      vib_off();
      break;
    case 'i':
      set_vib_intensity(ints);
      break;
    case 'm':
      vib_modus = ints;
      break;  
    case 'v':
      vib_on_duration = 1000 * ints;
      break;
    case 'z':
      vib_off_duration = 1000 * ints;
      break;          
  }
}

void check_vib()
{
  if(vib_modus != 0)
  {
    if(vib_status == 0)
    {
      if(timer0_counter > vib_off_duration)
      {
        //Serial.print("x");
        vib_on();
      }
    }else if(vib_status == 1)
    {
      if(timer0_counter > vib_on_duration)
      {
        //Serial.print("y");
        vib_off();
      }
    }
  }
}


