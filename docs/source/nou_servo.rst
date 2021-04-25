NoU_Servo
==========

.. cpp:class:: NoU_Servo

	Controls the output to one of the servo ports on the NoU2. The duty cycle of the 50 Hz PWM signal generated has 16 bits of precision (i.e. 0...65535).
	
	**Public Functions**
	
	.. cpp:function:: NoU_Servo(uint8_t servoPort, uint16_t minPulse = 540, uint16_t maxPulse = 2300)
	
		Constructs a new :cpp:class:`NoU_Servo` on the specified port. The default values for ``minPulse`` and ``maxPulse`` have been configured experimentally for the range accepted by most common `9g servos <https://www.amazon.com/Micro-Helicopter-Airplane-Remote-Control/dp/B072V529YD>`_, although each servo is a little different and often has slightly variant minimum and maximum pulse-widths.
		
		:param uint8_t servoPort: The port number of the servo, visible in front of each set of servo pins on the NoU2.
		:param uint16_t minPulse: The optional minimum pulse-width to send to the servo in microseconds, corresponding to 0°. See :cpp:func:`setMinimumPulse`.
		:param uint16_t minPulse: The optional maximum pulse-width to send to the servo in microseconds, corresponding to 180°. See :cpp:func:`setMaximumPulse`.
		
		.. TODO: Add which port uses up which pin and channel
	
	.. cpp:function:: void write(float degrees)
	
		Commands the servo to move to the specified degree heading, based on the configured minimum and maximum pulse-widths.
		
		:param float degrees: The degree heading to command the servo to move to. Maps 0° to the minimum pulse-width and 180° to the maximum pulse-width. Other values are interpolated linearly, including those outside the range of 0...180, although they will produce a pulse-width outside of the minimum and maxmimum.
	
	.. cpp:function:: void writeMicroseconds(uint16_t pulseLength)
	
		Sends a PWM signal with the specified pulse-width to the servo. Ignores the configured minimum and maximum pulse-widths.
		
		:param uint16_t pulseLength: The pulse-width in microseconds of the PWM signal to begin sending.
	
	.. cpp:function:: void setMinimumPulse(uint16_t minPulse)
	
		Sets the pulse-width corresponding to 0° with regard to the :cpp:func:`write` function. This value can usually be found in the datasheet for a servo, although it should be noted that the actual minimum pulse-width for some servos can vary slightly from the reported values. To get the greatest range possible out of a servo, it can be necessary to experimentally tweak the minimum pulse-width until the servo is clearly at the edge of its range.
		
		:param uint16_t minPulse: The pulse-width in microseconds corresponding to 0°.
	
	.. cpp:function:: void setMaximumPulse(uint16_t maxPulse)
	
		Sets the pulse-width corresponding to 180° with regard to the :cpp:func:`write` function. This value can usually be found in the datasheet for a servo, although it should be noted that the actual maximum pulse-width for some servos can vary slightly from the reported values. To get the greatest range possible out of a servo, it can be necessary to experimentally tweak the maximum pulse-width until the servo is clearly at the edge of its range.
		
		:param uint16_t maxPulse: The pulse-width in microseconds corresponding to 180°.
	
	.. cpp:function:: uint16_t getMicroseconds()
	
		Gets the pulse-width in microseconds of the PWM signal currently being generated for this servo. Updates when :cpp:func:`write` and :cpp:func:`writeMicroseconds` are called.
		
		:return: The pulse-width of the current output in microseconds.
	
	.. cpp:function:: float getDegrees()
	
		Gets the pulse-width in degrees of the PWM signal currently being generated for this servo, based on the configured minimum and maximum pulse-widths. Updates when :cpp:func:`write` and :cpp:func:`writeMicroseconds` are called.
		
		:return: The pulse-width of the current output in degees, with the configured minimum pulse-width being 0°, and the maximum being 180°.