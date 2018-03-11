// ############### Hardware Config ######################################
#define W_CLK 8                                             // AD9850 PIN
#define FQ_UD 9                                             // AD9850 PIN
#define DATA 10                                             // AD9850 PIN
#define RESET 11                                            // AD9850 PIN
#define TXPIN 7                                             // pin for PA control: 1 = TX ON; 0 = TX OFF
static const int RXPin = 5, TXPin = 3;                      // GPS pins
static const uint32_t GPSBaud = 9600;                       // GPS baud
int resetPin = 12;                                          // hardware reset pin
#define sysVolt 5                                           // system voltage (5 volts)

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

// ############### User Variables ######################################
char message[] = "KD2NDO KD2NDR FN31";
char call[] = "KD2NDR";
char loc[] = "FN31";
uint8_t dbm = 1;


