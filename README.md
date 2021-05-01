# Alfredo-NoU2
_Library version 2.0.1_

<img src="https://github.com/AlfredoElectronics/alfredoelectronics.github.io/blob/master/images/nou2-1.png" width="400px">

Library for the Alfredo NoU v2.6. Supports motors and servos and has helper methods for different drivetrain types.

## Getting started

This tutorial should help you set up a Windows computer to control a robot that uses an ESP32 and Alfredo NoU2 control system. This setup has been done on Mac before, but a lot of this tutorial won't apply, and it's not recommended unless you really know what you're doing. This tutorial uses the [Arduino IDE](https://www.arduino.cc/en/main/software). You'll need to download and install it if you don't already have it.

1. Firstly, we'll need to configure the Arduino IDE to upload to an ESP32. Check out [this board configuration tutorial](https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/) for instructions on how to do that.

2. Download this repository as a ZIP by clicking the green button on the right that says **Clone or download**, then **Download ZIP**.

3. In the Arduino IDE, add this repository as a library by clicking **Sketch** > **Include Library** > **Add .ZIP Library...**, and selecting the ZIP file you downloaded.

4. Make sure you've selected the right COM port and board (following the [board configuration tutorial](https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/) above) and upload one of the files in the `examples` folder to an ESP32 mounted on a NoU2. A good first test that doesn't require Bluetooth or the Driver Station is `NoU2MotorParty.ino`, which pulses all the connected motors and servos.

5. Once you've tested out the motor party code, open up the code for a robot, like any of the sketches in `examples` that end with "Bot". Before you upload to your ESP32, edit the code make sure to configure the name that the Bluetooth connection will appear as when pairing with the ESP32. In the examples, the default name is "DefaultBot", and you should change it to your own name by editing the line `bluetooth.begin("DefaultBot")` to something like `bluetooth.begin("My Cool Robot")`. Now's a good time to do this because, if you wait until later to change it, you'll have to restart your computer to be able to pair with the ESP32 under the new name.

6. To start driving your robot, either with your own code or one of the robot examples, start by pairing a computer with the ESP32 over Bluetooth. On Windows 10, you can pair with a Bluetooth device by going to your **Bluetooth & other devices** settings page > **Add Bluetooth or other device** > **Bluetooth**. All of the robot examples have the ESP32 advertise its Bluetooth connection as "DefaultBot", although you should have changed it in step 4 to your own name. It shouldn't ask for a passcode to pair, but if it does, the default is typically "1234".

7. Once you've paired a computer and the ESP32, you'll need to find out what COM port you need to use to send information to the ESP32 from the computer. On Windows 10, open up your Bluetooth settings (the "Bluetooth & other devices" page) and click "More Bluetooth options" in the "Related settings" on the right. Click on the "COM Ports" tab and you should see a pair of COM ports, both with the same name as the Bluetooth device you paired with ("DefaultBot" for the examples). Note the number of the port with the Direction "Outgoing". This is the COM port we'll use to send information to the robot.

8. Download the [MiniFRC Driver Station](https://github.com/ddthj/MiniFRC). If you're using a robot example from this repository, swap in the `config.txt` file from the example folder. In the `config.txt` file, you'll need to change the COM port to the one you found earlier. You can look at the comments in the original [`config.txt`](https://github.com/ddthj/MiniFRC/blob/master/config.txt) file in the Driver Station repository for instructions on how to modify axes, add buttons, and receive input from connected joysticks or game controllers.

9. Boot up the Driver Station (using the [`DriverStation.exe`](https://github.com/ddthj/MiniFRC/blob/master/DriverStation.exe) file). The Driver Station should connect to the robot, and you should be able to control it using the keybinds assigned in the `config.txt` file.

## Troubleshooting

If the Driver Station doesn't connect to the robot:
* Make sure the ESP32 is on.
* Make sure a program that broadcasts Bluetooth is uploaded to the ESP32. All the examples in this repository that end with "Bot" broadcast Bluetooth.
* Make sure the computer is paired with the ESP32 over Bluetooth.
* In the same folder as the `DriverStation.exe` file you opened to start the Driver Station, there should be a file called `config.txt`. Make sure the line that says `COM = <port>`, where <port> is a  Change this to the same COM port as you found in step 7s. If the COM port was COM6, you would edit the line to say `COM = COM6`.

If the Driver Station connects to the robot but the robot won't move:
* Make sure the line `BAUD = <number>` in the `config.txt` file matches the baud rate you've configured for your robot. By default, the examples are configured for 9600. If you're not sure what the baud rate set by your code is, it's probably 9600. For a baud rate of 9600, this line would say `BAUD = 9600`.
* Make sure your motors are connected to the same motor port as indicated in the code. The line `NoU_Motor frontLeftMotor(1);` says that there's a motor named `frontLeftMotor` on port 1, so you should make sure a motor is plugged into the terminals labelled M1- and M1+ on the NoU2.
* Check your `config.txt` file to make sure that you're assigning axes and buttons as you expect. The original [`config.txt`](https://github.com/ddthj/MiniFRC/blob/master/config.txt) file from the Driver Station repository has examples of how this is done. You should see the rendered axes and buttons on the Driver Station change when you move the axes or press buttons. You can test out buttons and axes without a robot by changing your COM port assignment in your `config.txt` file to say `COM = test`.

If Driver Station connects and the robot moves, but doesn't move as you expect:
* Make sure the order you assign buttons and axes corresponds to the order you read them in your code.
* If one of your motors always runs in reverse, you can set it as inverted in the code by calling `motor.setInverted(true)` in your `setup` function. The robot examples demonstrate this.

Most importantly, when you can't figure something out, ask for help! No one is born good at this stuff, and it takes some time to learn. Take your time to compose a question along with all the relevant information that might help others figure out your problem. MiniFRC participants, asking your question in the [MiniFRC Discord](https://discord.gg/VtGvf6B) is a great way to both get your question answered and meet lots of cool people eager to help you out. We're on the Discord to help out anyone with questions, but opening an issue on our [Issue Tracker](https://github.com/AlfredoElectronics/Alfredo-NoU-2/issues) with the "help wanted" or "question" labels is another good way to bring attention to a well-documented, persistent, or common problem, along with any solutions or workarounds people have found.
