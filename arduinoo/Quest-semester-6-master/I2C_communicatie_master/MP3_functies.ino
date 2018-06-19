
/********************************************************************************/
/*Function sendMP3Command: seek for a 'c' command and send it to MP3  */
/*Parameter: c. Code for the MP3 Command, 'h' for help.                                                                                                         */
/*Return:  void                                                                */

//TODO: additional/change music functions
void sendMP3Command(char c, int ints) {
  switch (c) {

    case 'p':   //play
      Serial.println("Play ");
      sendCommand(CMD_PLAY, 0);
      sendCommand(CMD_PLAYING_N, 0x0000); // ask for the number of file is playing
      ampon();
      break;

    case 'P':   //pause
      Serial.println("Pause");
      sendCommand(CMD_PAUSE, 0);
      ampoff();
      break;

    case '>':   //next
      Serial.println("Next");
      sendCommand(CMD_NEXT_SONG, 0);
      sendCommand(CMD_PLAYING_N, 0x0000); // ask for the number of file is playing
      break;

    case '<':   //previous
      Serial.println("Previous");
      sendCommand(CMD_PREV_SONG, 0);
      sendCommand(CMD_PLAYING_N, 0x0000); // ask for the number of file is playing
      break;

    case 'v': //TODO save volume
      Serial.println("set volume");
      delay(20);
      Send_buf[0] = 0x7e;   //
      Send_buf[1] = 0xff;   //
      Send_buf[2] = 0x06;   // Len
      Send_buf[3] = CMD_SET_VOLUME;//
      Send_buf[4] = 0x00;   // 0x00 NO, 0x01 feedback
      Send_buf[5] = 0x00;  //datah
      Send_buf[6] = (int8_t)(ints);       //datal
      Send_buf[7] = 0xef;   //
      Serial.print("Sending: ");
      for (uint8_t i = 0; i < 8; i++)
      {
        mp3.write(Send_buf[i]) ;
        Serial.print(sbyte2hex(Send_buf[i]));
      }
      Serial.println();
      users[currentUser].volume = ints;
      break;

    case 'S':   //Sleep
      Serial.println("Sleep");
      sendCommand(CMD_SLEEP_MODE, 0x00);
      users[currentUser].s_status = 0;
      ampoff();
      break;

    case 'W':   //Wake
      Serial.println("Wake up");
      sendCommand(CMD_WAKE_UP, 0x00);
      users[currentUser].s_status = 1;
      //ampon();
      break;

    case 'r':   //Reset
      Serial.println("Reset");
      sendCommand(CMD_RESET, 0x00);
      break;

   case 's'://TODO save shuffle?
      Serial.println("shuffle");
      sendCommand(CMD_SHUFFLE_PLAY, 0x00);
      users[currentUser].s_modus = 2;
      break;

   case 'C'://TODO save single cycle?
      Serial.println("single cycle play");
      sendCommand(CMD_SET_SNGL_CYCL, 0x00);
      users[currentUser].s_modus = 3;
      break;

   case 'F'://TODO save folder
      Serial.println("folder play");
      delay(20);
      Send_buf[0] = 0x7e;   //
      Send_buf[1] = 0xff;   //
      Send_buf[2] = 0x06;   // Len
      Send_buf[3] = CMD_FOLDER_CYCLE;//
      Send_buf[4] = 0x00;   // 0x00 NO, 0x01 feedback
      Send_buf[5] = 0x00;  //datah
      Send_buf[6] = (int8_t)(ints);       //datal
      Send_buf[7] = 0xef;   //
      Serial.print("Sending: ");
      for (uint8_t i = 0; i < 8; i++)
      {
        mp3.write(Send_buf[i]) ;
        Serial.print(sbyte2hex(Send_buf[i]));
      }
      Serial.println();

      delay(20);
      sendCommand(CMD_PLAY, 0);
      users[currentUser].play_folder = ints;
      break;

    case 'k': //TODO save index
      Serial.println("play song with index.");
      delay(20);
      Send_buf[0] = 0x7e;   //
      Send_buf[1] = 0xff;   //
      Send_buf[2] = 0x06;   // Len
      Send_buf[3] = CMD_PLAY_W_INDEX;//
      Send_buf[4] = 0x00;   // 0x00 NO, 0x01 feedback
      Send_buf[5] = 0x00;  //datah
      Send_buf[6] = (int8_t)(ints);       //datal
      Send_buf[7] = 0xef;   //
      Serial.print("Sending: ");
      for (uint8_t i = 0; i < 8; i++)
      {
        mp3.write(Send_buf[i]) ;
        Serial.print(sbyte2hex(Send_buf[i]));
      }
      Serial.println();
      users[currentUser].start_song = ints;
      break;

   case 'R':    //Folder cycle
      Serial.println("folder cycle");
      delay(20);
      Send_buf[0] = 0x7e;   //
      Send_buf[1] = 0xff;   //
      Send_buf[2] = 0x06;   // Len
      Send_buf[3] = CMD_FOLDER_CYCLE;//
      Send_buf[4] = 0x00;   // 0x00 NO, 0x01 feedback
      Send_buf[5] = 0x00;  //datah
      Send_buf[6] = (int8_t)(users[currentUser].play_folder);       //datal
      Send_buf[7] = 0xef;   //
      Serial.print("Sending: ");
      for (uint8_t i = 0; i < 8; i++)
      {
        mp3.write(Send_buf[i]) ;
        Serial.print(sbyte2hex(Send_buf[i]));
      }
      Serial.println();
      users[currentUser].s_modus = 1;
      break;
  }
  delay(30);
  //EEPROM_writeAnything(0, users);
  EEPROM.put(0,users[0]);
  EEPROM.put(75,users[1]);
  EEPROM.put(150,users[2]);
  EEPROM.put(225,users[3]);
  //EEPROM.put(300,users[4]);
  Serial.println("user data saved");
  delay(100);
  //TODO save settings
}



