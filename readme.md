This firmware was written by me and Alice Lau during our Hack the North project in 2018. 

It compiles and runs to an extent, though could be much cleaner and better documented.
We also did not manage to test the entire code as hardware problems provideda barrier.


FUNCTION
	
	1. The queen decides wich formation she wants to create with her slaves
	2. She turns on one of her 4 IR lights.
	3. SHe then cycles through an array ofpossibbleI2C addresses, waiting for a slaveto 	make contact and join the I2C network.
	4. The slaves move round until one feels an infrared light.
	5. That slave then advances until their IR sensor feels the strongest signal strength.
	6. It then turns on itself until its front is facing the source of the signal
	7. It moves towards the source
	8. As soon as it makes contact, electrodes on it connect it to the I2C network and it 	sends an Ack to the queen, confirming it has arrived.
	9. The queen immediattly instructs the slave to stop its motors and turn on the 	    appropriate IR led
	10. This process reapeats once another slave sees the new IR signal and until the     formation is made