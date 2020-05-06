#include <BluetoothSerial.h>
#include <Alfredo_NoU2.h>

BluetoothSerial bluetooth;

NoU_Motor frontLeftMotor(1);
NoU_Motor frontRightMotor(2);
NoU_Motor rearLeftMotor(3);
NoU_Motor rearRightMotor(4);
NoU_Servo servo(16);

NoU_Drivetrain drivetrain(&frontLeftMotor, &frontRightMotor, &rearLeftMotor, &rearRightMotor);

float throttle, rotation, servoAxis;
long lastTimePacketReceived = 0;

void setup() {
    Serial.begin(9600);
    RSL::initialize();
    bluetooth.begin("DefaultBot");
    frontLeftMotor.setInverted(false);
    frontRightMotor.setInverted(false);
    rearLeftMotor.setInverted(false);
    rearRightMotor.setInverted(false);
}

void loop() {
    while (bluetooth.available() > 0) {
        lastTimePacketReceived = millis();
        if ((bluetooth.read()) == 'z') {
            throttle = -bluetooth.parseFloat();
            rotation = bluetooth.parseFloat();
            servoAxis = bluetooth.parseFloat();
        }
    }
    servo.write((servoAxis + 1) * 90);
    if (fabs(throttle) < 0.2) {
        drivetrain.curvatureDrive(throttle, rotation, true);
    }
    else {
        drivetrain.curvatureDrive(throttle, rotation, false);
    }

    // RSL logic
    if (millis() - lastTimePacketReceived > 1000) {
        RSL::setState(RSL_DISABLED);
    }
    else {
        RSL::setState(RSL_ENABLED);
    }
    RSL::update();
}