
// ############### Mode Definitions ######################################

#define JT9_TONE_SPACING        1.74           // ~1.74 Hz (symshift) *
#define JT9_DELAY               576          // Delay (symboltime) *
#define JT9_SYMBOL_COUNT        85           // Max symbols

#define JT65_TONE_SPACING       2.69           // ~2.69 Hz *
#define JT65_DELAY              372          // Delay in ms for JT65A *
#define JT65_SYMBOL_COUNT       126           // Max symbols

#define JT4_TONE_SPACING        4.37           // ~4.37 Hz *
#define JT4_DELAY               229          // Delay value for JT4A *
#define JT4_SYMBOL_COUNT        207           // Max symbols

#define WSPR_TONE_SPACING       1.46           // ~1.46 Hz (working) *
#define WSPR_DELAY              683          // Delay value for WSPR (working) *
#define WSPR_SYMBOL_COUNT       162           // Max symbols

#define QRSS_TONE_SPACING       1.46           // ~1.46 Hz (working) *
#define QRSS_DELAY              683          // Delay value for WSPR (working) *
#define QRSS_SYMBOL_COUNT       162           // Max symbols

#define CW_TONE_SPACING       1.46           // ~1.46 Hz (working) *
#define CW_DELAY              683          // Delay value for WSPR (working) *
#define CW_SYMBOL_COUNT       162           // Max symbols

#define JT9_DEFAULT_FREQ        10140000UL
#define JT65_DEFAULT_FREQ       10140400UL
#define JT4_DEFAULT_FREQ        10140400UL
#define WSPR_DEFAULT_FREQ       10140050UL
#define QRSS_DEFAULT_FREQ       10140400UL
#define CW_DEFAULT_FREQ         10140400UL

#define DEFAULT_MODE            MODE_WSPR
