#ifndef Alfredo_NoU
#define Alfredo_NoU

#include <inttypes.h>

// Pins
#define MOTOR1_EN 14
#define MOTOR1_A 12
#define MOTOR1_B 13
#define MOTOR2_EN 15
#define MOTOR2_A 27
#define MOTOR2_B 4
#define MOTOR3_EN 32
#define MOTOR3_A 33
#define MOTOR3_B 25
#define MOTOR4_EN 26
#define MOTOR4_A 23
#define MOTOR4_B 5

#define RSL_PIN 2 // Same as built-in LED

// PWM Channels
#define MOTOR1_CHANNEL 0
#define MOTOR2_CHANNEL 1
#define MOTOR3_CHANNEL 2
#define MOTOR4_CHANNEL 3
#define SERVO1_CHANNEL 4
#define SERVO2_CHANNEL 5
#define SERVO3_CHANNEL 6
#define SERVO4_CHANNEL 7
#define RSL_CHANNEL 8

// PWM Configuration
#define MOTOR_PWM_RES 10 // bits
#define MOTOR_PWM_FREQ 39000 // Based on AF Motor Shield, uses 39kHz for DC Motors
#define SERVO_PWM_RES 16 // bits
#define SERVO_PWM_FREQ 50 // Hz
#define RSL_PWM_RES 10 // bits
#define RSL_PWM_FREQ 1000 // Hz

// Motor states
#define FORWARD 1
#define BACKWARD 2
#define BRAKE 3
#define RELEASE 4

// RSL states
#define RSL_OFF 0
#define RSL_ON 1
#define RSL_DISABLED 2
#define RSL_ENABLED 3

// Drivetrain configurations
#define TWO_MOTORS 0
#define FOUR_MOTORS 1

class NoU_Motor {
    public:
        NoU_Motor(uint8_t motorPort);
        void set(float velocity);
        void setState(uint8_t state);
        void setPower(uint16_t power);
        void setInverted(boolean isInverted);
        boolean isInverted();
    private:
        uint8_t enablePin;
        uint8_t aPin;
        uint8_t bPin;
        uint8_t channel;
        boolean inverted;
};

class NoU_Servo {
    public:
        NoU_Servo(uint8_t pin, uint16_t minPulse = 540, uint16_t maxPulse = 2400);
        void write(float degrees);
        void writeMicroseconds(uint16_t pulseLength);
        void setMinimumPulse(uint16_t minPulse);
        void setMaximumPulse(uint16_t maxPulse);
        uint16_t getMicroseconds();
        float getDegrees();
    private:
        uint8_t pin;
        uint8_t channel;
        uint16_t minPulse;
        uint16_t maxPulse;
        uint16_t pulse;
};

class NoU_Drivetrain {
    public:
        NoU_Drivetrain(NoU_Motor* leftMotor, NoU_Motor* rightMotor);
        NoU_Drivetrain(NoU_Motor* frontLeftMotor, NoU_Motor* frontRightMotor,
                        NoU_Motor* rearLeftMotor, NoU_Motor* rearRightMotor);
        void tankDrive(float leftPower, float rightPower);
        void arcadeDrive(float throttle, float rotation, boolean invertedReverse = false);
        void curvatureDrive(float throttle, float rotation, boolean isQuickTurn, boolean invertedReverse = false);
        void holonomicDrive(float xVelocity, float yVelocity, float rotation);
    private:
        NoU_Motor *frontLeftMotor;
        NoU_Motor *frontRightMotor;
        NoU_Motor *rearLeftMotor;
        NoU_Motor *rearRightMotor;
        uint8_t drivetrainType;
        float quickStopThreshold = 0.2;
        float quickStopAlpha = 0.1;
        float quickStopAccumulator;
};

class RSL {
    public:
        static void initialize();
        static void setState(uint8_t state);
        static void update();
    private:
        static uint8_t state;
};

#endif