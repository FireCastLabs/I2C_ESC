# I2C_ESC  [![Build Status](https://travis-ci.com/FireCastLabs/I2C_ESC.svg?branch=master)](https://travis-ci.com/FireCastLabs/I2C_ESC)
An ESC control library for controlling an Aerostar RVS TYPE ESC w/Reverse Function line over an Adafruit PCA9685 16-Channel 12-bit PWM/Servo Driver and I2C interface

## Summary
This Library is based on [RB-ENantel/RC_ESC library](https://github.com/RB-ENantel/RC_ESC) and extended to work with Adafruit PCA9685 16-Channel Servo Drivers on the I2C bus and fully wraps the [adafruit/Adafruit-PWM-Servo-Driver-Library](https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library).

## Supported platforms

This Library is designed to work with the Arduino IDE versions 1.8.x or later; we have not tested it with earlier versions. This Library should support any Arduino compatible board and the Adafruit PCA9685 I2C 16-Channel PWM/Servo Drivers

## Getting Started
Basic Instructions on how to use the ESC portion of the library can be found in the following Robotshop blog post.
https://www.robotshop.com/community/blog/show/rc-speed-controller-esc-arduino-library

Basic Instructions on how to use the I2C PWM/Servo wapper portion of the library can be found in the following Robotshop blog post.
https://learn.adafruit.com/16-channel-pwm-servo-driver

### Hardware

Aerostar RVS 40A Electronic Speed Controller w/Reverse Function 3A BEC (2~4S) can be purchased through [Hobby King's website](https://hobbyking.com/en_us/aerostar-rvs-40a-electronic-speed-controller-w-reverse-function-and-2a-bec-2-4s.html?wrh_pdp=2) other versions of this Aerostar RVS ESC with a Reverse Function line should also work.

Adafruit PCA9685 16-Channel Servo Drivers can be purchased on [Adafruit’s website](https://www.adafruit.com/product/815). See the [Adafruit PCA9685 16-Channel Servo Driver user’s guide and tutorial](https://learn.adafruit.com/16-channel-pwm-servo-driver/overview) and the [adafruit/Adafruit-PWM-Servo-Driver-Library](https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library) for more details.

## Documentation

- `I2C_ESC(uint8_t I2C_Address, int outputMin, int outputMax, int armVal)`
  - Default constructor
    - ESCs are plugged in with the control signal line then the reverse signal line. That gives pins 0 and 1 to the first ESC then 2 and 3 to the second ESC, etc
- `calib(int ESC_pin)`
  - Calibrate ESC on ESC_Pin
- `calibArray()`
  - Calibrate the Array of ESCs
- `arm(int ESC_pin)`
  - Arm ESC on ESC_Pin
- `armArray()`
  - Arm the Array of ESCs
- `stop(int ESC_pin)`
  - Send the stop pulse to the ESC on ESC_Pin to stop the motor
- `stopArray()`
  - Send the stop pulse to the Array of ESCs to stop the array of motors
- `speed(int ESC_pin, int speed)`
  - Send the speed pulse between the min and max calibration limits to the ESC on ESC_Pin to set the motor speed
- `speedArray(int speed)`
  - Send the speed pulse between the min and max calibration limits to the array of ESCs to set the motor array speed
- `reverse(int ESC_pin)`
  - tell the ESC on ESC_Pin to stop and reverse the motor
- `reverseArray()`
  - tell the array of ESCs to stop and reverse the motor array
- `rampSpeed(int ESC_pin, int speedInitial, int speedFinal, int step = 1, int stepTime = 10)`
  - Change the ESC/motor speed on ESC_Pin by step value from an initial to final speed. The step time is how long in milliseconds between each step
- `rampSpeedArray(int speedInitial, int speedFinal, int step = 1, int stepTime = 10)`
  - Change the array of ESCs/motors speed by step value from an initial to final speed. The step time is how long in milliseconds between each step
- `setCalibrationDelay(uint32_t calibration_delay)`
  - set the calibration delay for ESC calibration. Default delay is 8000 ms
- `setStopPulse(uint32_t stop_pulse)`
  - set the stop pulse value. The default is 500 us

#### Wrapped Adafruit-PWM-Servo-Driver-Library specific notes
The following wrapped Adafruit-PWM-Servo-Driver-Library specific functions allow controling the I2C functionality for the devices. The begin() function should be used only once. Calling the begin(), reset(), sleep(), wakeup() functions multiple times can cause undesirable behaviors and clog the wire I2C bus.
Based on Adafruit-PWM-Servo-Driver-Library version 2.3.1

- `begin(uint8_t prescale = 0)`
- `reset()`
- `sleep()`
- `wakeup()`
- `setExtClk(uint8_t prescale)`
- `setPWMFreq(float freq)`
- `setOutputMode(bool totempole)`
- `setOscillatorFrequency(uint32_t freq)`

  ## Version History
  - no releases have been made yet
