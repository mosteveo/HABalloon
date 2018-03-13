// ############### JT mode encoding #############################################

void encodeJT4()
{
char qth[5];                                                         // declare qth variable

      freq = JT4_DEFAULT_FREQ;
      symbol_count = JT4_SYMBOL_COUNT;                                 // From the library defines
      tone_spacing = JT4_TONE_SPACING;
      tone_delay = JT4_DELAY;
      
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

	jtencode.jt4_encode(message, tx_buffer);
}


void encodeJT9()
{
char qth[5];                                                         // declare qth variable

      freq = JT9_DEFAULT_FREQ;
      symbol_count = JT9_SYMBOL_COUNT;                                 // From the library defines
      tone_spacing = JT9_TONE_SPACING;
      tone_delay = JT9_DELAY;

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

	jtencode.jt9_encode(message, tx_buffer);

}


void encodeJT65()
{
char qth[5];                                                         // declare qth variable

      freq = JT65_DEFAULT_FREQ;
      symbol_count = JT65_SYMBOL_COUNT;                                // From the library defines
      tone_spacing = JT65_TONE_SPACING;
      tone_delay = JT65_DELAY;

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
  
  jtencode.jt65_encode(message, tx_buffer);
  
}
