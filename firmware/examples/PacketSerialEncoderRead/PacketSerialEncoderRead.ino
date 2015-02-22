
//Includes required to use Roboclaw library
#include "spark-roboclaw/spark-roboclaw.h"

SYSTEM_MODE(SEMI_AUTOMATIC)

//Roboclaw Address
#define address 0x80

//Velocity PID coefficients
#define Kp 1.0
#define Ki 0.5
#define Kd 0.25
#define qpps 44000



//Setup communcaitions with roboclaw. Use pins 10 and 11 with 10ms timeout
RoboClaw roboclaw(10,11,10000);

void setup() {
  //Open Serial and roboclaw at 38400bps
  Serial.begin(9600);
  roboclaw.begin(38400);
}

void loop() {
  uint8_t status1,status2,status3,status4;
  bool valid1,valid2,valid3,valid4;
  
  //Read all the data from Roboclaw before displaying on Serial window
  //This prevents the hardware serial interrupt from interfering with
  //reading data using software serial.
  uint32_t enc1= roboclaw.ReadEncM1(address, &status1, &valid1);
  uint32_t enc2 = roboclaw.ReadEncM2(address, &status2, &valid2);
  uint32_t speed1 = roboclaw.ReadSpeedM1(address, &status3, &valid3);
  uint32_t speed2 = roboclaw.ReadSpeedM2(address, &status4, &valid4);

  if(valid1){
    Serial.print("Encoder1:");
    Serial.print(enc1,HEX);
    Serial.print(" ");
    Serial.print(status1,HEX);
    Serial.print(" ");
  }
  if(valid2){
    Serial.print("Encoder2:");
    Serial.print(enc2,HEX);
    Serial.print(" ");
    Serial.print(status2,HEX);
    Serial.print(" ");
  }
  if(valid3){
    Serial.print("Speed1:");
    Serial.print(speed1,HEX);
    Serial.print(" ");
  }
  if(valid4){
    Serial.print("Speed2:");
    Serial.print(speed2,HEX);
    Serial.print(" ");
  }
  Serial.println();
  
  delay(100);
}
