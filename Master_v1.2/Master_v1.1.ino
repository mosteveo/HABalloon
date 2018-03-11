/*
 * 
 * setup timing schedule
 * add DDS frequency stability with GPS?
 * 
 */



// ############### Libraries and Includes ######################################

#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <JTEncode.h>
#include <rs_common.h>
#include <int.h>
#include <string.h>
#include "settings.h"

#define pulseHigh(pin) {digitalWrite(pin, HIGH); digitalWrite(pin, LOW); }

// ############### Enumerations ######################################

enum mode {MODE_JT9, MODE_JT65, MODE_JT4, MODE_WSPR};

// ############### Class instantiation ######################################

TinyGPSPlus gps;                                            // The TinyGPS++ object
JTEncode jtencode;
long lat, lon;                                              // The TinyGPS++ object

SoftwareSerial ss(RXPin, TXPin);                            // The serial connection to the GPS device

// ############### Global Variables ######################################

unsigned long freq;
uint8_t tx_buffer[255];
enum mode cur_mode = DEFAULT_MODE;
uint8_t symbol_count;
uint16_t tone_delay, tone_spacing;

#include "temp.h"
#include "volt.h"
#include "qth.h"
#include "AD9850.h"
#include "tx_encode.h"
#include "tx_buffer.h"


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

  pinMode (TXPIN, OUTPUT);                                              // optional amp switch
  digitalWrite (TXPIN, LOW);                                            // optional amp switch

  Serial.begin(9600);                                                   // Hardware baud speed
  ss.begin(GPSBaud);                                                    // GPS serial begin
  }

#include "set_mode.h"

#include "clear_serial.h"

#include "timing.h"
  

  
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
