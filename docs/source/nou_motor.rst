NoU_Motor
==========

.. cpp:class:: NoU_Motor

	Controls the output to one of the motor ports on the NoU2.

	**Public Functions**

	.. cpp:function:: NoU_Motor(uint8_t motorPort)

		Constructs a new :cpp:class:`NoU_Motor` on the specified port.
		
		:param uint8_t motorPort: The port number of the motor, visible in front of each terminal block on the NoU2.
		
		.. TODO: add the pins and PWM channel reserved for each motor port

		**Example usage:**

		::

			NoU_Motor myMotor(1);
			
		Constructs a new motor on motor port 1.
		   
	.. cpp:function:: void set(float output)
	
		Sets the power being applied to the motor and the direction of spin. Affects the state of the motor by changing it to ``FORWARD`` or ``BACKWARD``, but never ``BRAKE`` or ``RELEASE`` (see :cpp:func:`setState` for more information on these motor states).

		:param float output: `-1...1` The percentage of power to apply to the motor. The sign reverses the direction.
		
		**Example usage:**
		
		::
		
			myMotor.set(-0.5);
			
		Sets ``myMotor`` to spin in reverse at half speed.
	
	.. cpp:function:: void setPower(uint16_t power)
	
		Sets the power being applied to the motor, not affecting the direction the motor spins. To control motor spin direction when using this function, use :cpp:func:`setState`.
		
		:param uint16_t power: `0...1023` The duty cycle to send to the motor drivers, with 1023 being 100%.
		
		.. warning::
		
			This function is left public mainly to help with debugging issues with motor movement because it's a bit closer to the hardware than :cpp:func:`set`, allowing users to set the duty cycle with explicit 10-bit precision. It shouldn't be used on complete projects, but instead when you're not sure why a motor isn't behaving correctly and want to bypass any filtering you've applied to the :cpp:func:`set` function (i.e using :cpp:func:`setInputExponent`, :cpp:func:`setMaximumInput`, :cpp:func:`setInverted`, etc.).
		
	.. cpp:function:: void setState(uint8_t state)
	
		Sets the state of the motor, changing the behaviour of subsequent calls to :cpp:func:`setPower`. Typical usage of this function is to set the motor to the brake or release states. Generally, this function shouldn't be used to set the state to forward or backward, as :cpp:func:`set` accomplishes that behaviour based on the sign of its parameter.
	
		:param uint8_t state: The state to set the motor to. The possible inputs are defined as the following macros in Alfredo_NoU2.h_:  ``FORWARD``, ``BACKWARD``, ``BRAKE``, and ``RELEASE``.
		
		**Example usage:**
		
		::
		
			myMotor.setState(BRAKE);
			
		Sets ``myMotor`` to brake mode. This state would be cleared the next time :cpp:func:`set` is called.
		
			.. seealso::

				`This more technical explanation <DecayModes_>`_ of how the brake (slow decay) and release (fast decay) states work.
		
	
	.. cpp:function:: void setInverted(boolean isInverted)
	
		Sets whether the motor should always spin in the direction opposite of standard. This function is usually meant to be used called just once during setup, not repeatedly during operation. To switch the direction of a motor dynamically, use the :cpp:func:`set` function.
		
		:param boolean isInverted: If ``true``, sets the motor to spin in the opposite direction of standard. If ``false``, sets the motor to spin normally.
		
		**Example usage:**
		
		::
		
			myMotor.setInverted(true);
			
		Sets ``myMotor`` to be inverted.
	
	.. cpp:function:: boolean isInverted()
	
		Gets whether the motor has been set as inverted using the :cpp:func:`setInverted` function.
		
		:return: Returns ``true`` if the motor has be set as inverted; ``false`` otherwise.
	
	.. cpp:function:: void setMinimumOutput(float minimumOutput)
	
		Sets the minimum power that should be sent to the motor when using the :cpp:func:`set` function. Together with :cpp:func:`setMaximumOutput`, this function allows users to map inputs on the interval (0, 1] to (``minimumOutput``, ``maximumOutput``]. That is, if :cpp:func:`set` was passed an input just above zero, it would be mapped to an output just above :cpp:func:`minimumOutput`, which would be sent to the motor.
		
		:param float minimumOutput: `0...1` The minimum power that should be sent to the motor when using ``set``.
		
		.. note::  For motors in a ``NoU_Drivetrain``, the ``setMinimumOutput`` method of the ``NoU_Drivetrain`` class should be used, not this one.
	
	.. cpp:function:: void setMaximumOutput(float maximumOutput)
	
		Sets the maximum power that should be sent to the motor when using the :cpp:func:`set` function. Together with :cpp:func:`setMinimumOutput`, this function allows users to map inputs on the interval (0, 1] to (``minimumOutput``, ``maximumOutput``]. That is, if ``set`` was passed 1 as an input (i.e. full power), it would be mapped to ``maximumOutput``, which would be sent to the motor.
		
		:param float maximumOutput: `0...1` The maximum power that should be sent to the motor when using ``set``.
		
		.. note::  For motors in a ``NoU_Drivetrain``, the ``setMaximumOutput`` method of the ``NoU_Drivetrain`` class should be used, not this one.
	
	.. cpp:function:: void setExponent(float exponent)
	
		Sets the exponent to apply to inputs to the :cpp:func:`set` function.
		
		:param float exponent: The positive exponent to apply to inputs to :cpp:func:`set`.
		
		.. note::  For motors in a ``NoU_Drivetrain``, the ``setExponent`` method of the ``NoU_Drivetrain`` class should be used, not this one.
	
	.. cpp:function:: void setDeadband(float deadband)
	
		Sets the range of inputs to :cpp:func:`set` that should be mapped to zero.
		
		:param float deadband: `0...1` All inputs to :cpp:func:`set` with a smaller magnitude than this parameter will be mapped to zero.
		
		.. note:: For motors in a ``NoU_Drivetrain``, the ``setDeadband`` method of the ``NoU_Drivetrain`` class should be used, not this one.
	
	.. cpp:function:: float getOutput()
	
		Gets the current percentage of power being delivered to the motor. Updates when :cpp:func:`set` and :cpp:func:`setPower` are called.
		
		:return: `-1...1` The percentage of power being delivered to the motor, with negative values representing the reverse direction
	
	
.. _Alfredo_NoU2.h: https://github.com/AlfredoElectronics/Alfredo-NoU2/blob/master/Alfredo_NoU2.h
.. _DecayModes: https://www.allaboutcircuits.com/technical-articles/difference-slow-decay-mode-fast-decay-mode-h-bridge-dc-motor-applications/