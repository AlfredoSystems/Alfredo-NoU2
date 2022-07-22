Robot Programming with AlfredoConnect-Receive
=============================================

This tutorial will guide you through programming, uploading, and driving a robot using `Alfredo-NoU2`_ and `AlfredoConnect-Receive`_. A Windows computer is necessary to run `AlfredoConnect`_, so this guide assumes you are on a Windows machine.

Setup
-----

1. **Get the Arduino IDE.** This lets us write and upload programs to our robot. Download it from the `Arduino website <https://www.arduino.cc/en/main/software>`_ and install it.

2. **Get copies of the `Alfredo-NoU2`_ and `AlfredoConnect-Receive`_ libraries.** Go to their GitHub pages and click the green button that says **Code**, then **Download ZIP**.

3. **Add those libraries to the Arduino IDE.** In the Arduino IDE, click **Sketch** > **Include Library** > **Add .ZIP Library...**, and select the two ZIP files you downloaded.

4. **Configure the Arduino IDE to upload to an ESP32.** In the Arduino IDE, click **File** > **Preferences**. Paste the following in the **Additional Boards Manager URLs** field.

::

    https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
    
Then, go to **Tools** > **Board** > **Boards Manager**. Search for "ESP32" and install the package "esp32 by Espressif Systems".

5. **Install AlfredoConnect.** We've already prepared AlfredoConnect-Receive, the library we'll use on the robot to get input from the computer. Now we need to get AlfredoConnect-Desktop, the Windows application that lets us talk to the robot. Download and install its latest release `here <AlfredoConnect>`_.

Basics
------

We're going to start by writing a simple program to test using AlfredoConnect to control any motors or servos connected to your NoU2 via the ESP32's Bluetooth.

.. note:: For this section, you'll at least need an ESP32 on an Alfredo NoU2 ready to drive some motors. Follow our Electronics Tutorial to set that up before continuing here.
   
.. seealso:: If you just need an example program to test motor and servo movement without an explanation, use the `motor party <https://github.com/AlfredoSystems/Alfredo-NoU2/blob/master/examples/NoU2MotorParty/NoU2MotorParty.ino>`_ example sketch included with Alfredo-NoU2.
   
When you open up the Arduino IDE, you'll see an empty program (a "sketch") that looks like this:

.. code-block:: cpp

    void setup() {

    }

    void loop() {

    }

These are two **functions**, or chunks of code. When your program runs on an ESP32, the ``setup`` function runs once when the program starts, then the ``loop`` function runs repeatedly. Right now, they're empty, but we'll add some code to them soon.

Before that, we need to make some changes at the start of the sketch, before the functions. First, we need to specify that we want to use the libraries we installed earlier, Alfredo-NoU2 and AlfredoConnect-Receive. To do that, add the following lines to the top of the file.

.. code-block:: cpp

    #include <Alfredo_NoU2.h>
    #include <AlfredoConnect.h>
    #include <BluetoothSerial.h>
   
Each of these statements reference some code from a separate file that you want to have included in your final program. The first two, **Alfredo_NoU2.h** and **AlfredoConnect.h** are files in the libraries you installed earlier in the :ref:`Setup` section. **BluetoothSerial.h** is part of a built-in library for using the ESP32's Bluetooth capability.

Next, we'll declare the motors and servos we want to use.

.. code-block:: cpp

    NoU_Motor leftMotor(2);
    NoU_Servo armServo(3);

In the first line here, we say that there's a ``NoU_Motor`` called ``leftMotor`` assigned to motor port 2. You can check which motor port your motor is plugged into by checking for the little labels where the wires plug in. For example, motor port 2 has labels that say **M2-** and **M2+** on the NoU2. Similarly, in the second line, we construct an object called ``armServo`` of type ``NoU_Servo`` on servo port 3. The servo pins on the NoU2 are labeled **S1**, **S2**, and so on.

