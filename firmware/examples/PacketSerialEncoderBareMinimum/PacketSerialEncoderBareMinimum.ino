#include "spark-roboclaw/spark-roboclaw.h"

SYSTEM_MODE(SEMI_AUTOMATIC)

#define address 0x80

//Velocity PID coefficients
#define Kp 2
#define Ki 4
#define Kd 0
#define Qpps 14400 //3600

//Define the pins to use and the timeout for serial communications to the Roboclaw
RoboClaw roboclaw(10000);

void setup() {
  //Communicate at 38400bps
  roboclaw.begin(38400);

  //Set Velocity PID coefficients
  roboclaw.SetM1VelocityPID(address,Kd,Kp,Ki,Qpps);
  roboclaw.SetM2VelocityPID(address,Kd,Kp,Ki,Qpps);
}

void loop() {
}
