/*
 * Electronic Speed Controller (ESC) - Library
*/

#pragma once

#ifndef I2C_ESC_Library
#define I2C_ESC_Library

#if (ARDUINO >= 100)
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>	// Including the Adafruit I2C PWM extender Servo library
#define ESC_CAL_DELAY	(8000)	// Calibration delay between maximum and minimum (milisecond)
#define ESC_STOP_PULSE	(500)	// Stop Pulse value in miliseconds

class I2C_ESC
{
	public:
		I2C_ESC(uint8_t I2C_Address, int ESC_pin, int rev_pin, int outputMin = 1000, int outputMax = 2000, int armVal = 500);
		~I2C_ESC();
		void calib(void);
		void arm(void);
		void stop(void);
		void speed(int ESC_val);
		void reverse(void);

		// Wrap the public Adafruit_PWMServoDriver functions from v2.2.0
		void begin(uint8_t prescale = 0);
		void reset();
		void sleep();
		void wakeup();
		void setExtClk(uint8_t prescale);
		void setPWMFreq(float freq);
		void setOutputMode(bool totempole);
		uint8_t getPWM(uint8_t num);
		void setPWM(uint8_t num, uint16_t on, uint16_t off);
		void setPin(uint8_t num, uint16_t val, bool invert=false);
		uint8_t readPrescale(void);
		void writeMicroseconds(uint8_t num, uint16_t Microseconds);
		void setOscillatorFrequency(uint32_t freq);
		uint32_t getOscillatorFrequency(void);

	private:
	// < Local attributes >
		// Hardware
		uint8_t oBoard; // The I2C address on a TwoWire interface
		int oPin;	// I2C_ESC output Pin on the Adafruit PCA9685 16-Channel Servo Driver
		int rPin;	// I2C_ESC Pin of outputing of a reverse signal on the Adafruit PCA9685 16-Channel Servo Driver
		bool REVERSE_MODE; // a boolean for if the ESC is in Reverse mode

		// Calibration
		int oMin = 1000; 
		int oMax = 2000;
		int oESC = 1000;
		int oArm = 500;
		Adafruit_PWMServoDriver I2C_Servo; // create I2C servo object to control one of 16 ESCs
};

#endif
