// ############### Tx Schedule #########################################

void timing()
  {
    if (gps.time.second() == 1)                                       // ensure time is 1 second for transmission, essential for packet transmssion of these modes
        {
         if ((gps.time.minute() <= 10) && ((gps.time.minute() % 2) == 0))// minute to begin transmission
            {
                Serial.println("tx schedule 1 script running");       // debug
                //tempcalc();                                         // run temprature calculation
                //voltcalc();                                         // run voltage calculation
                qth();                                                // run qth calculation
                delay(50);
                memset(tx_buffer, 0, 255);
                cur_mode = MODE_JT4;                                  // define mode for this time slot (MODE_JT9, MODE_JT9, MODE_JT65, MODE_WSPR)
                setmode();                                            // set mode paramaters based on cur_mode chosen above and mode defines in top of script.
                encode();                                             // Tx
                sflush();                                             // flush RX soft serial buffer to prevent multiple Tx
                delay(150);
             }
         if ((gps.time.minute() >= 10) && (gps.time.minute() % 2))    // minute to begin transmission
            {
                Serial.println("tx schedule 2 script running");       // debug
                //tempcalc();                                         // run temprature calculation
                //voltcalc();                                         // run voltage calculation
                qth();                                                // run qth calculation
                delay (50);
                memset(tx_buffer, 0, 255);
                cur_mode = MODE_JT4;                                  // define mode for this time slot (MODE_JT9, MODE_JT9, MODE_JT65, MODE_WSPR)
                setmode();                                            // set mode paramaters based on cur_mode chosen above and mode defines in top of script.
                encode();                                             // Tx
                sflush();                                             // flush RX soft serial buffer to prevent multiple Tx
                delay(150);
             }        
        }
  }
