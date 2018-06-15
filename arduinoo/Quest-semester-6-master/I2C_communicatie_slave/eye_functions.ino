void eye_on(){
  analogWrite(EYE1, eye_intensity);
  analogWrite(EYE2, eye_intensity);
  eye_status = 1;
  eye_counter = 0;
  return;
}

void eye_off(){
  analogWrite(EYE1, LOW);
  analogWrite(EYE2, LOW);
  eye_status = 0;
  eye_counter = 0;
  return;
}

void eye_toggle(){
  if(eye_status == 1){
    eye_on();
    eye_status = 0;
  }else
  {
    eye_off();
    eye_status = 1;
  }
}

void set_eye_intensity(int ints){
  eye_intensity = (255 * ints/100);

    if(eye_status == 1){
      eye_on();
    }
   
}

void check_eye()
{
  if(eye_modus != 0)
  {
    if(eye_status == 0)
    {
      if(eye_counter > eye_off_duration)
      {
        //Serial.print("x");
        eye_on();
      }
    }else if(eye_status == 1)
    {
      if(eye_counter > eye_on_duration)
      {
        //Serial.print("y");
        eye_off();
      }
    }
  }
}
