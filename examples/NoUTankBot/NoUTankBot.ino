#include <BluetoothSerial.h>
#include <Alfredo_NoU.h>

BluetoothSerial ESP_BT;

NoU_Motor frontLeftMotor(1);
NoU_Motor frontRightMotor(2);
NoU_Motor rearLeftMotor(3);
NoU_Motor rearRightMotor(4);
NoU_Servo servo(16);

NoU_Drivetrain drivetrain(&frontLeftMotor, &frontRightMotor, &rearLeftMotor, &rearRightMotor);

float leftThrottle, rightThrottle, servoAxis;
long lastTimePacketReceived = 0;

void setup() {
    Serial.begin(9600);
    RSL::initialize();
    ESP_BT.begin("DefaultBot");
    frontLeftMotor.setInverted(false);
    frontRightMotor.setInverted(false);
    rearLeftMotor.setInverted(false);
    rearRightMotor.setInverted(false);
}

void loop() {
    while (ESP_BT.available() > 0) {
        lastTimePacketReceived = millis();
        if ((ESP_BT.read()) == 'z') {
            leftThrottle = -ESP_BT.parseFloat();
            rightThrottle = -ESP_BT.parseFloat();
            servoAxis = ESP_BT.parseFloat();
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