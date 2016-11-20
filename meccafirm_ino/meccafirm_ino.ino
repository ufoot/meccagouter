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
const int[] MECCAFIRM_SERVO_PINS={5,6,7,8,0}; // must end by 0

/**
 * The list of pins dedicated to "smart LED modules".
 * Connect the pins to the head (eyes) of the meccanoid robot.
 * NOT SUPPORTED YET.
 */
const int[] MECCAFIRM_LED_PINS={9,10,0}; // must end by 0

/**
 * The list of pins dedicated to "wheels".
 * You need extra hardware ("Motor shield or motor driver")
 * in order to make this work.
 * NOT SUPPORTED YET.
 */
const int[] MECCAFIRM_MOTOR_PINS={11,12,13,14,0};

const int MECCAFIRM_TRUE=1;
const int MECCAFIRM_FALSE=0;

const char *MECCAFIRM_INVALID_PIN="invalid pin";

static int meccafirmIsPin(int pin, int *pins) {
  int i,p;
  for (i=0; (p=pins[i])!=0; ++i) {
    if (p==pin)) {
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
  // do it here!
}

void meccafirmAnalogWriteCallback(byte pin, int value)
{
  if (meccafirmIsPinServo(pin)) {
    meccafirmHanldeServo(pin, value);
  } else  if (meccafirmIsPinLed(pin)) {
    meccafirmHanldeLed(pin, value);
  } else  if (meccafirmIsPinMotor(pin)) {
    meccafirmHanldeMotor(pin, value);
  } else {
    meccafirmHandleError(pin, value, MECCAFIRM_ERROR_INVALID_PIN);
  }
}

void setup()
{
  byte pin;

  Firmata.setFirmwareVersion(0, 2);
  Firmata.attach(ANALOG_MESSAGE, meccafirmAnalogWriteCallback);

  Firmata.begin(57600);
}

void loop()
{
  while(Firmata.available()) {
    Firmata.processInput();
  }
}
