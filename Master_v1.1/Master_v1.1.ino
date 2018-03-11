/*
 * 
 * fix tone spacing, which may not ba accurate
 * setup timing schedule
 * add DDS frequency stability with GPS?
 * 
 * 
 * 
 */



// ############### Libraries ######################################

#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <JTEncode.h>
#include <rs_common.h>
#include <int.h>
#include <string.h>

// ############### Hardware Config ######################################

#define W_CLK 8                                             // AD9850 PIN
#define FQ_UD 9                                             // AD9850 PIN
#define DATA 10                                             // AD9850 PIN
#define RESET 11                                            // AD9850 PIN
#define pulseHigh(pin) {digitalWrite(pin, HIGH); digitalWrite(pin, LOW); }
static const int RXPin = 5, TXPin = 3;                      // GPS pins
static const uint32_t GPSBaud = 9600;                       // GPS baud
#define TXPIN 7                                             // pin for PA control: 1 = TX ON; 0 = TX OFF
int resetPin = 12;                                          // hardware reset pin


// ############### Mode Definitions ######################################

#define JT9_TONE_SPACING        1.74           // ~1.74 Hz (symshift) *
#define JT9_DELAY               576          // Delay (symboltime) *
#define JT9_SYMBOL_COUNT        85

#define JT65_TONE_SPACING       2.69           // ~2.69 Hz *
#define JT65_DELAY              372          // Delay in ms for JT65A *
#define JT65_SYMBOL_COUNT       126

#define JT4_TONE_SPACING        4.37           // ~4.37 Hz *
#define JT4_DELAY               229          // Delay value for JT4A *
#define JT4_SYMBOL_COUNT        207

#define WSPR_TONE_SPACING       1.46           // ~1.46 Hz (working) *
#define WSPR_DELAY              683          // Delay value for WSPR (working) *
#define WSPR_SYMBOL_COUNT       162

#define JT9_DEFAULT_FREQ        10140000UL
#define JT65_DEFAULT_FREQ       10140400UL
#define JT4_DEFAULT_FREQ        10140400UL
#define WSPR_DEFAULT_FREQ       10140050UL

#define DEFAULT_MODE            MODE_JT9

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
char message[] = "KD2NDO KD2NDR FN31";
char call[] = "KD2NDR";
char loc[] = "FN31";
uint8_t dbm = 1;
uint8_t tx_buffer[255];
enum mode cur_mode = DEFAULT_MODE;
uint8_t symbol_count;
uint16_t tone_delay, tone_spacing;

// ############### AD9850 Initilization ######################################

void tfr_byte (byte data)
{
  for (int i = 0; i <8; i ++, data >>= 1) {
    digitalWrite (DATA, data & 0x01);
    pulseHigh (W_CLK);
  }
}
 
void sendFrequency(double frequency) {
  int32_t freq = frequency * 4294967295/125000000;          // note 125 MHz clock on 9850
  for (int b=0; b<4; b++, freq>>=8) {
    tfr_byte (freq & 0xFF);
  }
  tfr_byte(0x000);
  pulseHigh(FQ_UD);
}

// ############### Tx Loop ######################################

void encode()
{
  digitalWrite (TXPIN, HIGH);                                           // enable PA
  // set_tx_buffer();
  // delay(50);
  
  uint8_t i;
                                                                        // Now transmit the channel symbols 
  for(i = 0; i < symbol_count; i++)
  {
      sendFrequency(freq + (tx_buffer[i] * tone_spacing));
      delay(tone_delay);
  }
  sendFrequency (0);                                                    // disable Tx after completion
  digitalWrite(resetPin, LOW);                                          // begin hardware reset
}

// ############### Tx Buffer #############################################

