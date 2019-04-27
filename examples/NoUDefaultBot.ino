// NoUDefaultBot.ino (v0.1)

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
    drive(xAxis, yAxis);
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
void drive(int xAxis, int yAxis) {
    float V = ((1 - abs(xAxis)) * yAxis) + yAxis;  // This is where the X and Y axis inputs are converted into tank drive logic
    float W = ((1 - abs(yAxis)) * xAxis) + xAxis;
    float leftPower = (((V - W) / 2)) * 1023;
    float rightPower = (((V + W) / 2)) * 1023;

    //Serial.print(leftPower);
    //Serial.print("   ");
    //Serial.println(rightPower);

    frontLeftMotor.set(leftPower);
    frontRightMotor.set(rightPower);
    rearLeftMotor.set(leftPower);
    rearRightMotor.set(rightPower);
}