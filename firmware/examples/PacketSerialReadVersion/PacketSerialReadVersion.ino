//Includes required to use Roboclaw library
#include "spark-roboclaw/spark-roboclaw.h"

SYSTEM_MODE(SEMI_AUTOMATIC)

//Roboclaw Address
#define address 0x80


//Setup communcaitions with roboclaw. Use pins 10 and 11 with 10ms timeout
RoboClaw rc(10,11,10000);

void setup() {
  //Open terminal and roboclaw serial ports
  Serial.begin(57600);
  rc.begin(38400);
}

void loop() {
  char version[32];

  if(rc.ReadVersion(address,version)){
    Serial.println(version);  
  }

  delay(100);
}

