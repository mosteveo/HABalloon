// ############### Temp Calc ###########################################

void tempcalc()
  {
    int telemTemp;
    int sensorTemp = analogRead(A6);                                  // read temp from TMP36 module at pin A6
    int temp = ((sensorTemp * sysVolt) / 1024) * 100;             // correction for system voltage

    /* temperature is in nominal range -40°C .. +15 °C
     *  there are 19 possible encoding steps to convey this information leading to 4°C resolution.
     *  Value may be: 0, 3, 7, 10, 13, 17, 20, 23, 27, 30, 33, 37, 40, 43, 47, 50, 53, 57, 60
    */ 
    /*
    if (temp <= -44) { telemTemp = 0;}
    if (temp = -40) { telemTemp = 3;}
    if (temp = -36) { telemTemp = 7;}
    if (temp = -32) { telemTemp = 10;}
    if (temp = -28) { telemTemp = 13;}
    if (temp = -24) { telemTemp = 17;}
    if (temp = -20) { telemTemp = 20;}
    if (temp = -16) { telemTemp = 23;}
    if (temp = -12) { telemTemp = 27;}
    if (temp = -8) { telemTemp = 30;}
    if (temp = -4) { telemTemp = 33;}
    if (temp = 4) { telemTemp = 37;}
    if (temp = 8) { telemTemp = 40;}
    if (temp = 12) { telemTemp = 43;}
    if (temp = 16) { telemTemp = 47;}
    if (temp = 20) { telemTemp = 50;}
    if (temp = 24) { telemTemp = 53;}
    if (temp = 28) { telemTemp = 57;}
    if (temp >= 32) {telemTemp = 60;}

    
    Serial.print("dbm temp: ");
    Serial.println(telemTemp);
*/
    
    Serial.print("Temprature C: ");
    Serial.println(temp);

  }