.. note:: ``NoU_Motor`` is a **class** defined in the Alfredo-NoU2 library. A class is like a template that can be used to make an **object**, a specific instance of a class. In this case, the name we give to the specific instance of a ``NoU_Motor`` we're creating is ``leftMotor``, but we're allowed to call it whatever we want (like ``rightMotor``, ``m``, or ``john``). Lastly, we put a 2 in parentheses at the end to say we want motor port 2. 

Your setup is likely not just one motor and one servo, so make sure you have one line for each motor and/or servo. Make sure each one has a different name and the correct motor or servo port number.

Next, we need to declare an object to help us use the ESP32's Bluetooth.

.. code-block:: cpp

    BluetoothSerial bluetooth;

Altogether, our code so far looks something like this (with different motors and servos based on your setup):

.. code-block:: cpp

    #include <Alfredo_NoU2.h>
    #include <AlfredoConnect.h>
    #include <BluetoothSerial.h>

    NoU_Motor leftMotor(2);
    NoU_Servo armServo(3);
    BluetoothSerial bluetooth;
    
    void setup() {

    }

    void loop() {

    }

Now, we're going to start adding code to the ``setup`` function. This code will run as soon as the program starts. Pretty much any time the ESP32 is on, the last program you uploaded to it will be running. You can restart the program by either cycling power to the ESP32 or by clicking the little **EN** button near the USB port to reset it. We'll start by enabling Bluetooth.

.. code-block:: cpp

    void setup() {
        bluetooth.begin("Name me!"); // Change this name before uploading! Also, this is a code comment.
    }

This will cause the ESP32 to start advertising itself as a Bluetooth peripheral when it's on. Make sure to give it a unique name or it'll conflict with the Bluetooth name of anyone else who followed this tutorial.
   
.. warning:: Make sure to change the Bluetooth name of the ESP32 before continuing! If you decide to change it later, after the ESP32 has already Bluetooth paired with your computer, you may need to restart your computer to pair with the ESP32 under the new name.
   
.. note:: It's standard to add a level of indentation any time you enter a set of curly braces, like inside of a function. It doesn't affect the program, but it makes it easier to read.

Next, let's set up AlfredoConnect. Add the following code to the ``setup`` function.

.. code-block:: cpp

    AlfredoConnect.begin(bluetooth);
    bluetooth.println("Starting motor and servo test program.");

This lets the AlfredoConnect-Receive library know that it can expect to receive communication from AlfredoConnect over Bluetooth. Then, we use ``bluetooth.println`` to send a message over Bluetooth to the computer. This message will appear in your AlfredoConnect window when you connect to the robot later.

.. note:: Using ``bluetooth.println`` yourself is a great way to follow the flow of the code when things get confusing. For example, if you put ``bluetooth.println("Looping...")`` in the ``loop`` function, it would display that message in AlfredoConnect over and over.

Now, we'll add code to the ``loop`` function to control our motors.

.. code-block:: cpp

    void loop() {
        if (AlfredoConnect.keyHeld(Key::Q)) {
            leftMotor.set(1);
        }
        else {
            leftMotor.set(0);
        }
    }

This code will make ``leftMotor`` move while the **Q** key is held on AlfredoConnect and stop when it's not held. Don't forget that your motors may be called something different and you may have more than one, so change the name and duplicate as needed.

.. note:: How did we know to set ``leftMotor`` to 1 to start it and 0 to turn it off? You can look at the `API Reference <api_reference.html>`_ to see specific details about all the functions in Alfredo-NoU2. Specifically, the :cpp:func:`NoU_Motor::set` function takes a number between -1 (full reverse) and 1 (full forward), including decimal numbers.
   
.. note:: AlfredoConnect lets you use most keys on your keyboard to control things on your robot. You can see a full list of the supported keys `here <https://github.com/AlfredoSystems/AlfredoConnect-Receive/blob/master/Keys.h>`_. For example, in the above code, you can replace ``Key::Q`` with ``Key::Comma`` or ``Key::Backspace``.

