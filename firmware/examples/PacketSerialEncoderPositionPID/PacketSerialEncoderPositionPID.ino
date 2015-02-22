//Position PID example.  Velocity PID is not used. Speeds are not controlled by feedback.
//This example is the most like a standard RC servo

#include "spark-roboclaw/spark-roboclaw.h"

SYSTEM_MODE(SEMI_AUTOMATIC)

//Roboclaw Address
#define address 0x80

//Note: PID coeffcients will need to be tuned for this code to work with your motor.

//Velocity PID coefficients
#define Kp 0
#define Ki 0
#define Kd 0
#define Qpps 3600

//Position PID coefficients
#define PosKp 2000
#define PosKi 4
#define PosKd 20000
#define KiMax 12.5
#define DeadZone 10
#define Min 50
#define Max 1950

//Setup communcaitions with roboclaw. Use pins 10 and 11 with 10ms timeout
RoboClaw roboclaw(10000);

//Display Encoder and Speed for Motor 1
void displayspeed(void)
{
  uint8_t status1,status2;
  bool valid1,valid2;
  int32_t enc1 = roboclaw.ReadEncM1(address, &status1, &valid1);
  int32_t speed1 = roboclaw.ReadSpeedM1(address, &status2, &valid2);
  
  if(valid1){
    Serial.print("Encoder1:");
    Serial.print(enc1,DEC);
    Serial.print(" ");
    Serial.print(status1,HEX);
    Serial.print(" ");
  }
  if(valid2){
    Serail.print("Speed1:");
    Serial.print(speed1,DEC);
    Serial.print(" ");
  }
  
  Serial.println();
}

//This function will delay the program so the loop it
//executes in will run no more than every val milliseconds
int lasttime=0;
void rate(int val)
{
  while(millis()-lasttime<val);
  lasttime = millis();
}

void SetPosition(int pos)
{
  //Send position command. The Roboclaw library is using acknowledgement
  //When a valid command is received the roboclaw sends back a byte to ackowledge it.
  if(!roboclaw.SpeedAccelDeccelPositionM1(address,0,3600,0,pos,1))
    Serial.println("SpeedAccelDeccelPositionM1 Failed!");

  displayspeed();
}

//This is the first function arduino runs on reset/power up
void setup() {
  //Open Serial and roboclaw serial ports
  Serial.begin(57600);
  roboclaw.begin(38400);
  
  Serial.println("Starting...");
  
  //Use Absolute Encoder and Enable encoders in RC mode
  roboclaw.SetM1EncoderMode(address,0x81);

  //Set PID Coefficients
  roboclaw.SetM1VelocityPID(address,Kd,Kp,Ki,Qpps);
  roboclaw.SetM1PositionPID(address,PosKd,PosKp,PosKi,KiMax,DeadZone,Min,Max);

  //Save settings in Roboclaw eeprom.  Uncomment to save settings.
  //roboclaw.WriteNVM(address);
}

//Main loop
void loop() {
  for(int pos = 175;pos<1900;pos+=10){
    rate(10);
    SetPosition(pos);
  }

  for(int pos = 1900;pos>175;pos-=10){
    rate(10);
    SetPosition(pos);
  }
}
