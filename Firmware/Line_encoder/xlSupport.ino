void xlReadBytes(byte addr, byte *buffer, byte len)
{
  Wire.beginTransmission(XL_ADDR);
  Wire.write(addr);
  Wire.endTransmission(false);
  Wire.requestFrom((uint8_t) XL_ADDR, (uint8_t) len);
  for (byte i = 0; i<len; i++)
  {
    while (Wire.available() == 0);
    buffer[i] = Wire.read();
  }
}

void xlWriteBytes(byte addr, byte *buffer, byte len)
{
  Wire.beginTransmission(XL_ADDR);
  Wire.write(addr);
  for (byte i = 0; i < len; i++)
  {
    Wire.write(buffer[i]);
  }
  Wire.endTransmission();
}

void xlConfig()
{
  // First off, we'll set up our mode.
  
  // We're going to set up the accelerometer to react to taps. This allows the XL to
  //  be used as an input sensor, or to be used to detect a bump when then robot
  //  crashes into something.
  
  byte buffer[8]; // There are 8 registers involved in this process; we're going
                  //  to load them into this buffer one at a time.
  
  // Register 0x21: PULSE_CFG
  //  6: enable latching of pulse events into PULSE_SRC register
  //  4: enable single pulse events for z-axis (user input taps)
  //  0: enable single pulse events for x-axis (crash detection)
  buffer[0] = B01010001;
  
  // Register 0x22: PULSE_SRC
  //  This register is read only; this value doesn't matter but we must include a
  //  spacing byte so we can iterate through all the registers brainlessly.
  buffer[1] = 0;
  
  // Register 0x23: PULSE_THSX
  //  Threshold above which a pulse is detected for X-axis. 7-bit value, 0.063g/LSB.
  //  This is crash detection in our system.
  buffer[2] = 5;
  
  // Register 0x24: PULSE_THSY
  //  Y-axis pulse detection.
  buffer[3] = 0;
  
  // Register 0x25: PULSE_THSZ
  //  Z-axis pulse detection. This is user tap detection for us.
  buffer[4] = 5;
  
  // Register 0x26: PULSE_TMLT
  //  8-bit number defining the maximum pulse length of a signal before it's not
  //  considered a pulse anymore. The time base here depends on the mode of the
  //  device (normal, low power low noise, high res, or low power) and is too
  //  complex to cover here; we're in normal mode, 
  
}