Now, let's do something similar for our servos. Add the following code to the ``loop`` function for each servo you have.

.. code-block:: cpp

    if (AlfredoConnect.keyHeld(Key::W)) {
        armServo.write(180);
    }
    else {
        armServo.write(0);
    }
   
This will make ``armServo`` move to its 180° position while the **W** key is held and move back to its 0° position while it's released. Again, change the name and duplicate as needed for the servos in your setup.
   
Lastly, add this line to the end of your ``loop`` function to let AlfredoConnect-Receive process any new input coming in from your computer.

.. code-block:: cpp

    AlfredoConnect.update();
   
That should complete our test sketch. Here's what the final code should look like (but with the number of motors and servos adapted for your setup):
   
.. code-block:: cpp

    #include <Alfredo_NoU2.h>
    #include <AlfredoConnect.h>
    #include <BluetoothSerial.h>

    NoU_Motor leftMotor(2);
    NoU_Servo armServo(3);
    BluetoothSerial bluetooth;
    
    void setup() {
        bluetooth.begin("Name me!"); // Change this name before uploading!
        AlfredoConnect.begin(bluetooth);
        bluetooth.println("Starting motor and servo test program.");
    }

    void loop() {
        if (AlfredoConnect.keyHeld(Key::Q)) {
            leftMotor.set(1);
        }
        else {
            leftMotor.set(0);
        }

        if (AlfredoConnect.keyHeld(Key::W)) {
            armServo.write(180);
        }
        else {
            armServo.write(0);
        }

        AlfredoConnect.update();
    }
    
Uploading
*********
Now we need to upload our sketch to the robot.

1. **Select the ESP32 board.** Go to **Tools** > **Board** and select **ESP32 Dev Module** from the long list.
2. **Select the COM port.** Connect the ESP32 to your computer using a micro-USB cable and select the new COM port that appears under **Tools** > **Port**. The correct COM port may say (Silicon Labs) next to it. If none of them do, you can unplug and replug the USB to see which COM port disappears and reappears.
3. **Upload.** Clicking the **Upload** button (the arrow in the top left pointing right). If the console on the bottom of the window starts showing the text ``Connecting....._____.....``, hold down the **BOOT** button on the ESP32.
   
Bluetooth Pairing
*****************
Now that we've uploaded that sketch, the ESP32 will advertise itself as a Bluetooth device as long as it's on. We need to pair it to your computer so you can control the robot from AlfredoConnect. The following instructions are specifically for Windows 10. The procedure will be similar but not the same for other versions of Windows.

1. **Pair with the ESP32.** Go to **Devices** > **Bluetooth & other devices** > **Add Bluetooth or other device** > **Bluetooth**. If the ESP32 is powered and running the sketch we just uploaded, the name you assigned it should appear. Pair with it. It typically doesn't ask for a passcode, but if it does, the default is usually **1234**.

2. **Find the Bluetooth COM port of the ESP32.** Bluetooth pairing with the ESP32 has created a new COM port on your machine for communicating with the ESP32 over Bluetooth. To find it, in the **Bluetooth & other devices** settings page, click **More Bluetooth options** on the right panel. Go to the **COM Ports** tab. There should be two entries with the name you gave your ESP32. Find the one with the direction "Outgoing" and remember the **Port** field.

3. **Connect with AlfredoConnect.** Open AlfredoConnect on your computer and click the **Serial port** dropdown. One of the entries should be the port we noted in step 2. Select it and click **Open**.

You should now be connected to your robot in AlfredoConnect via Bluetooth. Press the keys you assigned (this tutorial used the Q and W keys) and the motors and servos you have connected to your robot should move.
    
Robot Programming
-----------------

Now, we'll adapt the sketch from the previous section to drive a robot. We'll assume the robot is the one from the Fabrication and Electrical tutorials, so it has a servo to raise and lower a basket and a drivetrain with two motors (technically, four motors using only two motor ports).

