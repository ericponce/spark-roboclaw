#include "spark-roboclaw/spark-roboclaw.h"

SYSTEM_MODE(SEMI_AUTOMATIC)

#define address 0x80


RoboClaw roboclaw(10000);

void setup() {
  roboclaw.begin(38400);

  // put your setup code here, to run once:
}

void loop() {

  // put your main code here, to run repeatedly: 
 
}
