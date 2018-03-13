// Modified and adapted as a low power CW beacon using an Arduino and AD9850 board from EBay
// The Morse generating code was taken from http://brainwagon.org
//Just change the message and FREQUENCY to whatever *you* need.
//If you need a different speed from 12WPM, just change the Speed define below.
// tweaked a bit by GM1SXX 20-06-2015

#define N_MORSE  (sizeof(morsetab)/sizeof(morsetab[0]))
#define FREQUENCY2 0              //Leave this at 0
#define FREQUENCY CW_DEFAULT_FREQ
#define SPEED  (12)              // WPM rate
#define DOTLEN  (1200/SPEED) // no need to adjust, tone length varies by WPM rate
#define DASHLEN  (3*(1200/SPEED)) // no need to adjust, tone length varies by WPM rate


struct t_mtab {
  char c, pat;
} ;

struct t_mtab morsetab[] = {
  {'+', 42},
  {'-', 97},
  {'=', 49},
  {'.', 106},
  {',', 115},
  {'?', 76},
  {'/', 41},
  {'A', 6},
  {'B', 17},
  {'C', 21},
  {'D', 9},
  {'E', 2},
  {'F', 20},
  {'G', 11},
  {'H', 16},
  {'I', 4},
  {'J', 30},
  {'K', 13},
  {'L', 18},
  {'M', 7},
  {'N', 5},
  {'O', 15},
  {'P', 22},
  {'Q', 27},
  {'R', 10},
  {'S', 8},
  {'T', 3},
  {'U', 12},
  {'V', 24},
  {'W', 14},
  {'X', 25},
  {'Y', 29},
  {'Z', 19},
  {'1', 62},
  {'2', 60},
  {'3', 56},
  {'4', 48},
  {'5', 32},
  {'6', 33},
  {'7', 35},
  {'8', 39},
  {'9', 47},
  {'0', 63}
} ;


void dash()
{
  sendFrequency(FREQUENCY);
  delay(DASHLEN);
  sendFrequency(FREQUENCY2);
  delay(DOTLEN);
}

void dit()
{
  sendFrequency(FREQUENCY);
  delay(DOTLEN);
  sendFrequency(FREQUENCY2);
  delay(DOTLEN);
}


void send(char c)
{
  int i ;
  if (c == ' ') {
    delay(7 * DOTLEN) ;
    return ;
  }
  for (i = 0; i < N_MORSE; i++) {
    if (morsetab[i].c == c) {
      unsigned char p = morsetab[i].pat ;
      Serial.print(morsetab[i].c) ;
      
      while (p != 1) {
        if (p & 1)
          dash() ;
        else
          dit() ;
        p = p / 2 ;
      }
      delay(2 * DOTLEN) ;
      return ;
    }
  }
  /* if we drop off the end, then we send a space */
  Serial.print("?") ;
}


void sendCW(char *str)
{
  while (*str)
    send(*str++) ;
}





