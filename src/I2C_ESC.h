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

class I2C_ESC
{
	public:
		I2C_ESC(uint8_t I2C_Address, int outputMin = 1000, int outputMax = 2000, int armVal = 500);
		~I2C_ESC();
		void setCalibrationDelay(uint32_t calibration_delay);
		void setStopPulse(uint32_t stop_pulse);
		void calib(int pin);
		void calibArray(void);
		void arm(int pin);
		void armArray(void);
		void stop(int pin);
		void stopArray(void);
		void reverse(int pin);
		void reverseArray(void);
		void speed(int pin, int ESC_val);
		void speedArray(int ESC_val);
		void rampSpeed(int pin, int speedInitial, int speedFinal, int step = 1, int stepInterval = 10);
		void rampSpeedArray(int speedInitial, int speedFinal, int step = 1, int stepInterval = 10);

		// Wrap the public Adafruit_PWMServoDriver functions from v2.3.1
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
		uint8_t oBoard = 0x40; // The I2C address on a TwoWire interface
		int oPin[8] = {0,2,4,6,8,10,12,14};	// An array of output Pins on the Adafruit PCA9685 16-Channel Servo Driver
		int rPin[8] = {1,3,5,7,9,11,13,15};	// An array of Pins for a reverse signal on the Adafruit PCA9685 16-Channel Servo Driver
		bool REVERSE_MODE = false; // a boolean for if the ESC is in Reverse mode

		// Calibration
		int oMin = 1000; 
		int oMax = 2000;
		int oESC = 1000;
		int oArm = 500;
		uint32_t calibrationDelay = 8000;	// Calibration delay (miliseconds)
		uint32_t stopPulse = 500;	// The ESC specific Stop pulse (microseconds) value else use a Zero Throttle value (1000)

		Adafruit_PWMServoDriver I2C_Servo; // create I2C servo object to control one of 16 ESCs
};

#endif
