void light_manager(char c, int b)
{
  switch (c)
  {
    case 'a':
        strip_on = (int)b;
      break;
    case 'b':
        strip_modus = (int)b;
      break;
    case 'm':
      eye_on();
      break;
    case 'n':
      eye_off();
      break;
    case 'o':
      set_eye_intensity((int)b);
      break;
    case 'p':
      eye_modus = (int)b;
      break;  
    case 'q':
      eye_on_duration = 1000 * (int)b;
      break;
    case 'r':
      eye_off_duration = 1000 * (int)b;
      break;      
  }
}
