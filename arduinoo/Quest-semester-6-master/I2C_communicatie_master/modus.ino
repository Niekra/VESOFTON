void check_modus(){
  char p;
  switch(users[currentUser].modus)
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
          delay(30);
          p = 'P';
          sendMP3Command(p, 0);
          ampoff();
          delay(30);
          p = 'a'; 
          light_manager(p, 0);
          users[currentUser].vib_modus = 1;
          vib_on();
        }else if(modus_state == 1)
        {
          delay(30);
          p = 'p';
          sendMP3Command(p, 0);
          ampon();
          users[currentUser].vib_modus = 0;
          vib_off();
        }else if(modus_state == 2)
        {
          delay(30);
          p = 'P';
          sendMP3Command(p, 0);
          ampoff();
          delay(30);
          p = 'a'; 
          light_manager(p, 1);

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
          delay(30);
          p = 'P';
          sendMP3Command(p, 0);
          ampoff();
          users[currentUser].vib_modus = 1;
          vib_on();
        }else if(modus_state == 1)
        {
          delay(30);
          p = 'p';
          sendMP3Command(p, 0);
          ampon();
          users[currentUser].vib_modus = 0;
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
      
      p = 'a';      
      if(check_switch_timer() == 1)
      {
        if(modus_state == 0)
        {
          delay(30);
          light_manager(p, 0);
          users[currentUser].vib_modus = 1;
          vib_on();
        }else if(modus_state == 1)
        {
          delay(30);
          light_manager(p, 1);
          users[currentUser].vib_modus = 0;
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
          delay(30);
          p = 'P';
          sendMP3Command(p, 0);
          ampoff();
          delay(30);
          p = 'a'; 
          light_manager(p, 1);
          users[currentUser].vib_modus = 1;
          vib_on();
        }else if(modus_state == 1)
        {
          delay(30);
          p = 'a'; 
          light_manager(p, 0);
          users[currentUser].vib_modus = 0;
          vib_off();
          delay(30);
          p = 'p';
          sendMP3Command(p, 0);
          ampon();
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
          delay(30);
          p = 'p';
          sendMP3Command(p, 0);
          ampon();
          delay(30);
          p = 'a'; 
          light_manager(p, 0);
          users[currentUser].vib_modus = 1;
          vib_on();
        }else if(modus_state == 1)
        {
          delay(30);
          p = 'a'; 
          light_manager(p, 1);
          users[currentUser].vib_modus = 0;
          vib_off();
          delay(30);
          p = 'P';
          sendMP3Command(p, 0);
          ampoff();
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
          delay(30);
          p = 'p';
          sendMP3Command(p, 0);
          ampon();
          delay(30);
          p = 'a'; 
          light_manager(p, 1);
          users[currentUser].vib_modus = 0;
          vib_off();
        }else if(modus_state == 1)
        {
          delay(30);
          p = 'a'; 
          light_manager(p, 0);
          ampoff();
          users[currentUser].vib_modus = 1;
          vib_on();
          delay(30);
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
          delay(30);
          p = 'p';
          sendMP3Command(p, 0);
          ampon();
          delay(30);
          p = 'a'; 
          light_manager(p, 0);
        }else if(modus_state == 1)
        {
          delay(30);
          p = 'a'; 
          light_manager(p, 1);
          delay(30);
          p = 'P';
          sendMP3Command(p, 0);
          ampoff();
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
          delay(30);
          p = 'a'; 
          light_manager(p, 1);
          users[currentUser].vib_modus = 0;
          vib_off();
        }else if(modus_state == 1)
        {
          delay(30);
          p = 'a'; 
          light_manager(p, 0);
          users[currentUser].vib_modus = 1;
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
          delay(30);
          p = 'p';
          sendMP3Command(p, 0);
          ampon();
          users[currentUser].vib_modus = 0;
          vib_off();
        }else if(modus_state == 1)
        {
          users[currentUser].vib_modus = 1;
          vib_on();
          delay(30);
          p = 'P';
          ampoff();
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
      users[currentUser].modus = ints;
      modus_timer = 0;
      if(users[currentUser].modus == 0)
      {
        //TODO userSetup? whould work
        setupUser();
      }
      if(users[currentUser].modus == 1)
      {
        delay(50);
        sendMP3Command('W', 0);
        max_state = 2;
        users[currentUser].vib_modus = 1;
        vib_on();
        delay(30);
        p = 'a';
        light_manager(p, 0);
        delay(30);
        p = 'P';
        sendMP3Command(p, 0);
        ampoff();
      }
      if(users[currentUser].modus == 2 || users[currentUser].modus == 3)
      {
        delay(50);
        sendMP3Command('W', 0);
        max_state = 1;
        users[currentUser].vib_modus = 1;
        vib_on();
      }else if(users[currentUser].modus == 4)
      {
        delay(50);
        sendMP3Command('W', 0);
        max_state = 1;
        users[currentUser].vib_modus = 1;
        vib_on();
        delay(30);
        p = 'a';
        light_manager(p, 1);
        delay(30);
        p = 'P';
        sendMP3Command(p, 0);
        ampoff();
      }else if(users[currentUser].modus == 5) //TODO: (geluid + trillen) / licht
      {
        delay(50);
        sendMP3Command('W', 0);
        max_state = 1;
        users[currentUser].vib_modus = 1;
        vib_on();
        delay(30);
        p = 'p';
        sendMP3Command(p, 0);
        ampon();
        delay(30);
        p = 'a';
        light_manager(p, 0);
      }else if(users[currentUser].modus == 6) //TODO: (licht+geluid) / trillen
      {
        delay(50);
        sendMP3Command('W', 0);
        max_state = 1;
        users[currentUser].vib_modus = 0;
        vib_off();
        delay(30);
        p = 'p';
        sendMP3Command(p, 0);
        ampon();
        delay(30);
        p = 'm';
        light_manager(p, 1);
      }else if(users[currentUser].modus == 7) //TODO: (geluid/licht) + trillen
      {
        delay(50);
        sendMP3Command('W', 0);
        max_state = 1;
        users[currentUser].vib_modus = 1;
        vib_on();
        delay(30);
        p = 'p';
        sendMP3Command(p, 0);
        ampon();
        delay(30);
        p = 'a';
        light_manager(p, 0);
      }else if(users[currentUser].modus == 8) //TODO: (licht/trillen) + geluid
      {
        delay(50);
        sendMP3Command('W', 0);
        max_state = 1;
        users[currentUser].vib_modus = 0;
        vib_off();
        delay(30);
        p = 'p';
        sendMP3Command(p, 0);
        ampon();
        delay(30);
        p = 'a';
        light_manager(p, 1);
      }else if(users[currentUser].modus == 9) //TODO: (geluid/trillen) + licht!
      {
        delay(50);
        sendMP3Command('W', 0);
        max_state = 1;
        users[currentUser].vib_modus = 0;
        vib_off();
        delay(30);
        p = 'p';
        sendMP3Command(p, 0);
        ampon();
        delay(30);
        p = 'a';
        light_manager(p, 1);
      }
      break;
    case 'd':
      users[currentUser].modus_duration = ints * 1000;
      break;
  }
  //EEPROM_writeAnything(0, users);
  EEPROM.put(0,user1);
  EEPROM.put(75,user2);
  EEPROM.put(150,user3);
  EEPROM.put(225,user4);
  EEPROM.put(300,user5);
}

int check_switch_timer(){
  if(modus_timer > users[currentUser].modus_duration){
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

