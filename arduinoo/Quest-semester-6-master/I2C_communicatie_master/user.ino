void user_manager(char c, int ints)
{
  Serial.println('x');
  switch(c)
  {
    case 'l':
      //TODO: load user data and send it to the app
      String str1, str2, str3, str4, str5, str6, str7 ,str8, str9, str10, str11, str12, str13, str14, str15,str16,str17,str18, strT;
      currentUser = ints; //Set the new user.

      //Get all the user data as string for easy processing
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

      //Build output string.
      strT ="a"+str1+","+str2+","+str3+","+str4+","+str5+","+str6+","+str7+","+str8+","+str9+","+str10+","+str11+","+str12+","+str13+","+str14+","+str15+","+str16+","+str17+","+str18+"!";
      //Serial.println(strT);
      //Confert string to char array
      int leng = strT.length();
      char sBuffer[leng];
      strT.toCharArray(sBuffer, leng+1);

      //Send Bluetooth buffer.
      BTserial.write(sBuffer); 

      Serial.print("User information: ");
      Serial.println(sBuffer);

      setupUser(); //Setup user settings.
      
      break;
  }
}

void setupUser()
{
  //Setup mp3 module
  delay(100);
  sendMP3Command('W', 0);
  delay(100);
  sendMP3Command('v', users[currentUser].volume);

  //Setup light manager
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

  //Code to run if the modus is 0  
  if(users[currentUser].modus == 0)
  {
    if(users[currentUser].vib_onoff == 1)   //check vib settings
    {
      users[currentUser].vib_modus = 1;
      vib_on();
    }

    if(users[currentUser].s_status == 1)
    {
      //Play sonf of the users folder.
      delay(50);
      sendMP3Command('W', 0);
      delay(50);
      sendMP3Command('F', users[currentUser].play_folder);
      delay(50);
      sendMP3Command('k', users[currentUser].start_song);
      ampon();
    }else
    {
      //Set the mp3 module in sleep.
      delay(50);
      sendMP3Command('S', 0);
      ampoff();
    }
    
  }else
  {
    //Modus manager will do the rest.
    modus_manager('m', users[currentUser].modus);
  }
}