/********************************************************************************/
/*Function decodeMP3Answer: Decode MP3 answer.                                  */
/*Parameter:-void                                                               */
/*Return: The                                                  */

String decodeMP3Answer() {
  String decodedMP3Answer = "";

  decodedMP3Answer += sanswer();

  switch (ansbuf[3]) {
    case 0x3A:
      decodedMP3Answer += " -> Memory card inserted.";
      break;

    case 0x3D:
      decodedMP3Answer += " -> Completed play num " + String(ansbuf[6], DEC);
      break;

    case 0x40:
      decodedMP3Answer += " -> Error";
      break;

    case 0x41:
      decodedMP3Answer += " -> Data recived correctly. ";
      break;

    case 0x42:
      decodedMP3Answer += " -> Status playing: " + String(ansbuf[6], DEC);
      break;

    case 0x48:
      decodedMP3Answer += " -> File count: " + String(ansbuf[6], DEC);
      break;

    case 0x4C:
      decodedMP3Answer += " -> Playing: " + String(ansbuf[6], DEC);
      break;

    case 0x4E:
      decodedMP3Answer += " -> Folder file count: " + String(ansbuf[6], DEC);
      break;

    case 0x4F:
      decodedMP3Answer += " -> Folder count: " + String(ansbuf[6], DEC);
      break;
  }

  return decodedMP3Answer;
}






/********************************************************************************/
/*Function: Send command to the MP3                                         */
/*Parameter:-int8_t command                                                     */
/*Parameter:-int16_ dat  parameter for the command                              */

void sendCommand(int8_t command, int16_t dat)
{
  delay(20);
  Send_buf[0] = 0x7e;   //
  Send_buf[1] = 0xff;   //
  Send_buf[2] = 0x06;   // Len
  Send_buf[3] = command;//
  Send_buf[4] = 0x00;   // 0x00 NO, 0x01 feedback
  Send_buf[5] = (int8_t)(dat >> 8);  //datah
  Send_buf[6] = (int8_t)(dat);       //datal
  Send_buf[7] = 0xef;   //
  Serial.print("Sending: ");
  for (uint8_t i = 0; i < 8; i++)
  {
    mp3.write(Send_buf[i]) ;
    Serial.print(sbyte2hex(Send_buf[i]));
  }
  Serial.println();
}



/********************************************************************************/
/*Function: sbyte2hex. Returns a byte data in HEX format.                 */
/*Parameter:- uint8_t b. Byte to convert to HEX.                                */
/*Return: String                                                                */


String sbyte2hex(uint8_t b)
{
  String shex;

  shex = "0X";

  if (b < 16) shex += "0";
  shex += String(b, HEX);
  shex += " ";
  return shex;
}




/********************************************************************************/
/*Function: sanswer. Returns a String answer from mp3 UART module.          */
/*Parameter:- uint8_t b. void.                                                  */
/*Return: String. If the answer is well formated answer.                        */

String sanswer(void)
{
  uint8_t i = 0;
  String mp3answer = "";

  // Get only 10 Bytes
  while (mp3.available() && (i < 10))
  {
    uint8_t b = mp3.read();
    ansbuf[i] = b;
    i++;

    mp3answer += sbyte2hex(b);
  }

  // if the answer format is correct.
  if ((ansbuf[0] == 0x7E) && (ansbuf[9] == 0xEF))
  {
    return mp3answer;
  }

  return "???: " + mp3answer;
}

void ampoff(){
  digitalWrite(AMPPIN, LOW);
}

void ampon(){
  digitalWrite(AMPPIN, HIGH);
}


