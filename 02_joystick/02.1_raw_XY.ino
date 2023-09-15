#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Wire.h>

// Define pins for LCD
const int RS = 37, EN = 36, D4 = 35, D5 = 34, D6 = 33, D7 = 32;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

// Define joystick pins
const int JOYSTICK_X = A8, JOYSTICK_Y = A9, JOYSTICK_BUTTON = 2;

void setup() {
  lcd.begin(16, 2);  // Initialize the LCD
  Serial.begin(9600);  // Initialize serial communication
}

void loop() {
  int xPosition = analogRead(JOYSTICK_X);
  int yPosition = analogRead(JOYSTICK_Y);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("X: ");
  lcd.print(xPosition);

  lcd.setCursor(0, 1);
  lcd.print("Y: ");
  lcd.print(yPosition);

  delay(10);
}

