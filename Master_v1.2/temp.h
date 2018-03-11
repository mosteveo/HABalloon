// ############### Temp Calc ###########################################

void tempcalc()
  {
    int sensorTemp = analogRead(A6);                                  // read temp from TMP36 module at pin A6
    float temp = ((sensorTemp * sysVolt) / 1024.0) * 100;             // correction for system voltage
    Serial.print("Temprature C: ");
    Serial.println(temp);
  }
