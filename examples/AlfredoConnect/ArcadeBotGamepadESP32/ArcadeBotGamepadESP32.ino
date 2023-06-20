/**
 * Example code for a robot using an ESP32 and NoU2 controlled with a gamepad from AlfredoConnect.
 * The NoU2 library can be found at https://github.com/AlfredoElectronics/Alfredo-NoU2.
 *
 * Detailed instructions can be found at https://github.com/AlfredoElectronics/AlfredoConnect-Receive/.
 */

#include <AlfredoConnect.h>
#include <BluetoothSerial.h>
#include <Alfredo_NoU2.h>

BluetoothSerial bluetooth;

// If your robot has more than a drivetrain and one servo, add those actuators here 
NoU_Motor frontLeftMotor(1);
NoU_Motor frontRightMotor(2);
NoU_Motor rearLeftMotor(3);
NoU_Motor rearRightMotor(4);
NoU_Servo servo(1);

// This creates the drivetrain object, you shouldn't have to mess with this
NoU_Drivetrain drivetrain(&frontLeftMotor, &frontRightMotor, &rearLeftMotor, &rearRightMotor);

void setup() {
//EVERYONE SHOULD CHANGE "ESP32 Bluetooth" TO THE NAME OF THEIR ROBOT HERE BEFORE PAIRING THEIR ROBOT TO ANY LAPTOP
    bluetooth.begin("ESP32 Bluetooth");
    AlfredoConnect.begin(bluetooth);
    bluetooth.println("ArcadeBotGamepad started");

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
    if (AlfredoConnect.getGamepadCount() >= 1) {
        float throttle = -AlfredoConnect.getAxis(0, 1);
        float rotation = AlfredoConnect.getAxis(0, 0);
        
        drivetrain.arcadeDrive(throttle, rotation);

        RSL::setState(RSL_ENABLED);
    } else {
        RSL::setState(RSL_DISABLED);
    }

// Here we decide what the servo angle will be based on if the Q key is pressed ()
    if (AlfredoConnect.keyHeld(Key::Q)) {
        servoAngle = 50;
    }
    else {
        servoAngle = 110;
    }

// Here we set the drivetrain motor speeds and servo angle based on what we found in the above code
    servo.write(servoAngle);

// No need to mess with this code
    AlfredoConnect.update();
    RSL::update();
}
