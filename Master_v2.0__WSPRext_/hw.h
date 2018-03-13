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