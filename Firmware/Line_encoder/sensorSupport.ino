// sensorBGCal() establishes the background level we're operating on. It also tries
//  to get a feel for the relative differences in sensor gain and the homogeneity of
//  the surface by calculating a standard deviation for each sensor.
void sensorBGCal()
{
  XBee.println("B");
  //XBee.println("Press any key to begin background calibration.");
  while (XBee.available() == 0);
  while (XBee.available()) XBee.read();
  //XBee.println("Calibrating...");
  // To calculate our average and standard deviation, we need three values:
  //  - a running mean value (stored in xCalLev)
  //  - a temporary last mean value (stored in xLastMean)
  //  - the most current read value (xLev)
  //  - the running standard deviation (xSD)
  // All those values need to be initialized to zero. I'm going to try and stick
  //  to integer math; float sucks.
  LCalLev = 0;
  RCalLev = 0;
  CCalLev = 0;
  int LLev = 0;
  int RLev = 0;
  int CLev = 0;
  int LQ = 0;
  int RQ = 0;
  int CQ = 0;
  int LLastMean = 0;
  int RLastMean = 0;
  int CLastMean = 0;
    
  for (byte i = 1; i <= 16; i++)
  {
    //XBee.println("Calculating...");
    // First, we need to capture a data point from each sensor.
    LLev = analogRead(L_LINE);
    RLev = analogRead(R_LINE);
    CLev = analogRead(C_LINE);
    // Store the current mean value, then calculate the current running mean.
    LLastMean = LCalLev;
    LCalLev = LCalLev + ((LLev-LCalLev)/i);
    // xQ is an intermediate variable. To find the SD at any step along the way, we'd
    //  do this:
    //    SD = sqrt(xQ/(i-1))
    // For more information on why this is the case, see the wikipedia article on
    //  standard deviation.
    LQ = LQ + ((LLev-LLastMean)*(LLev-LCalLev));
    
    // Now do the right sensor...
    RLastMean = RCalLev;
    RCalLev = RCalLev + ((RLev-RCalLev)/i);
    RQ = RQ + ((RLev-RLastMean)*(RLev-RCalLev));
    
    // And finally, the center sensor.
    CLastMean = CCalLev;
    CCalLev = CCalLev + ((CLev-CCalLev)/i);
    CQ = CQ + ((CLev-CLastMean)*(CLev-CCalLev));
    // The delay here is completely arbitrary. I want to be collecting data for a
    //  goodly amount of time, to get a nice distribution.
    delay(250);
  }
  
  driveStop();
  
  RBGSD = sqrt(RQ/15);
  LBGSD = sqrt(LQ/15);
  CBGSD = sqrt(CQ/15);
  
  if (RBGSD<BGSD_MIN) RBGSD = BGSD_MIN;
  if (CBGSD<BGSD_MIN) CBGSD = BGSD_MIN;
  if (LBGSD<BGSD_MIN) LBGSD = BGSD_MIN;
  
  XBee.print("R: "); XBee.print(RCalLev); XBee.print(", "); XBee.println(RBGSD);
  XBee.print("C: "); XBee.print(CCalLev); XBee.print(", "); XBee.println(CBGSD);
  XBee.print("L: "); XBee.print(LCalLev); XBee.print(", "); XBee.println(LBGSD);
}

