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
  timer0_counter++;
  if(timer0_counter > 30000){
    timer0_counter = 0;
  }
  modus_timer++;
  if(modus_timer > 30000){
    modus_timer = 0;
  }
}
