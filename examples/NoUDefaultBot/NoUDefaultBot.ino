#include <BluetoothSerial.h>
#include <Alfredo_NoU.h>

BluetoothSerial ESP_BT;

NoU_Motor frontLeftMotor(1);
NoU_Motor frontRightMotor(2);
NoU_Motor rearLeftMotor(3);
NoU_Motor rearRightMotor(4);
NoU_Servo servo(16);

float xAxis, yAxis, servoAxis;
long lastTimePacketReceived = 0;

void setup() {
    Serial.begin(9600);
    RSL::initialize();
    ESP_BT.begin("DefaultBot");
}

void loop() {
    while (ESP_BT.available() > 0) {
        lastTimePacketReceived = millis();
        if ((ESP_BT.read()) == 'z') {
            xAxis = ESP_BT.parseFloat();
            yAxis = ESP_BT.parseFloat();
            servoAxis = ESP_BT.parseFloat();
        }
    }
    drive(yAxis, xAxis);
    servo.write((servoAxis + 1) * 90);

    // RSL logic
    if (millis() - lastTimePacketReceived > 1000) {
        RSL::setState(RSL_DISABLED);
    }
    else {
        RSL::setState(RSL_ENABLED);
    }
    RSL::update();
}

// Inputs are from -1...1
void drive(float throttle, float rotation) {
    throttle = constrain(throttle, -1, 1);
    rotation = constrain(rotation, -1, 1);
    float leftPower;
    float rightPower;
    float maxInput = (throttle > 0 ? 1 : -1) * max(abs(throttle), abs(rotation));
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
            leftPower = throttle + rotation;
            rightPower = maxInput;
        }
        else {
            leftPower = maxInput;
            rightPower = throttle - rotation;
        }
    }
    frontLeftMotor.set(constrain(leftPower, -1, 1));
    frontRightMotor.set(constrain(rightPower, -1, 1));
    rearLeftMotor.set(constrain(leftPower, -1, 1));
    rearRightMotor.set(constrain(rightPower, -1, 1));
}