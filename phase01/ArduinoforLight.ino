//Arduino for light

#include <IRremote.h>

const int irPin = 8;
const int firstSecLightCtrlPin = 2;
const int secondSecLightCtrlPin = 3;
const int thirdSecLightCtrlPin = 4;
bool firstSecLightCtrlPinState = LOW;
bool secondSecLightCtrlPinState = LOW;
bool thirdSecLightCtrlPinState = LOW;

IRrecv irrecv(irPin);
decode_results results;

void setup()
{
  Serial.begin(9600);
  pinMode(firstSecLightCtrlPin, OUTPUT);
  pinMode(secondSecLightCtrlPin, OUTPUT);
  pinMode(thirdSecLightCtrlPin, OUTPUT);

  irrecv.enableIRIn();
}

void loop()
{
  //Serial.write();
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume();
    //delay(100);
  }

  if (results.value == 0xFD30CF) { //PRESSING 0, turn on all lights
    firstSecLightCtrlPinState  = HIGH;
    secondSecLightCtrlPinState = HIGH;
    thirdSecLightCtrlPinState = HIGH;
  }
  else if (results.value == 0xFD08F7) { //PRESSING 1, turn on 1st segment lights
    firstSecLightCtrlPinState  = HIGH;
  }
  else if (results.value == 0xFD8877) { //PRESSING 2, turn on 2nd segment lights
    secondSecLightCtrlPinState = HIGH;
  }
  else if (results.value == 0xFD48B7) { //PRESSING 3, turn on 3rd segment lights
    thirdSecLightCtrlPinState = HIGH;
  }
  else if (results.value == 0xFD28D7) { //PRESSING 4, turn off 1st segment lights
    firstSecLightCtrlPinState  = LOW;
  }
  else if (results.value == 0xFDA857) { //PRESSING 5, turn off 2nd segment lights
    secondSecLightCtrlPinState = LOW;
  }
  else if (results.value == 0xFD6897) { //PRESSING 6, turn off 3rd segment lights
    thirdSecLightCtrlPinState = LOW;
  }
  else if (results.value == 0xFD18E7) { //PRESSING 7, turn off all lights
    firstSecLightCtrlPinState  = LOW;
    secondSecLightCtrlPinState = LOW;
    thirdSecLightCtrlPinState = LOW;
  }


  digitalWrite(firstSecLightCtrlPin, firstSecLightCtrlPinState);
  digitalWrite(secondSecLightCtrlPin, secondSecLightCtrlPinState);
  digitalWrite(thirdSecLightCtrlPin, thirdSecLightCtrlPinState);
}
