#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Wire.h>

// Define pins for LCD
const int RS = 37, EN = 36, D4 = 35, D5 = 34, D6 = 33, D7 = 32;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

// Define joystick pins
const int JOYSTICK_X = A8, JOYSTICK_Y = A9, JOYSTICK_BUTTON = 2;

// Debounce variables for button
const unsigned long DEBOUNCE_DELAY = 50;
unsigned long lastDebounceTime = 0;

void setup() {
  lcd.begin(16, 2);  // Initialize the LCD
  Serial.begin(9600);  // Initialize serial communication
}

void loop() {
  int xPositionRaw = analogRead(JOYSTICK_X);
  int yPositionRaw = analogRead(JOYSTICK_Y);

  int xPercentage = map(xPositionRaw, 0, 1023, -100, 100);
  int yPercentage = map(yPositionRaw, 0, 1023, -100, 100);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("X = ");
  lcd.print(xPercentage);
  lcd.print(" %");

  lcd.setCursor(0, 1);
  lcd.print("Y = ");
  lcd.print(yPercentage);
  lcd.print(" %");

  delay(10);
}
