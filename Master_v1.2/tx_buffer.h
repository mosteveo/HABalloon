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
