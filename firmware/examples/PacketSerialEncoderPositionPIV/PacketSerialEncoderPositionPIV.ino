/17 or 18/19.

//Includes required to use Roboclaw library
#include "spark-roboclaw/spark-roboclaw.h"

SYSTEM_MODE(SEMI_AUTOMATIC)

//Roboclaw Address
#define address 0x80

//Note: PID coeffcients will need to be tuned for this code to work with your motor.

//Velocity PID coefficients
#define Kp 2
#define Ki 4
#define Kd 0
#define Qpps 14400 //3600

//Position PID coefficients
#define PosKp 2500
#define PosKi 0
#define PosKd 20000
#define KiMax 0
#define DeadZone 5 //10
#define Min 50
#define Max 1950

//Setup communcaitions with roboclaw. Use pins 10 and 11 with 10ms timeout
RoboClaw roboclaw(10,11,10000);

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
    Serial.print("Speed1:");
    Serial.print(speed1,DEC);
    Serial.print(" ");
  }
  
  Serial.println();
}

void SetPosition(int accel,int speed,int deccel,int pos)
{
  //Send position command. The Roboclaw library is using acknowledgement
  //When a valid command is received the roboclaw sends back a byte to ackowledge it.
  if(!roboclaw.SpeedAccelDeccelPositionM1(address,accel,speed,deccel,pos,1))
    Serial.println("SpeedAccelDeccelPositionM1 Failed!");
}

//This is the first function arduino runs on reset/power up
void setup() {
  //Open Serial and roboclaw at 38400bps
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

void loop() {
  SetPosition(32000,1000,32000,1700);
  uint32_t last = millis();
  while(millis()-last<5000){
    displayspeed();
    delay(50);
  }

  SetPosition(32000,1000,32000,300);
  last = millis();
  while(millis()-last<5000){
    displayspeed();
    delay(50);
  }
}
