/***************************************************************************************************************************************************
 * HABalloon v2.0
 * Fixed: GPS based QTH locator now works and will update QTH automatically into WSPR and JT (if enabled) messages 
 * Added: CW mode
 * 
 ***************************************************************************************************************************************************/



// ############### Libraries ######################################

#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <JTEncode.h>
#include <rs_common.h>
#include <int.h>
#include <string.h>
#include "settings.h"


#include"hw.h"

#include "modedef.h"


// ############### Enumerations ######################################

enum mode {MODE_JT9, MODE_JT65, MODE_JT4, MODE_WSPR};

// ############### Class instantiation ######################################

TinyGPSPlus gps;                                            // The TinyGPS++ object
JTEncode jtencode;
long lat, lon;                                              // The TinyGPS++ object

SoftwareSerial ss(RXPin, TXPin);                            // The serial connection to the GPS device


// ############### Global Variables ######################################


#define sysVolt 5                                           // system voltage (5 volts)
unsigned long freq;
char message[] = "KD2NDO KD2NDR FN31";                      // JT mode message
char call[] = "KD2NDR";                                     // WSPR variable
uint8_t dbm = 1;
uint8_t tx_buffer[255];
enum mode cur_mode = DEFAULT_MODE;
uint8_t symbol_count;
uint16_t tone_delay, tone_spacing;

#include "SSflush.h"
#include "AD9850.h"  
#include "tx.h"
#include "encodeJT.h"
#include "encodeWSPR.h"
#include "QRSS_CW.h"

#include "volt.h"
#include "temp.h"


// ############### Setup Loop ###########################################

void setup() 
  {
  digitalWrite(resetPin, HIGH);                                         // write reset pin high so arduino can boot
  pinMode(resetPin, OUTPUT);                                            // enable reset pin as output
  // Initialize the AD9850
  pinMode (FQ_UD, OUTPUT);                                              // AD9850 PIN
  pinMode (W_CLK, OUTPUT);                                              // AD9850 PIN
  pinMode (DATA, OUTPUT);                                               // AD9850 PIN
  pinMode (RESET, OUTPUT);                                              // AD9850 PIN

  pulseHigh (RESET);                                                    // AD9850 PIN
  pulseHigh (W_CLK);                                                    // AD9850 PIN
  pulseHigh (FQ_UD);                                                    // AD9850 PIN

  pinMode (TXPIN, OUTPUT); // optional amp switch
  digitalWrite (TXPIN, LOW); // optional amp switch

  Serial.begin(9600);                                                   // Hardware baud speed
  ss.begin(GPSBaud);                                                    // GPS serial begin
  }



#include "schedule.h"



// ############### Loop ################################################

void loop() 
  {
    while (ss.available() > 0) {
       if (gps.encode(ss.read()))
       { 
        if (gps.location.isValid())                                   // no point running is there is no GPS loction and timing
          {
             Serial.println("GPS is valid");                          // print if NMEA GPS sentance found
             Serial.print("GPS time: ");
             Serial.print(gps.time.minute());
             Serial.print(" : ");
             Serial.print(gps.time.second());
             Serial.println();
             timing();                                                // run through timing schedule
          }
       }
    }
  }