void set_tx_buffer()
{
  // Clear out the transmit buffer
  memset(tx_buffer, 0, 255);

  switch(cur_mode)                                                      // Set the proper frequency and timer CTC depending on mode
  {
  case MODE_JT9:
    jtencode.jt9_encode(message, tx_buffer);
    break;
  case MODE_JT65:
    jtencode.jt65_encode(message, tx_buffer);
    break;
  case MODE_JT4:
    jtencode.jt4_encode(message, tx_buffer);
    break;
  case MODE_WSPR:
    jtencode.wspr_encode(call, loc, dbm, tx_buffer);
    break;
  }
}

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

  void setmode()
  {
    switch(cur_mode)                                                   // Set the proper frequency, tone spacing, symbol count, and tone delay depending on mode 
    {
    case MODE_JT9:
      freq = JT9_DEFAULT_FREQ;
      symbol_count = JT9_SYMBOL_COUNT;                                 // From the library defines
      tone_spacing = JT9_TONE_SPACING;
      tone_delay = JT9_DELAY;
      break;
    case MODE_JT65:
      freq = JT65_DEFAULT_FREQ;
      symbol_count = JT65_SYMBOL_COUNT;                                // From the library defines
      tone_spacing = JT65_TONE_SPACING;
      tone_delay = JT65_DELAY;
      break;
    case MODE_JT4:
      freq = JT4_DEFAULT_FREQ;
      symbol_count = JT4_SYMBOL_COUNT;                                 // From the library defines
      tone_spacing = JT4_TONE_SPACING;
      tone_delay = JT4_DELAY;
      break;
    case MODE_WSPR:
      freq = WSPR_DEFAULT_FREQ;
      symbol_count = WSPR_SYMBOL_COUNT;                                // From the library defines
      tone_spacing = WSPR_TONE_SPACING;
      tone_delay = WSPR_DELAY;
      break;
     }
     set_tx_buffer();                                                   // Encode the message in the transmit buffer, This is RAM intensive and should be done separately from other subroutines
  }

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

// ############### Temp Calc ###########################################
/*
void tempcalc()
  {
    int sensorTemp = analogRead(A6);                                  // read temp from TMP36 module at pin A6
    float temp = ((sensorTemp * sysVolt) / 1024.0) * 100;             // correction for system voltage
    Serial.print("Temprature C: ");
    Serial.println(temp);
  }
*/
// ############### Volt Calc ###########################################
/*
void voltcalc()
  {
    int sensorVolt = analogRead(A4);                                  // read voltage from pin A4
    float volt = sensorVolt * (sysVolt / 1024.0);                     // calc voltage using system voltage defined above
    Serial.print("voltage: ");                                        // serial debug
    Serial.println(volt);                                             // serial debug
  }
*/
// ############### Clear Serial RX Buffer ##############################
void sflush()                                                         // to prevent double transmissions
  {
    ss.end();
     delay (200);                                                     // delay to stop, clear and start soft serial buffer
    ss.begin(GPSBaud);
  }
  
// ############### Tx Schedule #########################################

void timing()
  {
    if (gps.time.second() == 1)                                       // ensure time is 1 second for transmission, essential for packet transmssion of these modes
        {
         if ((gps.time.minute() <= 10) && ((gps.time.minute() % 2) == 0))// minute to begin transmission
            {
                Serial.println("tx schedule 1 script running");       // debug
                //tempcalc();                                         // run temprature calculation
                //voltcalc();                                         // run voltage calculation
                qth();                                                // run qth calculation
                delay(50);
                memset(tx_buffer, 0, 255);
                cur_mode = MODE_JT4;                                  // define mode for this time slot (MODE_JT9, MODE_JT9, MODE_JT65, MODE_WSPR)
                setmode();                                            // set mode paramaters based on cur_mode chosen above and mode defines in top of script.
                encode();                                             // Tx
                sflush();                                             // flush RX soft serial buffer to prevent multiple Tx
                delay(150);
             }
         if ((gps.time.minute() >= 10) && (gps.time.minute() % 2))    // minute to begin transmission
            {
                Serial.println("tx schedule 2 script running");       // debug
                //tempcalc();                                         // run temprature calculation
                //voltcalc();                                         // run voltage calculation
                qth();                                                // run qth calculation
                delay (50);
                memset(tx_buffer, 0, 255);
                cur_mode = MODE_JT4;                                  // define mode for this time slot (MODE_JT9, MODE_JT9, MODE_JT65, MODE_WSPR)
                setmode();                                            // set mode paramaters based on cur_mode chosen above and mode defines in top of script.
                encode();                                             // Tx
                sflush();                                             // flush RX soft serial buffer to prevent multiple Tx
                delay(150);
             }        
        }
  }

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
