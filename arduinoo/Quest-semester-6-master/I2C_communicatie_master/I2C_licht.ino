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
    Wire.write(t); // Send the int input as char array
  }else
  {
    Wire.write("0");    //write '0' if no input was given.
  }
  
  Wire.endTransmission();    // stop transmitting

  //DEBUG code
  Serial.print("I2C: ");
  Serial.print(c);
  Serial.println(ints);

  

  //Todo set light variables. and save.
  switch (c)
  {
    case 'a':   //Strip on/off
      Serial.print("led strip status: ");
      Serial.println(ints);
      users[currentUser].lit_status = (int)ints;
      break;
    case 'b':   //Strip modus
      Serial.print("led strip modus: ");
      Serial.println(ints);
      users[currentUser].lit_modus = (int)ints;
      break;
    case 'm':   //Eye on
      Serial.println("eye on.");
      users[currentUser].eye_status = 1;
      break;
    case 'n':   //Eye off
      Serial.print("eye off.");
      users[currentUser].eye_status = 0;
      break;
    case 'o':
      Serial.print("eye intensity: ");
      Serial.println(ints);
      users[currentUser].eye_intensity= ints;
      break;
    case 'p':   //eye intensity
      Serial.print("eye state: ");
      Serial.println(ints);
      users[currentUser].eye_status = (ints);
      break;  
    case 'q':   //eye duration
      Serial.print("eye on duration: ");
      Serial.println(ints*1000);
      users[currentUser].eye_on_duration = 1000 * (int)ints;
      break;
    case 'r':   //eye off duration
      Serial.print("eye off duration: ");
      Serial.println(ints*1000);
      users[currentUser].eye_off_duration = 1000 * (int)ints;
      break;      
  }
  delay(30);
  //Save user data
  EEPROM.put(0,users[0]);
  EEPROM.put(75,users[1]);
  EEPROM.put(150,users[2]);
  EEPROM.put(225,users[3]);
  //EEPROM.put(300,users[4]);
  Serial.println("user data saved.");
  delay(100);
}

