// ############### Encode WSPR Messages type 1 or 2 #############################################

void encodeWSPR1()
{
  char qth[5];                                                         // declare qth variable

      freq = WSPR_DEFAULT_FREQ;                                         // setting mode variables
      symbol_count = WSPR_SYMBOL_COUNT;                                // setting mode variables
      tone_spacing = WSPR_TONE_SPACING;                                 // setting mode variables
      tone_delay = WSPR_DELAY;                                          // setting mode variables
  
  
      lon = (gps.location.lng() * 100000) + 18000000;                     // GPS correction
      lat = (gps.location.lat() * 100000) +  9000000;                     // GPS correction
                     

      char MH[4] = {'A', 'A', '0', '0'};                                  // 4 place QTH print string
          MH[0] +=  lon / 2000000;                                        // 1st letter of QTH
          MH[1] +=  lat / 1000000;                                        // 2nd letter of QTH
          MH[2] += (lon % 2000000) / 200000;                              // 3rd number of QTH
          MH[3] += (lat % 1000000) / 100000;                              // 4th number of QTH   
  
        String qth_txt = "";                                                // Build up Maidenhead
        int i = 0;                                                          // into a string that's easy to print
          while (i < 4){                                                      // 4 place QTH
            qth_txt += MH[i];
            i++; }
        qth_txt.toCharArray(qth, 5);                                        // convert string to array for use in jtencode

  Serial.println(); 
  Serial.print("QTH4 : ");                                            // print QTH
  Serial.println(qth_txt);                                              // print QTH
  Serial.println();
  Serial.print("Altitude : ");                                       // altitude print
  Serial.print(gps.altitude.meters());                                // altitude print
  
  
  memset(tx_buffer, 0, 255);								// Clear out the transmit buffer

  jtencode.wspr_encode(call, qth, dbm, tx_buffer); 		// message contents (call, 4 char QTH, alt)
  
}


void encodeWSPR2()
{
  char qth[3];                                                         // declare qth variable

      freq = WSPR_DEFAULT_FREQ;                                         // setting mode variables
      symbol_count = WSPR_SYMBOL_COUNT;                                // setting mode variables
      tone_spacing = WSPR_TONE_SPACING;                                 // setting mode variables
      tone_delay = WSPR_DELAY;                                          // setting mode variables

  
      lon = (gps.location.lng() * 100000) + 18000000;                     // GPS correction
      lat = (gps.location.lat() * 100000) +  9000000;                     // GPS correction
                     

     char MH[2] = {'A', 'A'};                                            // last two characters of QTH
          MH[0] += ((lon % 200000) / 8333);                             // 5th letter of QTH
          MH[1] += ((lat % 100000) / 4166);                             // 6th letter of QTH   
  
      String qth_txt = "";                                                // Build up Maidenhead
      int i = 0;                                                          // into a string that's easy to print
        while (i < 2){                                                    // 6 place QTH
          qth_txt += MH[i];
          i++; }
      qth_txt.toCharArray(qth, 3);                                        // convert string to array for use in jtencode

  Serial.println(); 
  Serial.print("last 2 characters of QTH : ");                                            // print QTH
  Serial.println(qth_txt);                                              // print QTH
  Serial.println();
  Serial.print("Altitude : ");                                       // altitude print
  Serial.print(gps.altitude.meters());                                // altitude print
  
  
  memset(tx_buffer, 0, 255);                // Clear out the transmit buffer

  jtencode.wspr_encode(call, qth, dbm, tx_buffer);    // message contents (call, 2digit loc + batt volts, temp)

}

