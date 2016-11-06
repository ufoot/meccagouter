#include "MeccaBrain.h"

MeccaBrain servo(3);
 
const int TRIG_PIN = 3;
const int ECHO_PIN = 4; 
 
void setup() {
  // initialize serial communication:
  Serial.begin(9600);
 
  pinMode(TRIG_PIN,OUTPUT);
  pinMode(ECHO_PIN,INPUT);
}
 
void loop(){
  servo.communicate();
int pos0=0x20;
int pos1=0;

  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
 
 pos0++;
 pos1=pos0+0x20;
 pos0=pos0%0x7f;
 pos1=pos1%0x7f;
  servo.setServoPosition(0,pos0);
  servo.setServoPosition(1,pos1);
  
  delayMicroseconds(10000000);
}









