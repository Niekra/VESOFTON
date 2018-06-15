void check_modus(){
  char p;
  switch(modus)
  {
    case 0:
      //TODO: modus functions
      check_vib();
      break;
      
    case 1:
      //TODO: trillen/geluid/licht
      if(modus_state == 0)
      {
        check_vib();
      }

      if(check_switch_timer() == 1)
      {
        if(modus_state == 0)
        {
          p = 'm'; 
          light_manager(p, 0);
          vib_modus = 1;
          vib_on();
        }else if(modus_state == 1)
        {
          p = 'p';
          sendMP3Command(p, 0);
          vib_modus = 0;
          vib_off();
        }else if(modus_state == 2)
        {
          p = 'P';
          sendMP3Command(p, 0);
          p = 'm'; 
          light_manager(p, 0);
        }
      }
      break;
    
    case 2:
      //TODO: modus functions
      if(modus_state == 0)
      {
        check_vib();
      }
            
      if(check_switch_timer() == 1)
      {
        if(modus_state == 0)
        {
          p = 'P';
          sendMP3Command(p, 0);
          vib_modus = 1;
          vib_on();
        }else if(modus_state == 1)
        {
          p = 'p';
          sendMP3Command(p, 0);
          vib_modus = 0;
          vib_off();
        }
      }
      break;

    case 3:
      //TODO: licht/ trilen
      if(modus_state == 0)
      {
        check_vib();
      }
      
      p = 'm';      
      if(check_switch_timer() == 1)
      {
        if(modus_state == 0)
        {
          light_manager(p, 0);
          vib_modus = 1;
          vib_on();
        }else if(modus_state == 1)
        {
          light_manager(p, 1);
          vib_modus = 0;
          vib_off();
        }
      }
      break;

    case 4:
      //TODO: (licht + trillen) / geluid
      if(modus_state == 0)
      {
        check_vib();
      }
           
      if(check_switch_timer() == 1)
      {
        if(modus_state == 0)
        {
          p = 'P';
          sendMP3Command(p, 0);
          p = 'm'; 
          light_manager(p, 1);
          vib_modus = 1;
          vib_on();
        }else if(modus_state == 1)
        {
          p = 'm'; 
          light_manager(p, 0);
          vib_modus = 0;
          vib_off();
          p = 'p';
          sendMP3Command(p, 0);
        }
      }
      break;

    case 5:
      //TODO: (geluid + trillen) / licht
      if(modus_state == 0)
      {
        check_vib();
      }
           
      if(check_switch_timer() == 1)
      {
        if(modus_state == 0)
        {
          p = 'p';
          sendMP3Command(p, 0);
          p = 'm'; 
          light_manager(p, 0);
          vib_modus = 1;
          vib_on();
        }else if(modus_state == 1)
        {
          p = 'm'; 
          light_manager(p, 1);
          vib_modus = 0;
          vib_off();
          p = 'P';
          sendMP3Command(p, 0);
        }
      }
      break;

    case 6:
      //TODO: (licht+geluid) / trillen
      if(modus_state == 1)
      {
        check_vib();
      }
           
      if(check_switch_timer() == 1)
      {
        if(modus_state == 0)
        {
          p = 'p';
          sendMP3Command(p, 0);
          p = 'm'; 
          light_manager(p, 1);
          vib_modus = 0;
          vib_off();
        }else if(modus_state == 1)
        {
          p = 'm'; 
          light_manager(p, 0);
          vib_modus = 1;
          vib_on();
          p = 'P';
          sendMP3Command(p, 0);
        }
      }
      break;

    case 7:
      //TODO: (geluid/licht) + trillen
      check_vib();
          
      if(check_switch_timer() == 1)
      {
        if(modus_state == 0)
        {
          p = 'p';
          sendMP3Command(p, 0);
          p = 'm'; 
          light_manager(p, 0);
        }else if(modus_state == 1)
        {
          p = 'm'; 
          light_manager(p, 1);
          p = 'P';
          sendMP3Command(p, 0);
        }
      }
      break;

    case 8:
      //TODO: (licht/trillen) + geluid
      if(modus_state == 1)
      {
        check_vib();
      }
           
      if(check_switch_timer() == 1)
      {
        if(modus_state == 0)
        {
          p = 'm'; 
          light_manager(p, 1);
          vib_modus = 0;
          vib_off();
        }else if(modus_state == 1)
        {
          p = 'm'; 
          light_manager(p, 0);
          vib_modus = 0;
          vib_on();
        }
      }
      break;

    case 9:
      //TODO: (geluid/trillen) + licht
      if(modus_state == 1)
      {
        check_vib();
      }
           
      if(check_switch_timer() == 1)
      {
        if(modus_state == 0)
        {
          p = 'P';
          sendMP3Command(p, 0);
          vib_modus = 1;
          vib_off();
        }else if(modus_state == 1)
        {
          vib_modus = 0;
          vib_on();
          p = 'p';
          sendMP3Command(p, 0);
        }
      }
      break;
  }
}

void modus_manager(char c, int ints){
  char p;
  switch(c){
    case 'm':
      modus = ints;
      modus_timer = 0;
      if(modus == 1)
      {
        max_state = 2;
        vib_modus = 1;
        vib_on();
        p = 'm';
        light_manager(p, 1);
        p = 'P';
        sendMP3Command(p, 0);
      }
      if(modus == 2 || modus == 3)
      {
        max_state = 1;
        vib_modus = 1;
        vib_on();
      }else if(modus == 4)
      {
        max_state = 1;
        vib_modus = 1;
        vib_on();
        p = 'm';
        light_manager(p, 1);
        p = 'P';
        sendMP3Command(p, 0);
      }else if(modus == 5) //TODO: (geluid + trillen) / licht
      {
        max_state = 1;
        vib_modus = 1;
        vib_on();
        p = 'p';
        sendMP3Command(p, 0);
        p = 'm';
        light_manager(p, 0);
      }else if(modus == 6) //TODO: (licht+geluid) / trillen
      {
        max_state = 1;
        vib_modus = 0;
        vib_off();
        p = 'p';
        sendMP3Command(p, 0);
        p = 'm';
        light_manager(p, 1);
      }else if(modus == 7) //TODO: (geluid/licht) + trillen
      {
        max_state = 1;
        vib_modus = 1;
        vib_on();
        p = 'p';
        sendMP3Command(p, 0);
        p = 'm';
        light_manager(p, 0);
      }else if(modus == 8) //TODO: (licht/trillen) + geluid
      {
        max_state = 1;
        vib_modus = 0;
        vib_off();
        p = 'p';
        sendMP3Command(p, 0);
        p = 'm';
        light_manager(p, 1);
      }else if(modus == 9) //TODO: (geluid/trillen) + licht!
      {
        max_state = 1;
        vib_modus = 0;
        vib_off();
        p = 'p';
        sendMP3Command(p, 0);
        p = 'm';
        light_manager(p, 1);
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

