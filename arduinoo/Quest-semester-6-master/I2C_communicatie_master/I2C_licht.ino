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
  }
  
  Wire.endTransmission();    // stop transmitting

  Serial.println(c);
  Serial.println(t);
}

