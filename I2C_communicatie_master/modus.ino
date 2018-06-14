void check_modus(){
  char p;
  switch(modus)
  {
    case 0:
      //TODO: modus functions
      check_vib();
      break;
    case 2:
      //TODO: modus functions
      max_state = 1;
      if(modus_state == 0)
      {
        check_vib();
      }
            
      if(check_switch_timer() == 1)
      {
        if(modus_state == 0)
        {
          p = 'P';
          sendMP3Command(p);
          vib_modus = 1;
          vib_on();
        }else if(modus_state == 1)
        {
          p = 'p';
          sendMP3Command(p);
          vib_modus = 0;
          vib_off();
        }
      }
      break;
  }
}

void modus_manager(char c, int ints){
  switch(c){
    case 'm':
      modus = ints;
      modus_timer = 0;
      if(modus == 2)
      {
        vib_modus = 1;
        vib_on();
      }
      break;
    case 'd':
      modus_timer = ints * 1000;
      break;
  }
}

int check_switch_timer(){
  if(modus_timer > modus_duration){
    if(modus_state == max_state)
    {
      modus_state = 0;
    }else
    {
      modus_state++;
    }
    modus_timer = 0;
    return 1;
  }
  return 0;
}

