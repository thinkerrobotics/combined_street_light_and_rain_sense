#include <Servo.h>

// Pin assignments for street light control
const int IR1 = 2;
const int IR2 = 3;
const int IR3 = 4;
const int LDR = 5;
const int led1 = 6;
const int led2 = 7;
const int led3 = 8;

// Pin assignments for rain sensor control
const int rain_sensor = A0;
const int servo_pin = 9;

Servo myServo;

void setup() {
  // Street light control setup
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
  pinMode(LDR, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  
  // Rain sensor control setup
  myServo.attach(servo_pin);
  myServo.write(0);

  Serial.begin(9600);
}

void loop() {
  // Street light control
  int val1 = digitalRead(IR1);
  int val2 = digitalRead(IR2);
  int val3 = digitalRead(IR3);
  int val4 = digitalRead(LDR);

  if (val1 == 1 && val4 == 0 && val2 == 1 && val3 == 1) {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
  }
  else if (val1 == 1 && val4 == 1 && val2 == 1 && val3 == 1) {
    analogWrite(led1, 20);
    analogWrite(led2, 20);
    analogWrite(led3, 20);
  }
  else if (val1 == 0 && val4 == 1 && val2 == 1 && val3 == 1) {
    analogWrite(led1, 500);
    analogWrite(led2, 20);
    analogWrite(led3, 20);
  }
  else if (val1 == 1 && val4 == 1 && val2 == 0 && val3 == 1) {
    analogWrite(led1, 20);
    analogWrite(led2, 500);
    analogWrite(led3, 20);
  }
  else if (val1 == 1 && val4 == 1 && val2 == 1 && val3 == 0) {
    analogWrite(led1, 20);
    analogWrite(led2, 20);
    analogWrite(led3, 500);
  }

  // Rain sensor control
  int sensorValue = analogRead(rain_sensor);
  int motorAngle = map(sensorValue, 220, 1023, 180, 0);
  myServo.write(motorAngle);

  Serial.print("Street Light Sensor values: ");
  Serial.print(val1);
  Serial.print(val2);
  Serial.print(val3);
  Serial.print(val4);

  Serial.print(" Rain Sensor value: ");
  Serial.print(sensorValue);

  Serial.print(" Servo motor angle: ");
  Serial.println(motorAngle);

  delay(1000);
}
