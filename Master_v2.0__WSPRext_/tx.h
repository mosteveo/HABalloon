// ############### Tx Loop ######################################

void tx()
{
  digitalWrite (TXPIN, HIGH);                                           // enable PA
  
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