// We also need to calibrate for our line brightness. This is a little harder than
//  the BG cal- it requires some user intervention. We'll put down three lines of
//  tape, then take a few calibration readings on the tape by manually moving the
//  robot around and indicating to the calibration routine that we're ready for
//  another reading. It's *just* different enough to the BG cal that we want a
//  different function.
void sensorLineCal()
{
  XBee.println("L");
  //XBee.println("Press any key to begin line calibration.");
  while (XBee.available() == 0);
  while (XBee.available()) XBee.read();
  //XBee.println("Calibrating...");
  // To calculate our average and standard deviation, we need three values:
  //  - a running mean value (stored in xCalLev)
  //  - a temporary last mean value (stored in xLastMean)
  //  - the most current read value (xLev)
  //  - the running standard deviation (xSD)
  // All those values need to be initialized to zero. I'm going to try and stick
  //  to integer math; float sucks.
  LDetLev = 0;
  RDetLev = 0;
  CDetLev = 0;
  int LLev = 0;
  int RLev = 0;
  int CLev = 0;
  int LQ = 0;
  int RQ = 0;
  int CQ = 0;
  int LLastMean = 0;
  int RLastMean = 0;
  int CLastMean = 0;
  
  for (byte i = 1; i <= 16; i++)
  {
    //XBee.println("Calculating...");
    // First, we need to capture a data point from each sensor.
    LLev = analogRead(L_LINE);
    RLev = analogRead(R_LINE);
    CLev = analogRead(C_LINE);
    // Store the current mean value, then calculate the current running mean.
    LLastMean = LDetLev;
    LDetLev = LDetLev + ((LLev-LDetLev)/i);
    // xQ is an intermediate variable. To find the SD at any step along the way, we'd
    //  do this:
    //    SD = sqrt(xQ/(i-1))
    // For more information on why this is the case, see the wikipedia article on
    //  standard deviation.
    LQ = LQ + ((LLev-LLastMean)*(LLev-LDetLev));
    
    // Now do the right sensor...
    RLastMean = RDetLev;
    RDetLev = RDetLev + ((RLev-RDetLev)/i);
    RQ = RQ + ((RLev-RLastMean)*(RLev-RDetLev));
    
    // And finally, the center sensor.
    CLastMean = CDetLev;
    CDetLev = CDetLev + ((CLev-CDetLev)/i);
    CQ = CQ + ((CLev-CLastMean)*(CLev-CDetLev));
    delay(250);
  }
  
  RLSD = sqrt(RQ/15);
  LLSD = sqrt(LQ/15);
  CLSD = sqrt(CQ/15);
  
  if (RLSD<LSD_MIN) RLSD = LSD_MIN;
  if (CLSD<LSD_MIN) CLSD = LSD_MIN;
  if (LLSD<LSD_MIN) LLSD = LSD_MIN;
  
  XBee.print("R: "); XBee.print(RDetLev); XBee.print(", "); XBee.println(RLSD);
  XBee.print("C: "); XBee.print(CDetLev); XBee.print(", "); XBee.println(CLSD);
  XBee.print("L: "); XBee.print(LDetLev); XBee.print(", "); XBee.println(LLSD);
}

void setDetectionMode(void)
{
  if (RCalLev > RDetLev) lightOnDark = true;
  else                   lightOnDark = false;
  if (lightOnDark) XBee.println("Light on dark mode.");
  else             XBee.println("Dark on light mode.");
}

byte sensorScan(void)
{
  #define NUM_SAMPS 3
  byte result = 0;
  
  int RLev[NUM_SAMPS]; 
  int CLev[NUM_SAMPS];
  int LLev[NUM_SAMPS];
  
  for (byte i = 0; i<NUM_SAMPS; i++)
  {
    RLev[i] = analogRead(R_LINE);
    CLev[i] = analogRead(C_LINE);
    LLev[i] = analogRead(L_LINE);
  }
  
  if (lightOnDark)
  {
    if (RLev[0]<(RDetLev+(RLSD<<1))) result |= 0x01;  
    if (CLev[0]<(CDetLev+(CLSD<<1))) result |= 0x02;  
    if (LLev[0]<(LDetLev+(LLSD<<1))) result |= 0x04;  
  }
  else
  {
    if (RLev[0]>(RDetLev-(RLSD<<1))) result |= 0x01;  
    if (CLev[0]>(CDetLev-(CLSD<<1))) result |= 0x02;  
    if (LLev[0]>(LDetLev-(LLSD<<1))) result |= 0x04;  
  }
  
  for (byte i = 1; i<NUM_SAMPS; i++)
  {
    if (lightOnDark)
    {
      if (RLev[0]<(RDetLev+(RLSD<<1))) result &= 0x01;  
      if (CLev[0]<(CDetLev+(CLSD<<1))) result &= 0x02;  
      if (LLev[0]<(LDetLev+(LLSD<<1))) result &= 0x04;  
    }
    else
    {
      if (RLev[0]>(RDetLev-(RLSD<<1))) result &= 0x01;  
      if (CLev[0]>(CDetLev-(CLSD<<1))) result &= 0x02;  
      if (LLev[0]>(LDetLev-(LLSD<<1))) result &= 0x04;  
    }
  }
  return result;
}

