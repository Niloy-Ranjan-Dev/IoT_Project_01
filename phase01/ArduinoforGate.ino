#include <Servo.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(8,9,7,6,5,4);
int ultraSonicPin_00;
int ultraSonicPin_01;

int distance00;
int distance01;

int angle;
int servoPin;
int lastDistance00;
int lastDistance01;
long updatedebounceTime;
long debounceTime;
Servo myGate;

short row, col;
String message_01 = "Nil Cold Storage";
String message_02;


long readDistance(int triggerPin, int echoPin) {
  pinMode(triggerPin, OUTPUT);  // Clear the trigger

  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, LOW);
  delay(2);
  digitalWrite(triggerPin, HIGH);
  delay(5);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

void setup() {
  ultraSonicPin_00 = 2;
  ultraSonicPin_01 = 3;
  angle = 0;
  distance00 = 0;
  distance01 = 0;
  servoPin = A0;
  debounceTime = 5000;
  updatedebounceTime = millis();
  //Servo myGate
  Serial.begin(9600);
  myGate.attach(servoPin);
  
  //LCD
  lcd.begin(16, 2);

}

void loop() {
  // measure the ping time in cm
  distance00 = 0.01723 * readDistance(ultraSonicPin_00, ultraSonicPin_00);
  distance01 = 0.01723 * readDistance(ultraSonicPin_01, ultraSonicPin_01);

  //Serial.print(lastDistance00);
  //Serial.println("Last distance00");

  //Serial.print(distance00);
  //Serial.println("distance0");

  Serial.println(updatedebounceTime);
  Serial.println("updatedebounceTime");
  Serial.println(millis() - updatedebounceTime);

  //if((lastDistance00!=distance00)||(lastDistance01 != distance01)){
  //updatedebounceTime = millis();
  //}
  
  lcd.clear();
  lcd.setCursor(row, 0);
  lcd.print(message_01);

  if ((distance00 <= 250) || (distance01 <= 250)) {
    angle = 90;
    updatedebounceTime = millis();
	row = 0;
	col = 1;
	message_02 = "Gate Opening..";
	lcd.setCursor(row, col);
	lcd.print(message_02);
  }
  else if (((millis() - updatedebounceTime) >= debounceTime)) {
    if ((distance00 > 250) && (distance01 > 250)) {
      angle = 0;
	  row = 0;
	  col = 1;
	  message_02 = "Gate Closing..";
	  lcd.setCursor(row, col);
	  lcd.print(message_02);
    }
  }

  myGate.write(angle);
  delay(1000);

  lastDistance00 = distance00;
  lastDistance01 = distance01;
}
