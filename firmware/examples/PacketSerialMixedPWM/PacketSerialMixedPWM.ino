//Includes required to use Roboclaw library
#include "spark-roboclaw/spark-roboclaw.h"

SYSTEM_MODE(SEMI_AUTOMATIC)

//Roboclaw Address
#define address 0x80

//Setup communcaitions with roboclaw. Use pins 10 and 11 with 10ms timeout
RoboClaw roboclaw(10,11,10000);

void setup() {
  //Communciate with roboclaw at 38400bps
  roboclaw.begin(38400);
}

void loop() {
  roboclaw.ForwardMixed(address, 64);
  delay(2000);
  roboclaw.BackwardMixed(address, 64);
  delay(2000);
  roboclaw.TurnRightMixed(address, 64);
  delay(2000);
  roboclaw.TurnLeftMixed(address, 64);
  delay(2000);
  roboclaw.ForwardBackwardMixed(address, 32);
  delay(2000);
  roboclaw.ForwardBackwardMixed(address, 96);
  delay(2000);
  roboclaw.LeftRightMixed(address, 32);
  delay(2000);
  roboclaw.LeftRightMixed(address, 96);
  delay(2000);
}
