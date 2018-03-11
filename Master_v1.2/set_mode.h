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