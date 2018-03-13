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