First, we'll change our list of motors and servos to match our robot.

.. code-block:: cpp

    NoU_Motor leftMotor(1);
    NoU_Motor rightMotor(2);
    NoU_Servo basketServo(1);
    
Now, we'll create a ``NoU_Drivetrain`` with our two motors. We'll use this to move the drivetrain motors as a group instead of individually setting the power that goes to each one.

.. code-block:: cpp

    NoU_Drivetrain drivetrain(&leftMotor, &rightMotor);
   
Next, we'll change the ``loop`` function to make the robot drive. This will be different depending on whether you want to control your robot with a keyboard or a gamepad.
   
Keyboard
********

We'll use the WASD keys to drive the robot in this tutorial, but you can use whatever keys you want (key names defined `here <https://github.com/AlfredoSystems/AlfredoConnect-Receive/blob/master/Keys.h>`_). The W and S keys will control the throttle of the robot, while the A and D keys will control the rotation.

.. code-block:: cpp

    void loop() {
        float throttle = 0;
        float rotation = 0;
        
        // Set the throttle of the robot based on what key is pressed
        if (AlfredoConnect.keyHeld(Key::W)) {
            throttle = 1;
        }
        else if (AlfredoConnect.keyHeld(Key::S)) {
            throttle = -1;
        }
        
        // Set which direction the robot should turn based on what key is pressed
        if (AlfredoConnect.keyHeld(Key::A)) {
            rotation = -1;
        }
        else if (AlfredoConnect.keyHeld(Key::D)) {
            rotation = 1;
        }
        
        // Make the robot drive
        drivetrain.curvatureDrive(throttle, rotation);

        AlfredoConnect.update();
    }
    
Lastly, we'll make our servo move when we press the F key.
    
.. code-block:: cpp

    if (AlfredoConnect.keyHeld(Key::F)) {
        basketServo.write(180);
    }
    else {
        basketServo.write(0);
    }
    
Our completed sketch will now let us drive the robot with WASD and move the servo with the F key. Upload it to the ESP32, power on your robot, and connect to it with AlfredoConnect on your computer.

.. code-block:: cpp

    #include <Alfredo_NoU2.h>
    #include <AlfredoConnect.h>
    #include <BluetoothSerial.h>

    NoU_Motor leftMotor(1);
    NoU_Motor rightMotor(2);
    NoU_Servo basketServo(1);
    BluetoothSerial bluetooth;
    
    void setup() {
        bluetooth.begin("Name me!"); // Change this name before uploading!
        AlfredoConnect.begin(bluetooth);
        bluetooth.println("Starting robot.");
    }

    void loop() {
        float throttle = 0;
        float rotation = 0;
        
        // Set the throttle of the robot based on what key is pressed
        if (AlfredoConnect.keyHeld(Key::W)) {
            throttle = 1;
        }
        else if (AlfredoConnect.keyHeld(Key::S)) {
            throttle = -1;
        }
        
        // Set which direction the robot should turn based on what key is pressed
        if (AlfredoConnect.keyHeld(Key::A)) {
            rotation = -1;
        }
        else if (AlfredoConnect.keyHeld(Key::D)) {
            rotation = 1;
        }
        
        // Make the robot drive
        drivetrain.curvatureDrive(throttle, rotation);

        // Control the servo
        if (AlfredoConnect.keyHeld(Key::F)) {
            basketServo.write(180);
        }
        else {
            basketServo.write(0);
        }

        AlfredoConnect.update();
    }

.. _Alfredo-NoU2: https://github.com/AlfredoSystems/Alfredo-NoU2
.. _AlfredoConnect-Receive: https://github.com/AlfredoSystems/AlfredoConnect-Receive
.. _AlfredoConnect: https://github.com/AlfredoSystems/AlfredoConnect-Desktop/releases/latest