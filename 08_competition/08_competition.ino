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
#define encoderMotorR 18
#define encoderMotorL 19

// volatile int pulseCount = 0;
volatile int pulseCount_R = 0;
volatile int pulseCount_L = 0;
volatile int lastEncoderState_R = 0;
volatile int lastEncoderState_L = 0;

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
    Serial.println(pulseCount_L);

    int forward = 730;
    int right = 275;
    int second_forward = 450;

    if (pulseCount_L <= forward) {
        digitalWrite(Motor_R_dir_pin, Motor_forward);
        digitalWrite(Motor_L_dir_pin, Motor_forward);
        analogWrite(Motor_R_pwm_pin, 255);
        analogWrite(Motor_L_pwm_pin, 255);
    } else if (pulseCount_L <= (forward + right)) {
        analogWrite(Motor_R_pwm_pin, 0);
        digitalWrite(Motor_L_dir_pin, Motor_forward);

        analogWrite(Motor_L_pwm_pin, 100);
    } else if (pulseCount_L <= (forward + right + second_forward)) {
        digitalWrite(Motor_R_dir_pin, Motor_forward);
        digitalWrite(Motor_L_dir_pin, Motor_forward);
        analogWrite(Motor_R_pwm_pin, 255);
        analogWrite(Motor_L_pwm_pin, 255);
    } else {
        analogWrite(Motor_R_pwm_pin, 0);
        analogWrite(Motor_L_pwm_pin, 0);
    }

    delay(50);
}
