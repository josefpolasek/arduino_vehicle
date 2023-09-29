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

void setup() {
    lcd.begin(20, 4);
    Serial.begin(9600);
}

void loop() {
    int xPositionRaw = analogRead(JOYSTICK_X);
    int yPositionRaw = analogRead(JOYSTICK_Y);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(yPositionRaw);
    lcd.setCursor(0, 1);
    lcd.print(xPositionRaw);

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
    }

    // moving backward
    if (yPositionRaw > 530) {
        digitalWrite(Motor_R_dir_pin, Motor_backward);
        digitalWrite(Motor_L_dir_pin, Motor_backward);
        analogWrite(Motor_R_pwm_pin, map(yPositionRaw, 531, 1023, 0, 255));
        analogWrite(Motor_L_pwm_pin, map(yPositionRaw, 531, 1023, 0, 255));
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

    delay(50);
}
