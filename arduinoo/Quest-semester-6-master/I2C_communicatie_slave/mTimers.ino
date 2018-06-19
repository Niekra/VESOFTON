void mTimer()
{
  // Timer0 is already used for millis() - we'll just interrupt somewhere
  // in the middle and call the "Compare A" function below
  OCR0A = 0xAF;
  TIMSK0 |= _BV(OCIE0A);
}


// Interrupt is called once a millisecond, 
SIGNAL(TIMER0_COMPA_vect) 
{
  eye_counter++;
  if(eye_counter > 20000000){
    eye_counter = 0;
  }
}
