#include "esp32-hal-ledc.h"
#include "Arduino.h"
#include "Alfredo_NoU.h"
#include "assert.h"

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
    setState(RELEASE);
    setPower(0);
}

void NoU_Motor::setPower(uint16_t power) {
    power = min(power, (1 << MOTOR_PWM_RES) - 1);
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
    power = constrain(power, -1, 1);
    setState(power > 0 ? FORWARD : BACKWARD);
    setPower(fabs(power) * ((1 << MOTOR_PWM_RES) - 1));
}

void NoU_Motor::setInverted(boolean inverted) {
    this->inverted = inverted;
}

boolean NoU_Motor::isInverted() {
    return inverted;
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
    ledcWrite(channel, fmap(degrees, 0, 180, 103, 204));
}

NoU_Drivetrain::NoU_Drivetrain(NoU_Motor* leftMotor, NoU_Motor* rightMotor)
    : frontLeftMotor(leftMotor), frontRightMotor(rightMotor),
        rearLeftMotor(), rearRightMotor(), drivetrainType(TWO_MOTORS)
{ }

NoU_Drivetrain::NoU_Drivetrain(NoU_Motor* frontLeftMotor, NoU_Motor* frontRightMotor,
                                NoU_Motor* rearLeftMotor, NoU_Motor* rearRightMotor)
    : frontLeftMotor(frontLeftMotor), frontRightMotor(frontRightMotor),
        rearLeftMotor(rearLeftMotor), rearRightMotor(rearRightMotor), drivetrainType(FOUR_MOTORS)
{ }

void NoU_Drivetrain::tankDrive(float leftPower, float rightPower) {
    switch (drivetrainType) {
        case FOUR_MOTORS:
            rearLeftMotor->set(constrain((rearLeftMotor->isInverted() ? -1 : 1) * leftPower, -1, 1));
            rearRightMotor->set(constrain((rearRightMotor->isInverted() ? -1 : 1) * rightPower, -1, 1));
        case TWO_MOTORS:
            frontLeftMotor->set(constrain((frontLeftMotor->isInverted() ? -1 : 1) * leftPower, -1, 1));
            frontRightMotor->set(constrain((frontRightMotor->isInverted() ? -1 : 1) * rightPower, -1, 1));
    }
}

void NoU_Drivetrain::arcadeDrive(float throttle, float rotation, boolean invertedReverse) {
    throttle = constrain(throttle, -1, 1);
    rotation = constrain(rotation, -1, 1);
    float leftPower = 0;
    float rightPower = 0;
    float maxInput = (throttle > 0 ? 1 : -1) * max(fabs(throttle), fabs(rotation));
    if (throttle > 0) {
        if (rotation > 0) {
            leftPower = maxInput;
            rightPower = throttle - rotation;
        }
        else {
            leftPower = throttle + rotation;
            rightPower = maxInput;
        }
    } else {
        if (rotation > 0) {
            leftPower = invertedReverse ? maxInput : throttle + rotation;
            rightPower = invertedReverse ? throttle + rotation : maxInput;
        }
        else {
            leftPower = invertedReverse ? throttle - rotation : maxInput;
            rightPower = invertedReverse ? maxInput : throttle - rotation;
        }
    }
    tankDrive(leftPower, rightPower);
}

void NoU_Drivetrain::curvatureDrive(float throttle, float rotation, boolean isQuickTurn, boolean invertedReverse) {
    throttle = constrain(throttle, -1, 1);
    rotation = constrain(rotation, -1, 1);
    float angularPower;
    boolean overPower;
    if (isQuickTurn) {
        if (fabs(throttle) < quickStopThreshold) {
            quickStopAccumulator = (1 - quickStopAlpha) * quickStopAccumulator + quickStopAlpha * rotation * 2;
        }
        overPower = true;
        angularPower = rotation;
    }
    else {
        overPower = false;
        angularPower = fabs(throttle) * rotation - quickStopAccumulator;
    }

    if (quickStopAccumulator > 1) quickStopAccumulator--;
    else if (quickStopAccumulator < -1) quickStopAccumulator++;
    else quickStopAccumulator = 0;

    float leftPower;
    float rightPower;
    if (throttle < 0 && invertedReverse) {
        leftPower = throttle - angularPower;
        rightPower = throttle + angularPower;
    }
    else {
        leftPower = throttle + angularPower;
        rightPower = throttle - angularPower;
    }

    if (throttle < 0 && invertedReverse) {
        leftPower = -leftPower;
        rightPower = -rightPower;
    }

    if (overPower) {
        if (leftPower > 1) {
            rightPower -= leftPower - 1;
            leftPower = 1;
        } else if (rightPower > 1) {
            leftPower -= rightPower - 1;
            rightPower = 1;
        } else if (leftPower < -1) {
            rightPower -= leftPower + 1;
            leftPower = -1;
        } else if (rightPower < -1) {
            leftPower -= rightPower + 1;
            rightPower = -1;
        }
    }
    float maxMagnitude = max(fabs(leftPower), fabs(rightPower));
    if (maxMagnitude > 1) {
        leftPower /= maxMagnitude;
        rightPower /= maxMagnitude;
    }
    tankDrive(leftPower, rightPower);
}

void NoU_Drivetrain::holonomicDrive(float xVelocity, float yVelocity, float rotation) {
    if (drivetrainType == TWO_MOTORS) return;
    xVelocity = constrain(xVelocity, -1, 1);
    yVelocity = constrain(yVelocity, -1, 1);
    rotation = constrain(rotation, -1, 1);
    float frontLeftPower = -xVelocity - yVelocity + rotation;
    float frontRightPower = -xVelocity + yVelocity - rotation;
    float rearLeftPower = -xVelocity + yVelocity + rotation;
    float rearRightPower = -xVelocity - yVelocity - rotation;
    float maxMagnitude = max(fabs(frontLeftPower), max(fabs(frontRightPower), max(fabs(rearLeftPOwer), fabs(rearRightPower))));
    if (maxMagnitude > 1) {
        frontLeftPower /= maxMagnitude;
        frontRightPower /= maxMagnitude;
        rearLeftPower /= maxMagnitude;
        rearRightPower /= maxMagnitude;
    }
    frontLeftMotor->set(constrain((frontLeftMotor->isInverted() ? -1 : 1) * frontLeftPower, -1, 1));
    frontRightMotor->set(constrain((frontRightMotor->isInverted() ? -1 : 1) * frontRightPower, -1, 1));
    rearLeftMotor->set(constrain((rearLeftMotor->isInverted() ? -1 : 1) * rearLeftPower, -1, 1));
    rearRightMotor->set(constrain((rearRightMotor->isInverted() ? -1 : 1) * rearRightPower, -1, 1));
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