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
const int MECCAFIRM_LED_PINS[]={9,0}; // must end by 0

/**
 * The list of pins dedicated to "wheels".
 * You need extra hardware ("Motor shield or motor driver")
 * in order to make this work.
 * NOT SUPPORTED YET.
 */
const int MECCAFIRM_MOTOR_PINS[]={11,12,0};

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
}

void meccafirmBuiltinLedAck() {
     digitalWrite(LED_BUILTIN, HIGH);
     delayMicroseconds(100);
     digitalWrite(LED_BUILTIN, LOW);  
}

void meccafirmBuiltinLedFastBlink() {
     delay(25);
     digitalWrite(LED_BUILTIN, HIGH);
     delay(100);
     digitalWrite(LED_BUILTIN, LOW);
     delay(25);  
}

void meccafirmBuiltinLedSlowBlink() {
     delay(100);
     digitalWrite(LED_BUILTIN, HIGH);
     delay(400);
     digitalWrite(LED_BUILTIN, LOW);
     delay(100);  
}

void meccafirmBuiltinLedSOS() {
  int i;
  
  for (i=0;i<3;i++) {
    meccafirmBuiltinLedSlowBlink();
  }
  for (i=0;i<3;i++) {
    meccafirmBuiltinLedFastBlink();
  }
  for (i=0;i<3;i++) {
    meccafirmBuiltinLedSlowBlink();
  }
}

void meccafirmLedDebug(byte pin, int value)
{
  int i;
  
  for (i=0;i<=pin;i++) {
   meccafirmBuiltinLedSlowBlink();   
  }
  for (i=0;i<=value;i++) {
   meccafirmBuiltinLedFastBlink();   
  }
}

void meccafirmAnalogWriteCallback(byte pin, int value)
{
  if (meccafirmIsPinServo(pin)==MECCAFIRM_TRUE) {
    meccafirmBuiltinLedAck();
    meccafirmHandleServo(pin, value);
  } else  if (meccafirmIsPinLed(pin)==MECCAFIRM_TRUE){
    meccafirmBuiltinLedAck();
    meccafirmHandleLed(pin, value);
  } else  if (meccafirmIsPinMotor(pin)==MECCAFIRM_TRUE) {
    meccafirmBuiltinLedAck();
    meccafirmHandleMotor(pin, value);
  } else {
    meccafirmBuiltinLedSOS();
    meccafirmHandleError(pin, value, MECCAFIRM_ERROR_INVALID_PIN);
}
}

void meccafirmSetPinModeCallback(byte pin, int mode)
{
      if (IS_PIN_DIGITAL(pin)) {
        pinMode(PIN_TO_DIGITAL(pin), mode);
    }
}

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

 Firmata.setFirmwareVersion(FIRMATA_MAJOR_VERSION, FIRMATA_MINOR_VERSION);
  Firmata.attach(ANALOG_MESSAGE, meccafirmLedDebug);
     Firmata.attach(SET_PIN_MODE, meccafirmSetPinModeCallback);

  Firmata.begin(57600);
}

void loop()
{
  int i;
  while(Firmata.available()) {
    Firmata.processInput();
     for(i = 0; i < TOTAL_ANALOG_PINS; i++) {
 Firmata.sendAnalog(i, analogRead(i)); 
 }
    /*
      for (i = 0; i < TOTAL_PORTS; i++) {
        if (meccafirmIsPinServo(i) || meccafirmIsPinLed(i) || meccafirmIsPinMotor(i)) {
          Firmata.sendDigital(i, digitalRead(i));
        }
        
  }
  */ 
  }
}
