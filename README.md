# I2C_ESC  [![Build Status](https://travis-ci.com/FireCastLabs/I2C_ESC.svg?branch=master)](https://travis-ci.com/FireCastLabs/I2C_ESC)
An ESC control library for controlling an Aerostar RVS TYPE ESC w/Reverse Function line over an Adafruit PCA9685 16-Channel 12-bit PWM/Servo Driver and I2C interface

# Warning Library issues
This library is being depreceated in favor of the [I2C_Array_ESC library](https://github.com/FireCastLabs/I2C_Array_ESC) This library has had many issues with communicating over the I2C bus since each Library instance for a ESC/motor creates an new instance of the wrapped [adafruit/Adafruit-PWM-Servo-Driver-Library](https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library). The multiple libraries all trying to talk to the same I2C device is inconsistant. The [I2C_Array_ESC library](https://github.com/FireCastLabs/I2C_Array_ESC) solved this issue by being focused on the singular I2C device and prepopulates the motor pins. Again we do not recommend this library version due to the I2C issues we have encountered.

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
- `setCalibrationDelay(uint32_t calibration_delay)`
  - set the calibration delay for ESC calibration. Default delay is 8000 ms
- `setStopPulse(uint32_t stop_pulse)`
  - set the stop pulse value. The default is 500 us
- `rampSpeed(int speedInitial, int speedFinal, int step = 1, int stepTime = 10)`
  - Change the ESC/motor speed by step value from an initial to final speed. The step time is how long in milliseconds between each step

#### Wrapped Adafruit-PWM-Servo-Driver-Library specific notes
The following wrapped Adafruit-PWM-Servo-Driver-Library specific functions allow controling the I2C functionality for the devices. The begin() function should be used only once per Adafruit PCA9685 PWM Servo Driver and not once per library instance. Calling the begin(), reset(), sleep(), wakeup() functions multiple times can cause undesirable behaviors and clog the wire I2C bus.
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
