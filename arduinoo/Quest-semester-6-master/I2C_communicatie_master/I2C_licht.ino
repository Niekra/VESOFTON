void light_manager(char c, int ints){
  char t[5];
  String str;
  
  for(int z = 0; z<5; z++)
  {
    t[z] = '\0';
  }
  Wire.beginTransmission(8); // transmit to device #8
  Wire.write(c);        // sends one bytes
  if(ints != 0)
  {
    str = String(ints);
    str.toCharArray(t, 5);
    Wire.write(t); // sends one byte
    Serial.println(c);
    Serial.println(t);
  }else
  {
    Wire.write("0");
    Serial.println(c);
    Serial.println("0");
  }
  
  Wire.endTransmission();    // stop transmitting

  

  //Todo set light variables. and save.
  switch (c)
  {
    case 'a':
      users[currentUser].lit_status = (int)ints;
      break;
    case 'b':
      users[currentUser].lit_modus = (int)ints;
      break;
    case 'm':
      users[currentUser].eye_status = 1;
      break;
    case 'n':
      users[currentUser].eye_status = 0;
      break;
    case 'o':
      users[currentUser].eye_intensity= ints;
      break;
    case 'p':
      users[currentUser].eye_status = (ints);
      break;  
    case 'q':
      users[currentUser].eye_on_duration = 1000 * (int)ints;
      break;
    case 'r':
      users[currentUser].eye_off_duration = 1000 * (int)ints;
      break;      
  }
  delay(30);
  //EEPROM_writeAnything(0, users);
  EEPROM.put(0,user1);
  EEPROM.put(75,user2);
  EEPROM.put(150,user3);
  EEPROM.put(225,user4);
  EEPROM.put(300,user5);
  delay(100);
}

