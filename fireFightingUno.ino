#include <Servo.h>

Servo myservo;  // Create a servo object

int servoPin = 3;  // The PWM pin the servo is connected to
const int fireSensor = 2; // Pin number for the button
const int appWaterButton = 6;
const int relayPin = 4;
const int buzzer = 5;

void setup() {
  myservo.attach(servoPin);
  pinMode(fireSensor, INPUT_PULLUP); // Set the button pin as an input
  pinMode(appWaterButton, INPUT_PULLUP);
  pinMode(relayPin, OUTPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(relayPin, HIGH);
  digitalWrite(buzzer, LOW);
  Serial.begin(9600);       // Initialize serial communication at 9600 baud
}

void loop() {
  myservo.write(90);//90 degree
  digitalWrite(buzzer, LOW);
  digitalWrite(relayPin, HIGH);
  int sensorState = digitalRead(fireSensor); // Read the state of the button
  int appButtonState = digitalRead(appWaterButton); 

  if (sensorState == LOW || appButtonState == LOW) {
Serial.println("Water Flow");
    digitalWrite(relayPin, LOW);
    digitalWrite(buzzer, HIGH);
    for (int i = 40; i < 140; i++) {
      myservo.write(i);
      delay(5);                   // Wait for 500 milliseconds
    }
    delay(1000);
    for (int i = 140; i > 40; i--) {
      myservo.write(i);
      delay(5);                   // Wait for 500 milliseconds
    }

    delay(1000);
    for (int i = 40; i > 90; i--) {
      myservo.write(i);
      delay(5);                   // Wait for 500 milliseconds
    }
    delay(50);
    digitalWrite(buzzer, LOW);
    digitalWrite(relayPin, HIGH);
  }

  delay(50); // Add a small delay to debounce the button
}
