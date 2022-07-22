NoU_Drivetrain
===============

.. cpp:class:: NoU_Drivetrain

    Controls the output of a two- or four-motor drivetrain.

    **Public Functions**

    .. cpp:function:: NoU_Drivetrain(:cpp:class:`NoU_Motor`* leftMotor, :cpp:class:`NoU_Motor`* rightMotor)

        Constructs a new :cpp:class:`NoU_Drivetrain` using the specified two motors.

        :param :cpp:class:`NoU_Motor`* leftMotor: The motor on the left side of the drive train.
        :param :cpp:class:`NoU_Motor`* rightMotor: The motor on the right side of the drive train.

        **Example usage:**

        ::

            NoU_Motor leftMotor(1);
            NoU_Motor rightMotor(2);
            NoU_Drivetrain drivetrain(&leftMotor, &rightMotor);

        Constructs a new drivetrain with the left motor on motor port 1 and the right motor on motor port 2.
        
        .. note:: Robot builders often wire the two motors on each side of the drivetrain into the same terminal block in parallel, using two motor ports for a four-motor drivetrain. In this case, this constructor should be used, not the four-motor constructor, :cpp:function:`NoU_Drivetrain(:cpp:class:`NoU_Motor`, :cpp:class:`NoU_Motor`, :cpp:class:`NoU_Motor`, :cpp:class:`NoU_Motor`)`.

    .. cpp:function:: NoU_Drivetrain(:cpp:class:`NoU_Motor`* frontLeftMotor, :cpp:class:`NoU_Motor`* frontRightMotor, :cpp:class:`NoU_Motor`* rearLeftMotor, :cpp:class:`NoU_Motor`* rearRightMotor)

        Constructs a new :cpp:class:`NoU_Drivetrain` using the specified four motors.

        :param :cpp:class:`NoU_Motor`* leftMotor: The motor on the left side of the drive train.
        :param :cpp:class:`NoU_Motor`* rightMotor: The motor on the right side of the drive train.

        **Example usage:**

        ::

            NoU_Motor frontLeftMotor(1);
            NoU_Motor frontRightMotor(2);
            NoU_Motor rearLeftMotor(3);
            NoU_Motor rearRightMotor(4);
            NoU_Drivetrain drivetrain(&frontLeftMotor, &frontRightMtoor, &rearLeftMotor, &rearRightMotor);

        Constructs a new drivetrain with the front left motor on motor port 1, the front right motor on motor port 2, the rear left motor on motor port 3, and the rear right motor on motor port 4.

        .. note:: Robot builders often wire the two motors on each side of the drivetrain into the same terminal block in parallel, using two motor ports for a four-motor drivetrain. In this case, the two-motor constructor should be used, :cpp:function:`NoU_Drivetrain(:cpp:class:`NoU_Motor`, .:cpp:class:`NoU_Motor`)`.

    .. cpp:function:: void tankDrive(float leftPower, float rightPower)

        Tank drive applies the specified output power directly to the left and right motors, after adjustments from :cpp:function:`setMinimumOutput`, :cpp:function:`setMaximumOutput`, :cpp:function:`setInputExponent`, and :cpp:function:`setInputDeadband`. This gives direct control over each side of the drivetrain.

        :param float leftPower: `-1...1`. The percentage of power to apply to the left side of the drivetrain.
        :param float rightPower: `-1...1`. The percentage of power to apply to the right side of the drivetrain.

        **Example usage:**

        ::

            drivetrain.tankDrive(-0.7, 0.5);

        Sets the left side of the drivetrain to go in reverse at 70% power and the right side to go forward at 50% power.

        .. seealso:: If unsure of which style of drivetrain control to use, curvature drive (:cpp:function:`curvatureDrive`) is usually recommended.

    .. cpp:function:: void arcadeDrive(float throttle, float rotation, boolean invertedReverse=false)

        Arcade drive takes the provided throttle and adjusts the power delivered to each side of the drivetrain based on the provided rotation value. This allows control over the robot's speed and rotation, similarly to many racing games, hence the name "arcade drive".

        :param float throttle: `-1...1`. The percentage of throttle to apply to the drivetrain.
        :param float rotation: `-1...1`. The amount by which the throttle should be adjusted for the two sides of the drivetrain in order to produce a turning effect. When going forward, a positive `rotation` value produces a clockwise rotation.
        :param bool invertedReverse: Whether turning should be inverted while driving in reverse. When this is set to `false` (default), the drivetrain's orientation will turn in the same direction for the same value of `rotation`, regardless of whether `throttle` is positive or negative. In other words, when `invertedReverse` is `false`, the curve the drivetrain travels when going forward is mirrored from the curve it travels going backwards, assuming `rotation` is held constant. When `invertedReverse` is `true`, the curve the drivetrain travels when going forward is the same one it travels when going backwards, keeping the center of rotation on the same side of the robot whether `throttle` is positive or negative.

        **Example usage:**

        ::

            drivetrain.arcadeDrive(0.7, 0.5);

        Sets the drivetrain to go forward at 70% throttle while turning to the right.

        ::

            drivetrain.arcadeDrive(-0.7, 0.5, false);

        Sets the drivetrain to go backwards at 70% throttle while turning to the right, causing the drivetrain to veer to its left side. The curve the drivetrain travels is the mirror image of the curve traveled by the first example.

        ::

            drivetrain.arcadeDrive(-0.7, 0.5, true);

        Sets the drivetrain to go backwards at 70% throttle while turning to the left, causing the drivetrain to veer to its right side. The curve the drivetrain travels is the same one as in the first example, only in reverse.

        .. seealso:: When using arcade drive, for the same value of `rotation`, the drivetrain will traverse a much tighter arc when `throttle` is small compared to when it is large. Curvature drive (:cpp:function:`curvatureDrive`), on the other hand, keeps the radius of the arc constant for the same value of `rotation`, regardless of throttle. Most drivers prefer this, so curvature drive is usually recommended.

        .. seealso:: This method is based on WPILib's implementation of arcade drive(`Java <https://github.com/wpilibsuite/allwpilib/blob/ee03a7ad3bcc156d3b9c07c590e32bca5df83537/wpilibj/src/main/java/edu/wpi/first/wpilibj/drive/DifferentialDrive.java#L172>`_, `C++ <https://github.com/wpilibsuite/allwpilib/blob/ee03a7ad3bcc156d3b9c07c590e32bca5df83537/wpilibc/src/main/native/cpp/drive/DifferentialDrive.cpp#L29>`_) for FIRST Robotics Competition.

    .. cpp:function:: void curvatureDrive(float throttle, float rotation, boolean isQuickTurn=true)

        When using arcade drive (see :cpp:function:`arcadeDrive`), for the same value of `rotation`, the drivetrain will traverse a much tighter arc when `throttle` is small compared to when it is large. Curvature drive is similar to arcade drive, but instead, regardless of the `throttle` value, the drivetrain traverses an arc with the same radius for the same value of `rotation`. In other words, rather than directly applying a differential to the power applied to the two sides of the drivetrain, the `rotation` value is the ratio of power applied to the two sides of the drivetrain.

        :param float throttle: `-1...1`. The percentage of throttle to apply to the drivetrain.
        :param float rotation: `-1...1`. The ratio of power between the two sides of the drivetrain. When going forward, a positive `rotation` value produces a clockwise rotation.
        :param bool isQuickTurn: If enabled (default), the drivetrain will operate in arcade drive when `throttle` is below 20%. If disabled, because `rotation` controls the ratio of power applied to the sides of the drivetrain rather than the differential, a high `rotation` value with a `throttle` of 0 will produce no motion rather than turning the robot in place. For this reason, it is recommended that quick turn remains enabled for most applications.

        .. note:: When compared to arcade drive, curvature drive acts as if `invertedReverse` is always `true`, meaning the robot will traverse the same curve for the same value of `rotation`, regardless of whether `throttle` is positive or negative.
        
        ..seealso:: This method is based on WPILib's implementation of curvature drive (`Java <https://github.com/wpilibsuite/allwpilib/blob/ee03a7ad3bcc156d3b9c07c590e32bca5df83537/wpilibj/src/main/java/edu/wpi/first/wpilibj/drive/DifferentialDrive.java#L202>`_, `C++ <https://github.com/wpilibsuite/allwpilib/blob/ee03a7ad3bcc156d3b9c07c590e32bca5df83537/wpilibc/src/main/native/cpp/drive/DifferentialDrive.cpp#L49>`_) for FIRST Robotics Competition.

        **Example usage:**

        ::

            drivetrain.curvatureDrive(0.7, 0.4);

        Sets the drivetrain to go forward at 70% throttle while turning to the right. The left side of the drivetrain is set to 70% power, while the right side is set to 0.4 times that, 28% power.

    .. cpp:function:: void holonomicDrive(float xVelocity, float yVelocity, float rotation)

    .. cpp:function:: void setMinimumOutput(float minimumOutput)

    .. cpp:function:: void setMaximumOutput(float maximumOutput)

    .. cpp:function:: void setInputExponent(float inputExponent)

    .. cpp:function:: void setInputDeadband(float inputDeadband)

