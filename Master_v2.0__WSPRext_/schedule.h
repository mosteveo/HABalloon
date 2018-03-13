// ############### Tx Schedule #########################################

void timing()
  {
    if (gps.time.second() == 1)                                       // ensure time is 1 second for transmission, essential for packet transmssion of these modes
        {
         if ((gps.time.minute() >= 0) && (gps.time.minute() <= 2))  // minute to begin transmission
            {
                Serial.println("CW Message");    // debug
                //tempcalc();                                         // run temprature calculation
                //voltcalc();                                         // run voltage calculation
                delay(50);
                // memset(tx_buffer, 0, 255);                        // clear Tx buffer memory
                sendCW("KD2NDR KD2NDR TEST TEST");                              // must be caps start Tx, message in quotes
                sflush();                                             // flush RX soft serial buffer to prevent multiple Tx
                delay(150);
             }
         if ((gps.time.minute() >= 2) && (gps.time.minute() <= 6) && (gps.time.minute() == 2))  // minute to begin transmission
            {
                Serial.println("WSPR Message 1 - CALL 4LOC TELEM");    // debug
                //tempcalc();                                         // run temprature calculation
                //voltcalc();                                         // run voltage calculation
                delay(50);
                memset(tx_buffer, 0, 255);                        // clear Tx buffer memory
                encodeWSPR1();                                    // WSPR message format 1
                tx();                                             // start Tx
                sflush();                                             // flush RX soft serial buffer to prevent multiple Tx
                delay(150);
             }
         if ((gps.time.minute() >= 2) && (gps.time.minute() <= 6) && (gps.time.minute() == 4))    // minute to begin transmission
            {
                Serial.println("WSPR Message 2 - 6LOC TELEM");       // debug
                //tempcalc();                                         // run temprature calculation
                //voltcalc();                                         // run voltage calculation
                delay (50);
                memset(tx_buffer, 0, 255);                         // clear Tx buffer memory
                encodeWSPR2();                                    // WSPR message format 2
                tx();                                             // start Tx
                sflush();                                             // flush RX soft serial buffer to prevent multiple Tx
                delay(150);
             }   
             if ((gps.time.minute() >= 6) && (gps.time.minute() <= 59) && (gps.time.minute() %2) == 0)    // minute to begin transmission
            {
                Serial.println("JT4 Mode Transmission");       // debug
                //tempcalc();                                         // run temprature calculation
                //voltcalc();                                         // run voltage calculation
                delay (50);
                memset(tx_buffer, 0, 255);                           // clear Tx buffer memory
                encodeJT4();
                tx();                                             // start Tx
                sflush();                                             // flush RX soft serial buffer to prevent multiple Tx
                delay(150);
             }             
        }  
  }
