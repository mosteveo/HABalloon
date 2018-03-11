// ############### Volt Calc ###########################################
void voltcalc()
  {
    int sensorVolt = analogRead(A4);                                  // read voltage from pin A4
    float volt = sensorVolt * (sysVolt / 1024.0);                     // calc voltage using system voltage defined above
    Serial.print("voltage: ");                                        // serial debug
    Serial.println(volt);                                             // serial debug
  }
