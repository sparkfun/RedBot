#include <SoftwareSerial.h>
#include <Wire.h>

#define    R_LINE     A6
#define    L_LINE     A2
#define    C_LINE     A3

#define    L_ENC      3
#define    R_ENC      11

#define    L_CTRL_1   2
#define    L_CTRL_2   4
#define    PWM_L      5

#define    R_CTRL_1   7
#define    R_CTRL_2   8
#define    PWM_R      6

#define    SSRX       15   // Software serial RX pin, to XBee TX
#define    SSTX       14   // Software serial TX pin, to xBee RX

#define    XL_ADDR    0x1D // I2C address of the MMA8452Q accelerometer

#define    MOTION_TIMEOUT 3000  // Time allowed for a motion to complete, in ms

SoftwareSerial XBee(SSRX, SSTX);

// The CalLev is the level that we expect to see on a normal background most of the
//  time. We define it by running the robot around a bit before we get started.
int LCalLev = 0;
int CCalLev = 0;
int RCalLev = 0;

// The DetLev is the line brightness level. We define it by collecting some data before
//  we start.
int RDetLev = 0;
int CDetLev = 0;
int LDetLev = 0;

int RBGSD = 0;
int LBGSD = 0;
int CBGSD = 0;

#define BGSD_MIN 15

int RLSD = 0;
int CLSD = 0;
int LLSD = 0;

#define LSD_MIN 15

int RDetOffs = 0;
int CDetOffs = 0;
int LDetOffs = 0;

int RClrOffs = 0;
int CClrOffs = 0;
int LClrOffs = 0;

boolean lightOnDark = true;
boolean noLine = false;

void setup()
{
  Serial.begin(115200);
  XBee.begin(38400);
  Wire.begin();
  pinSetup();
  
  //XBee.println("Press x to skip calibration and disable line sensors.");
  XBee.println("X");
  while (XBee.available() == 0);
  char inputBuffer = XBee.read();
  if (inputBuffer = 'x') noLine = true;
  else
  {
    sensorBGCal();
    sensorLineCal();
    setDetectionMode();
  }
}

void loop()
{
  //XBee.println("Press a number key to move the robot!");
  XBee.println("?");
  while (XBee.available() == 0);
  char inputBuffer = XBee.read();
  switch(inputBuffer)
  {
    case '0':    // Drive straight forward
      driveDist(200, 16);
    break;
    
    case '1':   // Turn right, ~45 degrees
      driveTurn(4, -4);
    break;
    
    case '2':  // Turn right, ~90 degrees
      driveTurn(8, -8);
    break;
    
    case '3': // Don't do anything (could be turn right 135 degrees but isn't)
    break;
    
    case '4': // Reverse
      driveDist(200, -16);
    break;
    
    case '5': // Don't do anything (could be turn left 135 degrees)
    break;
    
    case '6': // Turn left 90 degrees
      driveTurn(-8,8);
    break;
    
    case '7': // Turn left 45 degrees
      driveTurn(-4,4);
    break;
      
    default:
    break;
  }
}

void pinSetup()
{
  pinMode(L_LINE, INPUT);
  pinMode(R_LINE, INPUT);
  pinMode(C_LINE, INPUT);
  pinMode(L_ENC, INPUT);
  pinMode(R_ENC, INPUT);
  pinMode(R_CTRL_1, OUTPUT);
  pinMode(R_CTRL_2, OUTPUT);
  pinMode(L_CTRL_1, OUTPUT);
  pinMode(L_CTRL_2, OUTPUT);
  pinMode(SSRX, INPUT);
  pinMode(SSTX, OUTPUT);
  digitalWrite(SSTX, HIGH);
}  

