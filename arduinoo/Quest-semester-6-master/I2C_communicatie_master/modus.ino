//Check if the mode state has changed and switch the pheriphals
void check_modus(){
  char p;
  switch(users[currentUser].modus)
  {
    case 0:
      //TODO: modus functions
      check_vib();
      break;
      
    case 1:
      //trillen/geluid/licht
      if(modus_state == 0)  //check vib
      {
        check_vib();
      }

      if(check_switch_timer() == 1) //check if mode needs to switch switches
      {
        if(modus_state == 0)      //Vibration sound+light off
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
        }else if(modus_state == 1)      //Sound light and vib off
        {
          delay(30);
          p = 'p';
          sendMP3Command(p, 0);
          ampon();
          users[currentUser].vib_modus = 0;
          vib_off();
        }else if(modus_state == 2)      //Lights soudn and vib off
        {
          delay(30);
          p = 'P';
          sendMP3Command(p, 0);
          ampoff();
          vib_off();
          delay(30);
          p = 'a'; 
          light_manager(p, 1);

        }
      }
      break;
    
    case 2:
      //TODO: trillen/licht
      if(modus_state == 0)    //check vib
      {
        check_vib();
      }
            
      if(check_switch_timer() == 1)
      {
        if(modus_state == 0)  //Vib on, sound off.
        {
          delay(30);
          p = 'P';
          sendMP3Command(p, 0);
          ampoff();
          users[currentUser].vib_modus = 1;
          vib_on();
        }else if(modus_state == 1)  //Vib off, sound on.
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
      if(modus_state == 0)      //check vib
      {
        check_vib();
      }
      
      p = 'a';      
      if(check_switch_timer() == 1)
      {
        if(modus_state == 0)        //lights off, vib on
        {
          delay(30);
          light_manager(p, 0);
          users[currentUser].vib_modus = 1;
          vib_on();
        }else if(modus_state == 1)    //lights on, vib off
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
        if(modus_state == 0)   //light + vib no sound
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
        }else if(modus_state == 1)    //Sound no vib + light
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
      if(modus_state == 0)    //check vib
      {
        check_vib();
      }
           
      if(check_switch_timer() == 1)
      {
        if(modus_state == 0)      //sound + vibration, no lights.
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
        }else if(modus_state == 1)    //lights no sound + vib
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
      if(modus_state == 1) // chech vib
      {
        check_vib();
      }
           
      if(check_switch_timer() == 1)   
      {
        if(modus_state == 0)    //light + sound
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
        }else if(modus_state == 1)      //vib no light+sound
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
        if(modus_state == 0)    //Sound no light
        {
          delay(30);
          p = 'p';
          sendMP3Command(p, 0);
          ampon();
          delay(30);
          p = 'a'; 
          light_manager(p, 0);
        }else if(modus_state == 1)    //Light no sound
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
        if(modus_state == 0) //light no vib
        {
          delay(30);
          p = 'a'; 
          light_manager(p, 1);
          users[currentUser].vib_modus = 0;
          vib_off();
        }else if(modus_state == 1)    //vib no light
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
        if(modus_state == 0)    //Sound no vib
        {
          delay(30);
          p = 'p';
          sendMP3Command(p, 0);
          ampon();
          users[currentUser].vib_modus = 0;
          vib_off();
        }else if(modus_state == 1)      //vib no sound
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


//Mange the differnt modus type commands
void modus_manager(char c, int ints){
  char p;
  switch(c){
    case 'm':
      users[currentUser].modus = ints;
      Serial.print("Mode selected: ");
      Serial.println(ints);
      modus_timer = 0;
      
      if(users[currentUser].modus == 0)   //Mode 0 use user info to setup system.
      {
        //TODO userSetup? whould work
        setupUser();
      }
      if(users[currentUser].modus == 1)   //Mode 1 vib/sound/light
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
      if(users[currentUser].modus == 2 || users[currentUser].modus == 3)    //mode 2+3 vib+sound, vib + light
      {
        delay(50);
        sendMP3Command('W', 0);
        max_state = 1;
        users[currentUser].vib_modus = 1;
        vib_on();
      }else if(users[currentUser].modus == 4)       //(light + vib) / sound
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
  //save user data
  EEPROM.put(0,users[0]);
  EEPROM.put(75,users[1]);
  EEPROM.put(150,users[2]);
  EEPROM.put(225,users[3]);
  //EEPROM.put(300,users[4]);
  Serial.println("userdata saved.");
}


//Change the mode_state when the timer is large then the duration.
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

