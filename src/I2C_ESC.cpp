/*
 * Electronic Speed Controller (ESC) - Library
 */

#include "I2C_ESC.h"

/*
 * < Constructor > Sets up the proper pins to output.
 */
I2C_ESC::I2C_ESC(uint8_t I2C_Address, int outputMin, int outputMax, int armVal)
{
	oBoard = I2C_Address;	// The I2C address on the TwoWire interface

	oMin   = outputMin;
	oMax   = outputMax;
	oArm   = armVal;
	I2C_Servo  = Adafruit_PWMServoDriver(oBoard);
}

// < Destructor >
I2C_ESC::~I2C_ESC()
{
	// Nothing to destruct
}

/*
 * Set the current calibration delay in miliseconds
 *
 */
void I2C_ESC::setCalibrationDelay(uint32_t calibration_delay)
{
	calibrationDelay = calibration_delay;
}

/*
 * Set the current Stop pulse in microseconds
 *
 */
void I2C_ESC::setStopPulse(uint32_t stop_pulse)
{
	stopPulse = stop_pulse;
}

/*
 * Calibrate the maximum and minimum PWM signal the ESC is expecting
 */
void I2C_ESC::calib(int pin)
{
	I2C_Servo.writeMicroseconds(pin, oMax);
		delay(calibrationDelay);
	I2C_Servo.writeMicroseconds(pin, oMin);
		delay(calibrationDelay);
	arm(pin);
}

/*
 * Array of 8 ESCs to Calibrate the maximum and minimum PWM signal the ESC is expecting
 * This is not expected to work or actually be convenient due to the timing of the calibration process
 */
void I2C_ESC::calibArray(void)
{
	for (int count=0; count<8; count++)
	{
		I2C_Servo.writeMicroseconds(oPin[count], oMax);
			delay(calibrationDelay);
		I2C_Servo.writeMicroseconds(oPin[count], oMin);
			delay(calibrationDelay);
		arm(oPin[count]);
		delay(5000);
	}
}

/*
 * Arm the ESC
 */
void I2C_ESC::arm(int pin)
{
	I2C_Servo.writeMicroseconds(pin, oArm);
}

/*
 * Arm the ESC
 */
void I2C_ESC::armArray(void)
{
	for (int count=0; count<8; count++)
	{
		I2C_Servo.writeMicroseconds(oPin[count], oArm);
	}
}


/*
 * Stop the ESC with the specified PWM signal the ESC is expecting
 */
void I2C_ESC::stop(int pin)
{
	I2C_Servo.writeMicroseconds(pin, stopPulse);
}

/*
 * Stop the ESC with the specified PWM signal the ESC is expecting
 */
void I2C_ESC::stopArray(void)
{
	for (int count=0; count<8; count++)
	{
		I2C_Servo.writeMicroseconds(oPin[count], stopPulse);
	}
}

/*
 * Set the ESC Speed with the specified PWM signal the ESC is expecting
 */
void I2C_ESC::speed(int pin, int Speed)
{
	int oESC = constrain(Speed, oMin, oMax);
	I2C_Servo.writeMicroseconds(pin, oESC);
}

/*
 * Set the ESC Speed with the specified PWM signal the ESC is expecting
 */
void I2C_ESC::speedArray(int Speed)
{
	for (int count=0; count<8; count++)
	{
		int oESC = constrain(Speed, oMin, oMax);
		I2C_Servo.writeMicroseconds(oPin[count], oESC);
	}
}

/*
 * Change the ESC/motor speed by step value from an initial to final speed
 * Step time is the miliseconds between each speed change, default it 10 ms
 *
 */
void I2C_ESC::rampSpeed(int pin, int speedInitial, int speedFinal, int step, int stepTime)
{
	int oESC;  // Variable for the speed sent to the ESC

	if (speedInitial < speedFinal)
	{
		// Goes from Minimum Initial speed to Maximum final speed
		for (oESC = speedInitial; oESC <= speedFinal; oESC += step)
		{
			speed(pin, oESC);	// tell ESC to go to the oESC speed value
			delay(stepTime);	// waits 10ms for the ESC to reach speed
		}
	}
	else
	{
		// Goes from Maximum Initial speed to Minimum final speed
		for (oESC = speedInitial; oESC <= speedFinal; oESC -= step)
		{
			speed(pin, oESC);	// tell ESC to go to the oESC speed value
			delay(stepTime);	// waits 10ms for the ESC to reach speed
		}
	}
}

/*
 * Change the ESC/motor speed by step value from an initial to final speed
 * Step time is the miliseconds between each speed change, default it 10 ms
 *
 */
