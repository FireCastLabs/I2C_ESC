# I2C_ESC  [![Build Status](https://travis-ci.com/FireCastLabs/I2C_ESC.svg?branch=master)](https://travis-ci.com/FireCastLabs/I2C_ESC)
An ESC control library for controlling an Aerostar RVS TYPE ESC w/Reverse Function line over an Adafruit PCA9685 16-Channel 12-bit PWM/Servo Driver and I2C interface

## Summary
This Library is based on [RB-ENantel/RC_ESC library](https://github.com/RB-ENantel/RC_ESC) and extended to work with Adafruit PCA9685 16-Channel Servo Drivers on the I2C bus and fully wraps the [adafruit/Adafruit-PWM-Servo-Driver-Library](https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library)

## Supported platforms

This Library is designed to work with the Arduino IDE versions 1.8.x or later; we have not tested it with earlier versions.  This Library should support any Arduino compatible board and the Adafruit PCA9685 I2C 16-Channel PWM/Servo Drivers

## Getting Started
Basic Instructions on how to use the ESC portion of the library can be found in the following Robotshop blog post.
https://www.robotshop.com/community/blog/show/rc-speed-controller-esc-arduino-library

Basic Instructions on how to use the I2C PWM/Servo wapper portion of the library can be found in the following Robotshop blog post.
https://learn.adafruit.com/16-channel-pwm-servo-driver

### Hardware

Aerostar RVS 40A Electronic Speed Controller w/Reverse Function 3A BEC (2~4S) can be purchased through [Hobby King's website](https://hobbyking.com/en_us/aerostar-rvs-40a-electronic-speed-controller-w-reverse-function-and-2a-bec-2-4s.html?wrh_pdp=2) other versions of this Aerostar RVS ESC with a Reverse Function line should also work. 

Adafruit PCA9685 16-Channel Servo Drivers can be purchased on [Adafruit’s website](https://www.adafruit.com/product/815). See the [Adafruit PCA9685 16-Channel Servo Driver user’s guide and tutorial](https://learn.adafruit.com/16-channel-pwm-servo-driver/overview) and the [adafruit/Adafruit-PWM-Servo-Driver-Library](https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library) for more details.

## Documentation

- `I2C_ESC(uint8_t I2C_Address, int ESC_pin, int rev_pin, int outputMin, int outputMax, int armVal)`
  - Default constructor
- `calib()`
  - Calibrate motor
- `arm()`
  - Arm motor
- `stop()`
  - Stop motor
- `speed(int speed)`
  - Set speed for motor
- `reverse()`
  - stop and reverse the motors
  
  ## Version History
  - no releases have been made yet
