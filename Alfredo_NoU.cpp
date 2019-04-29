// Alfredo_NoU.cpp (v0.2)

#include "esp32-hal-ledc.h"
#include "Arduino.h"
#include "Alfredo_NoU.h"

uint8_t RSL::state = RSL_OFF;

float fmap(float val, float in_min, float in_max, float out_min, float out_max) {
    return (val - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

NoU_Motor::NoU_Motor(uint8_t motorPort)
{
    switch (motorPort) {
        case 1:
            enablePin = MOTOR1_EN;
            aPin = MOTOR1_A;
            bPin = MOTOR1_B;
            channel = MOTOR1_CHANNEL;
            break;
        case 2:
            enablePin = MOTOR2_EN;
            aPin = MOTOR2_A;
            bPin = MOTOR2_B;
            channel = MOTOR2_CHANNEL;
            break;
        case 3:
            enablePin = MOTOR3_EN;
            aPin = MOTOR3_A;
            bPin = MOTOR3_B;
            channel = MOTOR3_CHANNEL;
            break;
        case 4:
            enablePin = MOTOR4_EN;
            aPin = MOTOR4_A;
            bPin = MOTOR4_B;
            channel = MOTOR4_CHANNEL;
            break;
    }
    ledcSetup(channel, MOTOR_PWM_FREQ, MOTOR_PWM_RES);
    ledcAttachPin(enablePin, channel);
    pinMode(aPin, OUTPUT);
    pinMode(bPin, OUTPUT);
    pinMode(enablePin, OUTPUT);
}

void NoU_Motor::setPower(int16_t power) {
    // TODO: clamp power
    ledcWrite(channel, power);
}

void NoU_Motor::setState(uint8_t state) {
    switch (state) {
        case FORWARD:
            digitalWrite(aPin, HIGH);
            digitalWrite(bPin, LOW);
            break;
        case BACKWARD:
            digitalWrite(aPin, LOW);
            digitalWrite(bPin, HIGH);
            break;
        case BRAKE:
            digitalWrite(aPin, HIGH);
            digitalWrite(bPin, HIGH);
            break;
        case RELEASE:
            digitalWrite(aPin, LOW);
            digitalWrite(bPin, LOW);
            break;
    }
}

void NoU_Motor::set(float power) {
    power = max(-1.0f, min(1.0f, power)); // clamp power from -1..1
    setState(power > 0 ? FORWARD : BACKWARD);
    setPower(fabs(power) * (1 << MOTOR_PWM_RES));
}

NoU_Servo::NoU_Servo(uint8_t pin) {
    this->pin = pin;
    if (pin == 16) channel = SERVO1_CHANNEL;
    else if (pin == 17) channel = SERVO2_CHANNEL;
    else if (pin == 18) channel = SERVO3_CHANNEL;
    else if (pin == 19) channel = SERVO4_CHANNEL;
    ledcSetup(channel, SERVO_PWM_FREQ, SERVO_PWM_RES);
    ledcAttachPin(pin, channel);
}

void NoU_Servo::write(float degrees) {
    ledcWrite(channel, fmap(degrees, 0, 180, 24, 120));
}

void RSL::initialize() {
    ledcSetup(RSL_CHANNEL, 1000, 10);
    ledcAttachPin(RSL_PIN, RSL_CHANNEL);
}

void RSL::setState(uint8_t state) {
    RSL::state = state;
}

void RSL::update() {
    switch (state) {
        case RSL_OFF:
            ledcWrite(RSL_CHANNEL, 1);
            break;
        case RSL_ON:
            ledcWrite(RSL_CHANNEL, 1023);
            break;
        case RSL_ENABLED:
            ledcWrite(RSL_CHANNEL, millis() % 1000 < 500 ? (millis() % 500) * 2 : (500 - (millis() % 500)) * 2);
            break;
        case RSL_DISABLED:
            ledcWrite(RSL_CHANNEL, 1023);
            break;
    }
}