// ############### Clear Serial RX Buffer ##############################
void sflush()                                                         // to prevent double transmissions
  {
    ss.end();
     delay (200);                                                     // delay to stop, clear and start soft serial buffer
    ss.begin(GPSBaud);
  }
