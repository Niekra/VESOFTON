//Set vibration on.
void vib_on(){
  analogWrite(TRIL_MOTOR1, users[currentUser].vib_intensity);
  analogWrite(TRIL_MOTOR2, users[currentUser].vib_intensity);
  users[currentUser].vib_status = 1;
  timer0_counter = 0;
  return;
}

//Set vibration off.
void vib_off(){
  analogWrite(TRIL_MOTOR1, LOW);
  analogWrite(TRIL_MOTOR2, LOW);
  users[currentUser].vib_status = 0;
  timer0_counter = 0;
  return;
}

//Toggle vibration
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

//Set vibration intesity
void set_vib_intensity(int ints){
  users[currentUser].vib_intensity = (255 * ints/100);

    if(users[currentUser].vib_status == 1){
      vib_on();
    }
   
}

//Manage vibration type inputs
void vib_manager(char c, int ints){
  switch(c) {
    case 'o': //vib on
      Serial.println("vib on.");
      vib_on();
      users[currentUser].vib_onoff = 1;
      users[currentUser].vib_modus = 1;
      break;
    case 'f': //vib off
      Serial.println("vib off");
      vib_off();
      users[currentUser].vib_onoff = 0;
      users[currentUser].vib_modus = 0;
      break;
    case 'i': //vib intensity
      Serial.print("vib intensity: ");
      Serial.println(ints);
      set_vib_intensity(ints);
      break;
    case 'm':   //vib modus
      Serial.print("vib modus: ");
      Serial.println(ints);
      users[currentUser].vib_modus = ints;
      break;  
    case 'v':   //vib on duration ms
      Serial.print("vib on duration: ");
      Serial.println(ints);
      users[currentUser].vib_on_duration = 1000 * ints;
      break;
    case 'z':   //vib off duration ms
      Serial.print("vib off duration: ");
      Serial.println(ints);
      users[currentUser].vib_off_duration = 1000 * ints;
      break;          
  }
  delay(30);
  //save user data;
  EEPROM.put(0,users[0]);
  EEPROM.put(75,users[1]);
  EEPROM.put(150,users[2]);
  EEPROM.put(225,users[3]);
  //EEPROM.put(300,users[4]);
  Serial.println("userdata saved");
  delay(100);
}


//Check if the Vib needs to be switched on or off
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


