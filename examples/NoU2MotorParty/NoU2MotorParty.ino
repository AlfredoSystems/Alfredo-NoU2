#include <Alfredo_NoU2.h>

NoU_Motor motor1(1);
NoU_Motor motor2(2);
NoU_Motor motor3(3);
NoU_Motor motor4(4);
NoU_Motor motor5(5);
NoU_Motor motor6(6);
NoU_Servo servo1(1);
NoU_Servo servo2(2);
NoU_Servo servo3(3);
NoU_Servo servo4(4);

void setup() {
    Serial.begin(9600);
    RSL::initialize();
    RSL::setState(RSL_ENABLED);
}

void loop() {
    for (float i = -1023; i < 1023; i += 1) {
        motor1.set(i / 1023.0);
        motor2.set(i / 1023.0);
        motor3.set(i / 1023.0);
        motor4.set(i / 1023.0);
        motor5.set(i / 1023.0);
        motor6.set(i / 1023.0);
        servo1.write(map(i, -1023, 1023, 0, 180));
        servo2.write(map(i, -1023, 1023, 0, 180));
        servo3.write(map(i, -1023, 1023, 0, 180));
        servo4.write(map(i, -1023, 1023, 0, 180));
        RSL::update();
        delay(1);
    }
    for (float i = 1023; i > -1023; i -= 1) {
        motor1.set(i / 1023.0);
        motor2.set(i / 1023.0);
        motor3.set(i / 1023.0);
        motor4.set(i / 1023.0);
        motor5.set(i / 1023.0);
        motor6.set(i / 1023.0);
        servo1.write(map(i, -1023, 1023, 0, 180));
        servo2.write(map(i, -1023, 1023, 0, 180));
        servo3.write(map(i, -1023, 1023, 0, 180));
        servo4.write(map(i, -1023, 1023, 0, 180));
        RSL::update();
        delay(1);
    }
}