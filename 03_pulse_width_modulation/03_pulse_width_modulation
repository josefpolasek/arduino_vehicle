#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Wire.h>

// Define pins for LCD
const int RS = 37, EN = 36, D4 = 35, D5 = 34, D6 = 33, D7 = 32;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

// Define joystick pins
const int JOYSTICK_X = A8, JOYSTICK_Y = A9;
const int SW = 2;
bool ledIsOn = true;

// Define LED pins
const int LED1 = 12, LED2 = 13;

// Define function for button press
void buttonPressed();

// Debounce variables for button
const unsigned long debounceDelay = 200;
unsigned long lastDebounceTime = 0;

void setup() {
    lcd.begin(20, 4);    // Initialize the LCD
    Serial.begin(9600);  // Initialize serial communication

    // Initialize LED pins as output
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(SW, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(SW), buttonPressed, FALLING);
}

void loop() {
    if (!ledIsOn) {
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
        return;
    }

    int xPositionRaw = analogRead(JOYSTICK_X);
    int yPositionRaw = analogRead(JOYSTICK_Y);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(yPositionRaw);
    lcd.setCursor(0, 1);
    lcd.print(xPositionRaw);

    int xPercentage = map(xPositionRaw, 0, 1023, -100, 100);
    int yPercentage = map(yPositionRaw, 0, 1023, -100, 100);

    // Control brightness based on Y - axis
    int brightness = map(abs(yPositionRaw), 0, 1023, 255, 0);

    // Control which LED is active based on X - axis
    if (xPositionRaw > 493) {
        analogWrite(LED1, brightness);
        digitalWrite(LED2, LOW);
    } else {
        analogWrite(LED2, brightness);
        digitalWrite(LED1, LOW);
    }

    delay(50);
}

void buttonPressed() {
    if ((millis() - lastDebounceTime) > debounceDelay) {
        Serial.println("Pressed");
        ledIsOn = !ledIsOn;
        lastDebounceTime = millis();
    }
}
