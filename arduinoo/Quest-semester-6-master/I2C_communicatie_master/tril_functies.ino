void vib_on(){
  analogWrite(TRIL_MOTOR1, users[currentUser].vib_intensity);
  analogWrite(TRIL_MOTOR2, users[currentUser].vib_intensity);
  users[currentUser].vib_status = 1;
  timer0_counter = 0;
  return;
}

void vib_off(){
  analogWrite(TRIL_MOTOR1, LOW);
  analogWrite(TRIL_MOTOR2, LOW);
  users[currentUser].vib_status = 0;
  timer0_counter = 0;
  return;
}

void vib_toggle(){
  if(users[currentUser].vib_status == 1){
    vib_on();
    users[currentUser].vib_status = 0;
  }else
  {
    vib_off();
    users[currentUser].vib_status = 1;
  }
}

void set_vib_intensity(int ints){
  users[currentUser].vib_intensity = (255 * ints/100);

    if(users[currentUser].vib_status == 1){
      vib_on();
    }
   
}

void vib_manager(char c, int ints){
  switch(c) {
    case 'o':
      vib_on();
      users[currentUser].vib_onoff = 1;
      users[currentUser].vib_modus = 1;
      break;
    case 'f':
      Serial.println("x");
      vib_off();
      users[currentUser].vib_onoff = 0;
      users[currentUser].vib_modus = 0;
      break;
    case 'i':
      set_vib_intensity(ints);
      break;
    case 'm':
      users[currentUser].vib_modus = ints;
      break;  
    case 'v':
      users[currentUser].vib_on_duration = 1000 * ints;
      break;
    case 'z':
      users[currentUser].vib_off_duration = 1000 * ints;
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

void check_vib()
{
  if(users[currentUser].vib_modus != 0)
  {
    if(users[currentUser].vib_status == 0)
    {
      if(timer0_counter > users[currentUser].vib_off_duration)
      {
        //Serial.print("x");
        vib_on();
      }
    }else if(users[currentUser].vib_status == 1)
    {
      if(timer0_counter > users[currentUser].vib_on_duration)
      {
        //Serial.print("y");
        vib_off();
      }
    }
  }
}


