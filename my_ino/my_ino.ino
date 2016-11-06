#include "MeccaBrain.h"
#include <math.h>

MeccaBrain servoL(5);
MeccaBrain servoR(6);

const int TRIG_PIN = 3;
const int ECHO_PIN = 4;

void setup() {
  // initialize serial communication:
  Serial.begin(9600);

  pinMode(TRIG_PIN,OUTPUT);
  pinMode(ECHO_PIN,INPUT);
}

const int shoulder=0;
const int elbow=1;

void setArticulation(MeccaBrain *mb, int i, float pos) {
  mb->communicate();
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(1);

  if (mb==&servoL) {
    pos=1.0f-pos;
  }
  if (i==elbow) {
    pos=1.0f-pos;
  }
  if (pos>1.0f) {
    pos=1.0f;
  }
  if (pos<0.0f) {
    pos=0.0f;
  }
  mb->setServoPosition(i, (int(pos*float(0xff)))&0xff);
}

void setLeftShoulder(float pos) {
  setArticulation(&servoL,shoulder,pos);
}
void setRightShoulder(float pos) {
  setArticulation(&servoR,shoulder,pos);
}
void setLeftElbow(float pos) {
  setArticulation(&servoL,elbow,pos);
}
void setRightElbow(float pos) {
  setArticulation(&servoR,elbow,pos);
}

void setZero() {
  setLeftShoulder(0);
  setLeftElbow(0);
  setRightShoulder(0);
  setRightElbow(0);
}

void setStraight() {
  setLeftShoulder(0.5);
  setLeftElbow(0.5);
  setRightShoulder(0.5);
  setRightElbow(0.5);
}

void run(int i) {
  setLeftShoulder(0.1);
  setRightShoulder(0.1);
  setLeftElbow((1.0f+cos(float(i)*2.0*PI/7.0))/3.0f);
  setRightElbow((1.0f+cos((float(i)*2.0*PI/7.0)+PI))/3.0f);
}

void nawak(int i) {
  setLeftShoulder((1.0f+cos(float(i)*2.0*PI/5.0))/2.0f);
  setRightShoulder((1.0f+cos(float(i)*2.0*PI/6.0))/2.0f);
  setLeftElbow((1.0f+cos(float(i)*2.0*PI/7.0))/2.0f);
  setRightElbow((1.0f+cos(float(i)*2.0*PI/8.0))/2.0f);
}

void rest(int i) {
    setStraight();
}

void choregraphy(int i) {
  switch ((i/20)%5) {
    case 0:
    case 1:
      run(i);
      break;
    case 2:
    case 3:
      nawak(i);
      break;
    default:
     rest(i);
     break;
  }
}

void loop(){
  //servoL.communicate();
  //servoR.communicate();
  static int counter=0;

  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  //digitalWrite(TRIG_PIN, LOW);
  //delayMicroseconds(2);
  //digitalWrite(TRIG_PIN, HIGH);
  //delayMicroseconds(10);
  //digitalWrite(TRIG_PIN, LOW);

  choregraphy(++counter);
  
  delay(10);
}









