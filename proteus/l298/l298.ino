#include <Stepper.h>
const int stepsPerRevolution = 20; // 360/18
Stepper myStepper(stepsPerRevolution, 11, 10, 9, 8);

void setup(){
// to do 50 rpm
myStepper.setSpeed(50);
pinMode(8, OUTPUT);
pinMode(9, OUTPUT);
pinMode(10, OUTPUT);
pinMode(11, OUTPUT);
Serial.begin(9600);
}

void loop(){
  Serial.println("+360 do theo chieu kim dong ho -->");
  myStepper.step(stepsPerRevolution);
  delay(1000);

  Serial.println("-360 do nguoc chieu kim dong ho -->");
   myStepper.step(~stepsPerRevolution);
   delay(1000);
  }
