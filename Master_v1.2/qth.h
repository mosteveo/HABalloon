// ############### QTH Calc ############################################

void qth()
  {
  lon = (gps.location.lng() * 100000) + 18000000;                     // GPS correction
  lat = (gps.location.lat() * 100000) +  9000000;                     // GPS correction
                     

//  char MH[6] = {'A', 'A', '0', '0', 'a', 'a'};                      // 6 place QTH print string
  char MH[4] = {'A', 'A', '0', '0'};                                  // 4 place QTH print string
      MH[0] +=  lon / 2000000;                                        // 1st letter of QTH
      MH[1] +=  lat / 1000000;                                        // 2nd letter of QTH
      MH[2] += (lon % 2000000) / 200000;                              // 3rd number of QTH
      MH[3] += (lat % 1000000) / 100000;                              // 4th number of QTH
//      MH[4] += ((lon % 200000) / 8333);                             // 5th letter of QTH
//      MH[5] += ((lat % 100000) / 4166);                             // 6th letter of QTH   
  
  String qth_txt = "";                                                // Build up Maidenhead
  int i = 0;                                                          // into a string that's easy to print
//  while (i < 6){                                                    // 6 place QTH
  while (i < 4){                                                      // 4 place QTH
  qth_txt += MH[i];
  i++; }

  Serial.print(" QTH : ");                                            // print QTH
  Serial.print(qth_txt);                                              // print QTH
  Serial.println();                                                   // blank line for formatting
  Serial.print(" Altitude : ");                                       // altitude print
  Serial.print(gps.altitude.meters());                                // altitude print
  }
