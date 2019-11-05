/*
 * Electronic Speed Controller (ESC) - Library
 */

#include "I2C_ESC.h"

/*
 * < Constructor > Sets up the proper pins to output.
 */
I2C_ESC::I2C_ESC(uint8_t I2C_Address, int ESC_pin, int rev_pin, int outputMin, int outputMax, int armVal)
{
	oBoard = I2C_Address;	// The I2C address on the TwoWire interface
	oPin   = ESC_pin;	// ESC output Pin on the Adafruit PCA9685 16-Channel Servo Driver
	rPin   = rev_pin;	// I2C_ESC Pin of outputing of a reverse signal on the Adafruit PCA9685 16-Channel Servo Driver
	REVERSE_MODE = false; // start in normal mode

	oMin   = outputMin;
	oMax   = outputMax;
	oArm   = armVal;
	I2C_Servo  = Adafruit_PWMServoDriver(oBoard);
	// Ensure the reverse pin is in off mode at startup
	//I2C_Servo.setPWM(rPin, 0, 4096);  // turns pin fully off
}

// < Destructor >
I2C_ESC::~I2C_ESC()
{
	// Nothing to destruct
}

/*
 * Calibrate the maximum and minimum PWM signal the ESC is expecting
 */
void I2C_ESC::calib(void)
{
	I2C_Servo.writeMicroseconds(oPin, oMax);
		delay(calibrationDelay);
	I2C_Servo.writeMicroseconds(oPin, oMin);
		delay(calibrationDelay);
	arm();
}

/*
 * Arm the ESC
 */
void I2C_ESC::arm(void)
{
	I2C_Servo.writeMicroseconds(oPin, oArm);
}

/*
 * Stop the ESC with the specified PWM signal the ESC is expecting
 */
void I2C_ESC::stop(void)
{
	I2C_Servo.writeMicroseconds(oPin, stopPulse);
}

/*
 * Set the ESC Speed with the specified PWM signal the ESC is expecting
 */
void I2C_ESC::speed(int Speed)
{
	oESC = constrain(Speed, oMin, oMax);
	I2C_Servo.writeMicroseconds(oPin, oESC);
}

/*
 * Set the ESC Speed with the specified PWM signal the ESC is expecting
 */
void I2C_ESC::reverse(void)
{
	// stop the motor before sending the reverse signal
	stop();
	// check whether we are in reverse mode
	if (REVERSE_MODE == false)
	{
		I2C_Servo.setPWM(rPin, 4096, 0);  // turns pin fully on
		REVERSE_MODE = true; // we are now in reverse mode
	}
	else
	{
		I2C_Servo.setPWM(rPin, 0, 4096);  // turns pin fully off
		REVERSE_MODE = false; // We are no longer in reverse mode
	}
}

/*
 * Get the current calibration delay in miliseconds
 *
 */
uint32_t getCalibrationDelay(void)
{
	return calibrationDelay;
}

/*
 * Set the current calibration delay in miliseconds
 *
 */
void setCalibrationDelay(uint32_t calibration_delay)
{
	calibrationDelay = calibration_delay;
}

/*
 * Get the current Stop pulse in microseconds
 *
 */
uint32_t getStopPulse(void)
{
	return stopPulse;
}

/*
 * Set the current Stop pulse in microseconds
 *
 */
void setStopPulse(uint32_t stop_pulse)
{
	stopPulse = stop_pulse;
}

/*
 * Wrap the Adafruit_PWMServoDriver functions
 * These are 1-to-1 mappings and need to be checked when the wapped Library changes
 * Updated with adafruit/Adafruit-PWM-Servo-Driver-Library v2.2.0
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
