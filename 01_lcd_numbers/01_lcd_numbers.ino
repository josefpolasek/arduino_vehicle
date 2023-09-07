#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Wire.h>

const int rs = 37, en = 36, d4 = 35, d5 = 34, d6 = 33, d7 = 32;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define AINPUT A1
#define AINPUT33 A0

// Function prototype (declaration)
void voltage_calc();

void setup() {
  lcd.begin(16, 2);
}

void loop() {
  voltage_calc();
}

void voltage_calc() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.write("pot = ");
  lcd.print(analogRead(AINPUT) * 5.0 / 1023, 2);

  lcd.setCursor(0, 1);
  lcd.write("3.3 = ");
  lcd.print(analogRead(AINPUT33) * 5.0 / 1023, 1);
  delay(50);
}
