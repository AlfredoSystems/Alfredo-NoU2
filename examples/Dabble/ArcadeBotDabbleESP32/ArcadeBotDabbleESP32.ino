/**
 * Example code for a robot using an ESP32 and NoU2 controlled with the Dabble app.
 * The NoU2 library can be found at https://github.com/AlfredoElectronics/Alfredo-NoU2.
 * 
 * Dabble is avalible on IOS https://apps.apple.com/us/app/dabble-bluetooth-controller/id1472734455
 * and Android https://play.google.com/store/apps/details?id=io.dabbleapp&hl=en_AU&gl=US
 */

#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <DabbleESP32.h>
#include <Alfredo_NoU2.h>

// If your robot has more than a drivetrain and one servo, add those actuators here 
NoU_Motor frontLeftMotor(1);
NoU_Motor frontRightMotor(2);
NoU_Motor rearLeftMotor(3);
NoU_Motor rearRightMotor(4);
NoU_Servo servo(1);

// This creates the drivetrain object, you shouldn't have to mess with this
NoU_Drivetrain drivetrain(&frontLeftMotor, &frontRightMotor, &rearLeftMotor, &rearRightMotor);

void setup() {
//EVERYONE SHOULD CHANGE "ESP32-Bluetooth" TO THE NAME OF THEIR ROBOT HERE BEFORE PAIRING THEIR ROBOT TO ANY LAPTOP
    Dabble.begin("ESP32-Bluetooth");       //set bluetooth name of your device
    Serial.begin(115200);
// If a motor in your drivetrain is spinning the wrong way, change the value for it here from 'false' to 'true'
    frontLeftMotor.setInverted(false);
    frontRightMotor.setInverted(true);
    rearLeftMotor.setInverted(false);
    rearRightMotor.setInverted(true);

// No need to mess with this code
    RSL::initialize();
    RSL::setState(RSL_ENABLED);
}

void loop() {
// Here we define the variables we use in the loop
    int throttle = 0;
    int rotation = 0;
    int servoAngle = 0;

// Here we decide what the throttle and rotation direction will be based on gamepad inputs   
    if (Dabble.isAppConnected()) {
        float throttle = scaleDabbleYaxis(GamePad.getYaxisData());
        float rotation = scaleDabbleXaxis(GamePad.getXaxisData());
        Serial.print(throttle);
        Serial.print(" ");
        Serial.println(rotation);

        drivetrain.arcadeDrive(throttle, rotation);

        RSL::setState(RSL_ENABLED);
    } else {
        RSL::setState(RSL_DISABLED);
    }

// functions you can call to get controller state from your phone
// GamePad.isUpPressed()
// GamePad.isDownPressed()
// GamePad.isLeftPressed()
// GamePad.isRightPressed()
// GamePad.isSquarePressed()
// GamePad.isCirclePressed()
// GamePad.isCrossPressed()
// GamePad.isTrianglePressed()
// GamePad.isStartPressed()
// GamePad.isSelectPressed()

// Here we decide what the servo angle will be based on if the circle button is pressed
    if (GamePad.isCirclePressed()) {
        servoAngle = 50;
    }
    else {
        servoAngle = 140;
    }

// Here we set the servo angle based on what we found in the above code
    servo.write(servoAngle);

// No need to mess with this code
    Dabble.processInput(); 
    RSL::update();
}

//Dabble axis values are weird, these helper funtions scale them to be useful to the NoU2 library
float scaleDabbleYaxis(float y_in) {
  return (0 < y_in) ? (y_in/7) : (y_in/6);
}

float scaleDabbleXaxis(float x_in) {
  return (0 < x_in) ? (x_in/6) : (x_in/7);
}