void I2C_ESC::rampSpeedArray(int speedInitial, int speedFinal, int step, int stepInterval)
{
	int oESC;  // Variable for the speed sent to the ESC

	if (speedInitial < speedFinal)
	{
		// Goes from Minimum Initial speed to Maximum final speed
		for (oESC = speedInitial; oESC <= speedFinal; oESC += step)
		{
			for (int count=0; count<8; count++) // cycle through the ESCs
			{
				speed(oPin[count], oESC);	// tell ESC to go to the oESC speed value
			}

			delay(stepInterval);	// waits 10ms for the ESCs to reach speed
		}
	}
	else
	{
		// Goes from Maximum Initial speed to Minimum final speed
		for (oESC = speedInitial; oESC <= speedFinal; oESC -= step)
		{
			for (int count=0; count<8; count++) // cycle through the ESCs
			{
				speed(oPin[count], oESC);	// tell ESC to go to the oESC speed value
			}

			delay(stepInterval);	// waits 10ms for the ESC to reach speed
		}
	}
}

/*
 * Set the ESC Speed with the specified PWM signal the ESC is expecting
 */
void I2C_ESC::reverse(int pin)
{
	// stop the ESC before sending the reverse signal
	stop(pin);
	// check whether we are in reverse mode
	if (REVERSE_MODE == false)
	{
		I2C_Servo.setPWM(pin+1, 4096, 0);  // turns pin+1 fully on
		REVERSE_MODE = true; // we are now in reverse mode
	}
	else
	{
		I2C_Servo.setPWM(pin+1, 0, 4096);  // turns pin+1 fully off
		REVERSE_MODE = false; // We are no longer in reverse mode
	}

	delay(100); // Set a small delay to allow the PCA9685 chips time to rearm
	arm(pin); // Send arm again to confim motors are ready 
}

/*
 * Set the ESC Speed with the specified PWM signal the ESC is expecting
 */
void I2C_ESC::reverseArray(void)
{
	// stop the ESCs before sending the reverse signal
	stopArray();
	// check whether we are in reverse mode
	if (REVERSE_MODE == false)
	{
		for (int count=0; count<8; count++) // cycle through the ESCs
		{
			I2C_Servo.setPWM(oPin[count+1], 4096, 0);  // turns pins+1 fully on
		}
		REVERSE_MODE = true; // we are now in reverse mode
	}
	else
	{
		for (int count=0; count<8; count++) // cycle through the ESCs
		{
			I2C_Servo.setPWM(oPin[count+1], 0, 4096);  // turns pins+1 fully off
		}
		REVERSE_MODE = false; // We are no longer in reverse mode
	}

	delay(100); // Set a small delay to allow the PCA9685 chips time to rearm
	armArray(); // Send arm again to confim motors are ready 
}

/*
 * Wrap the Adafruit_PWMServoDriver functions
 * These are 1-to-1 mappings and need to be checked when the wapped Library changes
 * Updated with adafruit/Adafruit-PWM-Servo-Driver-Library v2.3.1
 */

void I2C_ESC::begin(uint8_t prescale)
{
	I2C_Servo.begin(prescale);
}

void I2C_ESC::reset()
{
	I2C_Servo.reset();
}

void I2C_ESC::sleep()
{
	I2C_Servo.sleep();
}

void I2C_ESC::wakeup()
{
	I2C_Servo.wakeup();
}

void I2C_ESC::setExtClk(uint8_t prescale)
{
	I2C_Servo.setExtClk(prescale);
}

void I2C_ESC::setPWMFreq(float freq)
{
	I2C_Servo.setPWMFreq(freq);
}

void I2C_ESC::setOutputMode(bool totempole)
{
	I2C_Servo.setOutputMode(totempole);
}

uint8_t I2C_ESC::getPWM(uint8_t num)
{
	return I2C_Servo.getPWM(num);
}

void I2C_ESC::setPWM(uint8_t num, uint16_t on, uint16_t off)
{
	I2C_Servo.setPWM(num, on, off);
}

void I2C_ESC::setPin(uint8_t num, uint16_t val, bool invert)
{
	I2C_Servo.setPin(num, val, invert);
}

uint8_t I2C_ESC::readPrescale(void)
{
	return I2C_Servo.readPrescale();
}

void I2C_ESC::writeMicroseconds(uint8_t num, uint16_t Microseconds)
{
	I2C_Servo.writeMicroseconds(num, Microseconds);
}

void I2C_ESC::setOscillatorFrequency(uint32_t freq)
{
	I2C_Servo.setOscillatorFrequency(freq);
}

uint32_t I2C_ESC::getOscillatorFrequency(void)
{
	return I2C_Servo.getOscillatorFrequency();
}
