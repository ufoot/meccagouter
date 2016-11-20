/*
 * http://firmata.org/wiki/Download
 */

#include <Firmata.h>
#include "MeccaBrain.h"

/**
 * The list of pins dedicated to "smart servo modules".
 * Connect these pins to the arms (shoulders, elbows) of the meccanoid robot,
 * or to the corresponding servos if your meccanoid setup is
 * not a humanoid any more. Technically, you might only need
 * two of them if, for instance, you chain two servos on each pin.
 */
const int MECCAFIRM_SERVO_PINS[]={5,6,7,8,0}; // must end by 0

/**
 * The list of pins dedicated to "smart LED modules".
 * Connect the pins to the head (eyes) of the meccanoid robot.
 * NOT SUPPORTED YET.
 */
const int MECCAFIRM_LED_PINS[]={9,10,0}; // must end by 0

/**
 * The list of pins dedicated to "wheels".
 * You need extra hardware ("Motor shield or motor driver")
 * in order to make this work.
 * NOT SUPPORTED YET.
 */
const int MECCAFIRM_MOTOR_PINS[]={11,12,0};

/**
 * Pin ID used to report errors, bind this to the builtin LED.
 * See https://www.arduino.cc/en/tutorial/blink for details, I use 13
 * for an Arduino UNO but this depends on the hardware you have.
 */
const int MECCAFIRM_LED_BUILTIN=LED_BUILTIN;

const int MECCAFIRM_TRUE=1;
const int MECCAFIRM_FALSE=0;

const char *MECCAFIRM_ERROR_INVALID_PIN="invalid pin";

static int meccafirmIsPin(int pin, const int *pins) {
  int i,p;
  for (i=0; (p=pins[i])!=0; i++) {
    if (p==pin) {
    return MECCAFIRM_TRUE;
  }
}
return MECCAFIRM_FALSE;
}

int meccafirmIsPinServo(int pin) {
  return meccafirmIsPin(pin, MECCAFIRM_SERVO_PINS);
}

int meccafirmIsPinLed(int pin) {
  return meccafirmIsPin(pin, MECCAFIRM_LED_PINS);
}

int meccafirmIsPinMotor(int pin) {
  return meccafirmIsPin(pin, MECCAFIRM_MOTOR_PINS);
}

void meccafirmHandleServo(int pin, int value) {
}

void meccafirmHandleLed(int pin, int value) {
}

void meccafirmHandleMotor(int pin, int value) {
  
}

void meccafirmHandleError(int pin, int value, const char *msg) {
  // this should never happen, it's complicated, on a
  // platform like Arduino, to report errors, but if you
  // have a way to do so (custom led, serial output...)
  // do it here! By default, the builtin led blinks.
  int i;
  
  for (i=0;i<3;i++) {
     digitalWrite(LED_BUILTIN, HIGH);
     delay(50);
     digitalWrite(LED_BUILTIN, LOW);
     delay(25);
  }
}

void meccafirmAnalogWriteCallback(byte pin, int value)
{
  meccafirmHandleError(pin, value, MECCAFIRM_ERROR_INVALID_PIN);
  /*
  if (meccafirmIsPinServo(pin)==MECCAFIRM_TRUE) {
    meccafirmHandleServo(pin, value);
  } else  if (meccafirmIsPinLed(pin)==MECCAFIRM_TRUE){
    meccafirmHandleLed(pin, value);
  } else  if (meccafirmIsPinMotor(pin)==MECCAFIRM_TRUE) {
    meccafirmHandleMotor(pin, value);
  } else {
    meccafirmHandleError(pin, value, MECCAFIRM_ERROR_INVALID_PIN);
  }
  */
}

void setup()
{
  pinMode(MECCAFIRM_LED_BUILTIN, OUTPUT);

  Firmata.setFirmwareVersion(0, 2);
  Firmata.attach(ANALOG_MESSAGE, meccafirmAnalogWriteCallback);

  Firmata.begin(57600);
}

void loop()
{
  int s;
  digitalWrite(MECCAFIRM_LED_BUILTIN, HIGH);
  while(Firmata.available()) {
    Firmata.processInput();
    digitalWrite(MECCAFIRM_LED_BUILTIN, (s=!s) ?HIGH:LOW);
  }
}
