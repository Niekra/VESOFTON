void stand(byte stand){
  Wire.beginTransmission(8); // transmit to device #8
  Wire.write("S");        // sends one bytes
  Wire.write(stand); // sends one byte

  Wire.endTransmission();    // stop transmitting
  Serial.print("transmitted");
  return;
}

void intensiteit(byte intensiteit){
  Wire.beginTransmission(8); // transmit to device #8
  Wire.write("I");        // sends one bytes
  Wire.write(intensiteit); // sends one byte

  Wire.endTransmission();    // stop transmitting
}
