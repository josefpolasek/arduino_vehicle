#include <Arduino.h>
#include <Wire.h>

const int rs = 37, en = 36, d4 = 35, d5 = 34, d6 = 33, d7 = 32;

#define RED_LIGHT_LEFT 23
#define YELLOW_LIGHT_LEFT 25
#define GREEN_LIGHT_LEFT 27

#define RED_LIGHT_RIGHT 22
#define YELLOW_LIGHT_RIGHT 24
#define GREEN_LIGHT_RIGHT 26

#define AINPUT A1
#define AINPUT33 A0

void setup() {
  pinMode(RED_LIGHT_LEFT, OUTPUT);
  pinMode(YELLOW_LIGHT_LEFT, OUTPUT);
  pinMode(GREEN_LIGHT_LEFT, OUTPUT);
  pinMode(RED_LIGHT_RIGHT, OUTPUT);
  pinMode(YELLOW_LIGHT_RIGHT, OUTPUT);
  pinMode(GREEN_LIGHT_RIGHT, OUTPUT);
}

void loop() {
  digitalWrite(GREEN_LIGHT_LEFT, HIGH);
  digitalWrite(RED_LIGHT_RIGHT, HIGH);
  delay(1000);
  digitalWrite(GREEN_LIGHT_LEFT, LOW);
  digitalWrite(RED_LIGHT_RIGHT, LOW);

  digitalWrite(YELLOW_LIGHT_RIGHT, HIGH);
  digitalWrite(YELLOW_LIGHT_LEFT, HIGH);
  delay(1000);
  digitalWrite(YELLOW_LIGHT_LEFT, LOW);
  digitalWrite(YELLOW_LIGHT_RIGHT, LOW);

  digitalWrite(RED_LIGHT_LEFT, HIGH);
  digitalWrite(GREEN_LIGHT_RIGHT, HIGH);
  delay(1000);
  digitalWrite(GREEN_LIGHT_RIGHT, LOW);
  digitalWrite(RED_LIGHT_LEFT, LOW);

  digitalWrite(YELLOW_LIGHT_LEFT, HIGH);
  digitalWrite(YELLOW_LIGHT_RIGHT, HIGH);
  delay(1000);
  digitalWrite(YELLOW_LIGHT_RIGHT, LOW);
  digitalWrite(YELLOW_LIGHT_LEFT, LOW);
  Serial.println("one loop");
}
