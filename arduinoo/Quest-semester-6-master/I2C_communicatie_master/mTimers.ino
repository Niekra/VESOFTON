void mTimer()
{
  // Timer0 is already used for millis()
  OCR0A = 0xAF;
  TIMSK0 |= _BV(OCIE0A);
}


// Interrupt is called once a millisecond, 
SIGNAL(TIMER0_COMPA_vect) 
{
  timer0_counter++;
  if(timer0_counter > 2000000000){
    timer0_counter = 0;
  }
  modus_timer++;
  if(modus_timer > 2000000000){
    modus_timer = 0;
  }
}
