#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#define CMPS14_address 0x60

#include <LiquidCrystal.h>
#define Motor_forward 1
#define Motor_backward 0
#define Motor_L_dir_pin 7
#define Motor_R_dir_pin 8
#define Motor_L_pwm_pin 9
#define Motor_R_pwm_pin 10

const int RS = 37, EN = 36, D4 = 35, D5 = 34, D6 = 33, D7 = 32;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

const int JOYSTICK_X = A8, JOYSTICK_Y = A9;

int pwm_R = 0;
int pwm_L = 0;

////////////////////////
// attach interrupt works only for certain pins
#define encoderMotorR 18
#define encoderMotorL 19

// volatile int pulseCount = 0;
volatile int pulseCount_R = 0;
volatile int pulseCount_L = 0;

void handleEncoderR() { pulseCount_R++; }

void handleEncoderL() { pulseCount_L++; }

//////////////////

void setup() {
    //////////////////
    pinMode(encoderMotorR, INPUT);
    pinMode(encoderMotorL, INPUT);

    attachInterrupt(digitalPinToInterrupt(encoderMotorR), handleEncoderR,
                    RISING);
    attachInterrupt(digitalPinToInterrupt(encoderMotorL), handleEncoderL,
                    RISING);

    //////////////////

    lcd.begin(20, 4);
    Serial.begin(9600);
    // Start the I2C interface
    Wire.begin();
}

void loop() {
    int xPositionRaw = analogRead(JOYSTICK_X);
    int yPositionRaw = analogRead(JOYSTICK_Y);

    lcd.clear();
    //////////////////

    lcd.setCursor(0, 0);
    // lcd.print(yPositionRaw);
    lcd.print("L: ");
    lcd.print(pulseCount_L);

    lcd.setCursor(0, 1);
    lcd.print("R: ");
    lcd.print(pulseCount_R);
    // lcd.print(xPositionRaw);
    //////////////////

    if (yPositionRaw >= 470 && yPositionRaw <= 530 && xPositionRaw >= 470 &&
        xPositionRaw <= 530) {
        analogWrite(Motor_R_pwm_pin, 0);
        analogWrite(Motor_L_pwm_pin, 0);
    }

    // moving forward
    if (yPositionRaw < 470) {
        digitalWrite(Motor_R_dir_pin, Motor_forward);
        digitalWrite(Motor_L_dir_pin, Motor_forward);
        analogWrite(Motor_R_pwm_pin, map(yPositionRaw, 469, 0, 0, 255));
        analogWrite(Motor_L_pwm_pin, map(yPositionRaw, 469, 0, 0, 255));

        // turning left while moving forward
        if (xPositionRaw > 530) {
            analogWrite(
                Motor_L_pwm_pin,
                map(xPositionRaw, 531, 1023, map(yPositionRaw, 469, 0, 0, 255),
                    map(yPositionRaw, 469, 0, 0, 255) / 2));
        }

        // turning right while moving forward
        if (xPositionRaw < 470) {
            analogWrite(
                Motor_R_pwm_pin,
                map(xPositionRaw, 469, 0, map(yPositionRaw, 469, 0, 0, 255),
                    map(yPositionRaw, 469, 0, 0, 255) / 2));
        }
    }

    // moving backward
    if (yPositionRaw > 530) {
        digitalWrite(Motor_R_dir_pin, Motor_backward);
        digitalWrite(Motor_L_dir_pin, Motor_backward);
        analogWrite(Motor_R_pwm_pin, map(yPositionRaw, 531, 1023, 0, 255));
        analogWrite(Motor_L_pwm_pin, map(yPositionRaw, 531, 1023, 0, 255));

        // turning left while moving backward
        if (xPositionRaw > 530) {
            analogWrite(Motor_L_pwm_pin,
                        map(xPositionRaw, 531, 1023,
                            map(yPositionRaw, 531, 1023, 0, 255),
                            map(yPositionRaw, 531, 1023, 0, 255) / 2));
        }

        // turning right while moving backward
        if (xPositionRaw < 470) {
            analogWrite(
                Motor_R_pwm_pin,
                map(xPositionRaw, 469, 0, map(yPositionRaw, 531, 1023, 0, 255),
                    map(yPositionRaw, 531, 1023, 0, 255) / 2));
        }
    }

    // turning left
    if (xPositionRaw > 530 && yPositionRaw >= 470 && yPositionRaw <= 530) {
        digitalWrite(Motor_R_dir_pin, Motor_forward);
        digitalWrite(Motor_L_dir_pin, Motor_backward);
        analogWrite(Motor_R_pwm_pin, map(xPositionRaw, 531, 1023, 0, 255));
        analogWrite(Motor_L_pwm_pin, map(xPositionRaw, 531, 1023, 0, 255));
    }

    // turning right
    if (xPositionRaw < 470 && yPositionRaw >= 470 && yPositionRaw <= 530) {
        digitalWrite(Motor_R_dir_pin, Motor_backward);
        digitalWrite(Motor_L_dir_pin, Motor_forward);
        analogWrite(Motor_R_pwm_pin, map(xPositionRaw, 470, 0, 0, 255));
        analogWrite(Motor_L_pwm_pin, map(xPositionRaw, 470, 0, 0, 255));
    }

    // Request a single byte from the compass
    Wire.beginTransmission(CMPS14_address);
    Wire.write(1);  // This is the register we wish to read
    Wire.endTransmission(false);

    // Now request a single byte of data from the compass
    Wire.requestFrom(CMPS14_address, 1, true);

    if (Wire.available() >= 1) {
        // Read the bearing data (8-bit)
        uint8_t raw = Wire.read();

        // Display the raw bearing data on the LCD
        lcd.setCursor(0, 4);
        lcd.print(raw);
    }

    delay(50);
}
