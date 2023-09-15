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

// Function prototypes
void handleJoystickButton();

void setup() {
  lcd.begin(16, 2);  // Initialize the LCD
  Serial.begin(9600);  // Initialize serial communication
  
  pinMode(JOYSTICK_BUTTON, INPUT_PULLUP); // Set joystick button pin as input with pull-up resistor
  attachInterrupt(digitalPinToInterrupt(JOYSTICK_BUTTON), handleJoystickButton, FALLING); // Attach button interrupt
}

void loop() {
  lcd.clear(); // Clear the LCD

  // Display your content on the LCD
  lcd.setCursor(0, 0);
  lcd.print("Press joystick!!");
  lcd.setCursor(0, 1);
  lcd.print("<---------------");

  delay(1000); // Delay for stability
}

// Interrupt handler for joystick button
void handleJoystickButton() {
  unsigned long currentMillis = millis();
  
  if (currentMillis - lastDebounceTime >= DEBOUNCE_DELAY) {
    Serial.println("Button Pressed!");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(" Button Pressed ");
    
    lastDebounceTime = currentMillis;
  }
}
