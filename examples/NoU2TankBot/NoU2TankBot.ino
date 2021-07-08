/**
 * This example is for the legacy MiniFRC driver station, found here:
 * https://github.com/ddthj/MiniFRC. To use the AlfredoConnect driver station, check
 * out AlfredoConnect-Receive, which includes examples for the Alfredo NoU2:
 * https://github.com/AlfredoElectronics/AlfredoConnect-Receive.
 */

#include <BluetoothSerial.h>
#include <Alfredo_NoU2.h>

BluetoothSerial bluetooth;

NoU_Motor frontLeftMotor(1);
NoU_Motor frontRightMotor(2);
NoU_Motor rearLeftMotor(3);
NoU_Motor rearRightMotor(4);
NoU_Servo servo(1);

NoU_Drivetrain drivetrain(&frontLeftMotor, &frontRightMotor, &rearLeftMotor, &rearRightMotor);

float leftThrottle, rightThrottle, servoAxis;
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
            leftThrottle = -bluetooth.parseFloat();
            rightThrottle = -bluetooth.parseFloat();
            servoAxis = bluetooth.parseFloat();
        }
    }
    servo.write((servoAxis + 1) * 90);
    drivetrain.tankDrive(leftThrottle, rightThrottle);

    // RSL logic
    if (millis() - lastTimePacketReceived > 1000) {
        RSL::setState(RSL_DISABLED);
    }
    else {
        RSL::setState(RSL_ENABLED);
    }
    RSL::update();
}