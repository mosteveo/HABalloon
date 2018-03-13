// GPS altitude conversion to formatted foe WSPR/JT

void altitude() 
{

Serial.println("Altitude Meters: ");            // debug
Serial.println(gps.altitude.meters());            // debug


unsigned int telemAlt; 								// define variable "alt"


if (gps.altitude.meters() <= 9999)
	{
	alt = (round((gps.altitude.meters() / 1000)) * 1000); // convert altitude to nearest 1000
	}
if (gps.altitude.meters() >= 10000)
	{
	alt = (round((gps.altitude.meters() / 10000)) * 10000); // convert altitude to nearest 1000
	}



    /* Altitude range encoded into the 19 possible "dbm" ranges from 0 to 18,000 meters
     *  there are 19 possible encoding steps to convey this information leading to 1000 meter resolution.
     *  Value may be: 0, 3, 7, 10, 13, 17, 20, 23, 27, 30, 33, 37, 40, 43, 47, 50, 53, 57, 60
    */ 


    if (alt <= 0) { telemAlt = 0;}
    if (alt = 1000) { telemAlt = 3;}
    if (alt = 2000) { telemAlt = 7;}
    if (alt = 3000) { telemAlt = 10;}
    if (alt = 4000) { telemAlt = 13;}
    if (alt = 5000) { telemAlt = 17;}
    if (alt = 6000) { telemAlt = 20;}
    if (alt = 7000) { telemAlt = 23;}
    if (alt = 8000) { telemAlt = 27;}
    if (alt = 9000) { telemAlt = 30;}
    if (alt = 10000) { telemAlt = 33;}
    if (alt = 11000) { telemAlt = 37;}
    if (alt = 12000) { telemAlt = 40;}
    if (alt = 13000) { telemAlt = 43;}
    if (alt = 14000) { telemAlt = 47;}
    if (alt = 15000) { ttelemAlt = 50;}
    if (alt = 16000) { telemAlt = 53;}
    if (alt = 17000) { telemAlt = 57;}
    if (alt >= 18000) {telemAlt = 60;}

    
    
    
	Serial.print("nearest thousand meter altitude: ");
    Serial.println(alt);
    Serial.print("dbm altitude: ");
    Serial.println(telemAlt);
    
}