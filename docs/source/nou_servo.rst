NoU_Servo
==========

.. cpp:class:: NoU_Servo

	Controls the output to one of the servo ports on the NoU2.
	
	**Public Functions**
	
	.. cpp:function:: NoU_Servo(uint8_t servoPort, uint16_t minPulse = 540, uint16_t maxPulse = 2300)
	
		Constructs a new :cpp:class:`NoU_Servo` on the specified port.
		
		:param uint8_t servoPort: The port number of the servo, visible in front of each set of servo pins on the NoU2.
	
	.. cpp:function:: void write(float degrees)
	
	.. cpp:function:: void writeMicroseconds(uint16_t pulseLength)
	
	.. cpp:function:: void setMinimumPulse(uint16_t minPulse)
	
	.. cpp:function:: void setMaximumPulse(uint16_t maxPulse)
	
	.. cpp:function:: uint16_t getMicroseconds()
	
	.. cpp:function:: float getDegrees()
	