//Arduino for light

#include <IRremote.h>

const int irPin = 5;
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

	  if (results.value == 0xFD30CF) { //PRESSING 0, turn on all lights
		firstSecLightCtrlPinState  = HIGH;
		secondSecLightCtrlPinState = HIGH;
		thirdSecLightCtrlPinState = HIGH;
	  }
	  else if (results.value == 0xFD08F7) { //PRESSING 1, turn on/off 1st segment lights
		firstSecLightCtrlPinState  = !firstSecLightCtrlPinState;
	  }
	  else if (results.value == 0xFD8877) { //PRESSING 2, turn on/off 2nd segment lights
		secondSecLightCtrlPinState = !secondSecLightCtrlPinState;
	  }
	  else if (results.value == 0xFD48B7) { //PRESSING 3, turn on/off 3rd segment lights
		thirdSecLightCtrlPinState = !thirdSecLightCtrlPinState;
	  }
	  else if (results.value == 0xFD28D7) { //PRESSING 4, turn off all lights
		firstSecLightCtrlPinState  = LOW;
		secondSecLightCtrlPinState = LOW;
		thirdSecLightCtrlPinState = LOW;
	  }
  }

  digitalWrite(firstSecLightCtrlPin, firstSecLightCtrlPinState);
  digitalWrite(secondSecLightCtrlPin, secondSecLightCtrlPinState);
  digitalWrite(thirdSecLightCtrlPin, thirdSecLightCtrlPinState);
}
