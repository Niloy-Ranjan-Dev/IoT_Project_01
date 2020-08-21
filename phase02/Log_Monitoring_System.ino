#include <Servo.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(8,9,7,6,5,4);
int ultraSonicPin_00;
int ultraSonicPin_01;

long doorCounter = 0;

int distance00;
int distance01;

int angle;
int servoPin;
int lastDistance00;
int lastDistance01;
long updatedebounceTime;
long debounceTime;
Servo myGate;

int temperatureInputPin; 
float celsius = 0.0;

short row, col;
String message_01 = "Welcome to";
String message_02 = "Nil Cold Storage";
String message_03 = "";
String message_04 = "";



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
  servoPin = 10;
  debounceTime = 5000;
  updatedebounceTime = millis();
  //Servo myGate
  Serial.begin(9600);
  //pinMode(servoPin, OUTPUT);
  myGate.attach(servoPin);
  
  //Teperature
  temperatureInputPin = A5; 
  pinMode(temperatureInputPin, INPUT);
  
  //LCD
  lcd.begin(16, 2);

}

void loop() {
  Serial.println("Angle: ");
  Serial.print(angle);
  myGate.write(angle);

  // measure the ping time in cm
  distance00 = 0.01723 * readDistance(ultraSonicPin_00, ultraSonicPin_00);
  distance01 = 0.01723 * readDistance(ultraSonicPin_01, ultraSonicPin_01);
  
  lcd.clear();

  lcd.setCursor(row, 0);
  lcd.print(message_01);

  lcd.setCursor(row, 1);
  lcd.print(message_02);
  delay(100);
  
  message_04 = "Opened " + String(doorCounter) + " times";
  
  if (((distance00 <= 250) || (distance01 <= 250))&&(angle== 0)) {
    angle = 90;
    Serial.println("Open angle");
    Serial.print(angle);
    doorCounter += 1;
    updatedebounceTime = millis();
    row = 0;

    message_03 = "Gate Opening..";
    message_04 = "Opend " + String(doorCounter) + " times";    
  }
  else if((millis() - updatedebounceTime) >= debounceTime) {
    if (((distance00 > 250) && (distance01 > 250))&&(angle== 90)) {
      angle = 0;
      row = 0;

      message_03 = "Gate Closing..";
    }
  }
  lcd.clear();
  lcd.setCursor(row, 0);
  lcd.print(message_03);

  lcd.setCursor(row, 1);
  lcd.print(message_04);
  delay(100);
  myGate.write(angle);
  
  lcd.clear();
  lcd.setCursor(row, 0);
  lcd.print(message_04);
  celsius = map(((analogRead(temperatureInputPin) - 20) * 3.04), 0, 1023, -40, 125);
  message_03 = "Temp is:" + String(celsius);
  lcd.setCursor(row, 1);
  lcd.print(message_03);
  delay(100);

  lastDistance00 = distance00;
  lastDistance01 = distance01;
}
