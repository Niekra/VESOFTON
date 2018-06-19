void user_manager(char c, int ints)
{
  switch(c)
  {
    case 'l':
      //TODO: load user data and send it to the app
      String str1, str2, str3, str4, str5, str6, str7 ,str8, str9, str10, str11, str12, str13, str14, str15,str16,str17,str18, strT;
      currentUser = ints; //Set the new user.
  
      str1 = String(users[currentUser].play_folder);
      str2 = String(users[currentUser].start_song);
      str3 = String(users[currentUser].modus_duration);
      str4 = String(users[currentUser].modus);
      str5 = String(users[currentUser].vib_onoff);
      str6 = String(users[currentUser].vib_intensity);
      str7 = String(users[currentUser].vib_on_duration);
      str8 = String(users[currentUser].vib_off_duration);
      str9 = String(users[currentUser].vib_modus);
      str10 = String(users[currentUser].lit_status);
      str11 = String(users[currentUser].lit_modus);
      str12 = String(users[currentUser].eye_status);
      str13 = String(users[currentUser].eye_on_duration);
      str14 = String(users[currentUser].eye_off_duration);
      str15 = String(users[currentUser].eye_intensity);
      str16 = String(users[currentUser].volume);
      str17 = String(users[currentUser].s_status);
      str18 = String(users[currentUser].s_modus);
    
      strT ="a"+str1+","+str2+","+str3+","+str4+","+str5+","+str6+","+str7+","+str8+","+str9+","+str10+","+str11+","+str12+","+str13+","+str14+","+str15+","+str16+","+str17+","+str18+"!";
      //Serial.println(strT);
      int leng = strT.length();
      char sBuffer[leng];
      strT.toCharArray(sBuffer, leng+1);
      Serial.println(sBuffer);
      
      BTserial.write(sBuffer); 
      //Todo refresh all settings.
      //EEPROM_writeAnything(0, users);
      setupUser();
      
      break;
  }
}

void setupUser()
{
  delay(100);
  sendMP3Command('W', 0);
  delay(100);
  sendMP3Command('v', users[currentUser].volume);

  light_manager('a', users[currentUser].lit_status);
  light_manager('b', users[currentUser].lit_modus);
  if(users[currentUser].eye_status == 1)
  {
    light_manager('m', 0);
  }else
  {
    light_manager('n', 0);
  }
  light_manager('o', users[currentUser].eye_intensity);
  light_manager('q', users[currentUser].eye_on_duration/1000);
  light_manager('r', users[currentUser].eye_off_duration/1000);
    
  if(users[currentUser].modus == 0)
  {
    if(users[currentUser].vib_onoff == 1)
    {
      users[currentUser].vib_modus = 1;
      vib_on();
    }

    if(users[currentUser].s_status == 1)
    {
      delay(50);
      sendMP3Command('W', 0);
      delay(50);
      sendMP3Command('F', users[currentUser].play_folder);
      delay(50);
      sendMP3Command('k', users[currentUser].start_song);
      ampon();
    }else
    {
      delay(50);
      sendMP3Command('S', 0);
      ampoff();
    }
    
  }else
  {
    modus_manager('m', users[currentUser].modus);
  }
}


