# Alfredo-NoU2
_Library version 2.0.2_

<img src="https://github.com/AlfredoElectronics/alfredoelectronics.github.io/blob/master/images/nou2-1.png" width="400px">

Library for the Alfredo NoU v2.6. Supports motors and servos and has helper methods for different drivetrain types.

## Getting started

### Basic setup

This tutorial will guide you through uploading example code to your ESP32 with an attached Alfredo NoU2. This should work on any OS.

1. **Get the Arduino IDE**. If you don't already have it, download it from the [Arduino website](https://www.arduino.cc/en/main/software) and install it.

2. **Configure the Arduino IDE to upload to an ESP32.** Check out [this board configuration tutorial](https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/) for instructions on how to do that.

3. **Download this repository as a ZIP**. Click [here](https://github.com/AlfredoElectronics/Alfredo-NoU2/archive/refs/heads/master.zip) to start the download, or click the green button on this page that says `Code`, then `Download ZIP`.

4. **Add this library to the Arduino IDE**. In the Arduino IDE, Click `Sketch` > `Include Library` > `Add .ZIP Library...`, and select the ZIP file you downloaded.

5. **Open the `NoU2MotorParty` example**. In the Arduino IDE, go to `File` > `Examples` > `Alfredo-NoU2-master` (you might need to scroll down) and select `NoU2MotorParty`. This will open a new window with the example opened. You can close the old one.

6. **Connect your ESP32 and select the COM port**. Connect your ESP32 to your computer using a micro USB cable. In the Arduino IDE, select the corresponding COM port under `Tools` > `Port`. The correct COM port may say `(Silicon Labs)` next to it. If none of them do, you can unplug and replug the USB to see which COM port disappears and reappears. If you cannot find any COM port for the ESP32, try the [troubleshooting steps](#cant-connect-to-the-esp32-over-usb-to-upload).

7. **Select ESP32 as the board type**. In the Arduino IDE, go to `Tools` > `Board` > `ESP32 Arduino` and select `ESP32 Dev Module`. On older versions of Arduino, it may just be `Tools` > `Board` > `ESP32 Dev Module`.

8. **Upload `NoU2MotorParty` to your ESP32**. In the window with `NoU2MotorParty` opened, click the upload button (the arrow in the top left). If the console on the bottom of the window starts showing `Connecting....._____.....`, hold down the `BOOT` button on the ESP32.

Once the top of the console says `Done uploading.`, the example is on the ESP32 and you can unplug it from the computer. When connected to an Alfredo NoU2, the `NoU2MotorParty` example will pulse any connected motors and servos back and forth.

### Driving a robot

[AlfredoConnect](https://github.com/AlfredoElectronics/AlfredoConnect-Desktop/releases) is a driver station that runs on Windows for controlling robots over Bluetooth using your computer's keyboard or connected gamepads. It has a corresponding Arduino library, [AlfredoConnect-Receive](https://github.com/AlfredoElectronics/AlfredoConnect-Receive), which contains examples for using AlfredoConnect with the Alfredo NoU2. After following the [basic setup tutorial](#basic-setup) here, follow the [getting started tutorials for AlfredoConnect-Receive](https://github.com/AlfredoElectronics/AlfredoConnect-Receive#getting-started) to learn how to control your robot using AlfredoConnect.

## Troubleshooting

### Can't connect to the ESP32 over USB to upload
* The most common cause of this is accidentally using a power-only micro USB cable, which won't allow the computer and ESP32 to communicate, but will power on the ESP32. Try a new cable. When plugging in the ESP32, you should hear a sound on the computer indicating it's plugged in.
* Make sure you're selecting the right COM port. The most common way to check is to unplug the ESP32, check the ports list in the Arduino IDE, (`Tools` > `Port`), plug the ESP32 in, and then check the list again to see what COM port got added. On Windows, you can also open Device Manager (`Win+R`, type in `devmgmt.msc`) and check the `Ports (COM & LPT)` dropdown, which should include a port list similar to the one in the Arduino IDE.
* You may need to install appropriate drivers for [CP210x](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers) or [FTDI](https://ftdichip.com/drivers/vcp-drivers/), depending on your ESP32 module type. If unsure, get both.

## Links

* [**Product Page**](https://alfredoelectronics.github.io/products/alfredo-nou2/): Purchase an Alfredo NoU2 here.
* [**MiniFRC Discord**](https://discord.gg/VtGvf6B): This is the best place to get quick help with the Alfredo NoU2 and this library from both users and the Alfredo Electronics team.
* [**Issue Tracker**](https://github.com/AlfredoElectronics/Alfredo-NoU-2/issues): If you're having a problem or need guidance, feel free to open an issue with the `help wanted` or `question` label.
