/*
  ESC_Stop
    This is to illustrate the "stop" command that can be use. It will send a 500us value which in most cases will stop the motor.
    If another value is needed, it can be changed in the library ESC.h under "ESC_STOP_PULSE" 

    Based on the 27 April 2017 Sketch by Eric Nantel and his RC_ESC library for Robot shop
    rewritten for use in the I2C_ESC library with the Adafruit PCA9685 16-Channel 12-bit PWM/Servo Driver - I2C interface
**/
#include "I2C_ESC.h"
#define LED_PIN (13)            // Pin for the LED
#define SPEED_MIN (1000)        // Set the Zero throttle Speed in microseconds
#define SPEED_MAX (2000)        // Set the Maximum Speed in microseconds
#define ARM_VALUE (500)         // Set the Arm value in microseconds
#define SERVO_FREQ (50)         // Analog servos run at ~50 Hz updates
#define ESC_PIN (0)             // Pin for the ESC on the I2C PWM/Servo extender

/*
 * Instantiate the PWM extenders
 * ESC_Name (I2C_address, Minimum Value, Maximum Value, Default Speed, Arm Value)
 * 8 ESC/motors per I2C PWM/Servo extender, 16 signals per extender 2 lines per ESC with 1 for motor and 1 for reverse pin
 */
I2C_ESC myESC (0x40, SPEED_MIN, SPEED_MAX, ARM_VALUE);

void setup()
{
  // start serial port
  Serial.begin(9600);
  Serial.println("I2C Controller Test with ESC");

  /*
   * Set up the I2C based PWM/Servo extenders
   * begin() calls the wire.begin()
   * This is only done once per Adafruit PCA9685 PWM/Servo driver
   */
  myESC.begin();

  /*
   * In theory the internal oscillator (clock) is 25MHz but it really isn't that precise. 
   * You must 'calibrate' by tweaking this number until you get the PWM update frequency you're expecting!
   * The int.osc. is used for calculating things like writeMicroseconds
   * Analog servos run at ~50 Hz updates, It is very importaint to use an oscilloscope in setting the frequency 
   * for the I2C PCA9685 PWM/Servo extender chip. 
   * 1) Attach the oscilloscope to one of the PWM signal pin and ground on the I2C PCA9685 chip you are setting the value for.
   * 2) Adjust setOscillatorFrequency() until the PWM update frequency is the expected value (50Hz for most ESCs)
   * Setting the value here is specific to each individual I2C PCA9685 chip and affects the calculations for the PWM update frequency.
   * Failure to correctly set this value will cause unusual behavior in the ESCs
   * We only need to do this once per chipset
   */
  myESC.setOscillatorFrequency(24600000);

 /*
  * Set the analog servo PWM frequency
  * alternativly you could set this using the prescale 50Hz is a prescale of about ### (depending on the internal oscillator frequency)
  * This is only done once per Adafruit PCA9685 PWM/Servo driver
  */
  myESC.setPWMFreq(SERVO_FREQ);

  delay(10); // Set a small delay to allow the PCA9685 chips time to set their frequency

  pinMode(LED_PIN, OUTPUT);        // LED Visual Output
  myESC.arm(ESC_PIN);              // Send the Arm value so the ESC will be ready to take commands
  digitalWrite(LED_PIN, HIGH);     // LED High Once Armed
  delay(5000);                     // Wait for a while
  myESC.speed(ESC_PIN, SPEED_MIN); // Set ESC to minimum speed now that the ESC should be Armed
}

void loop()
{
  myESC.speed(ESC_PIN, 1200);      // Set the speed to a testing value between SPEED_MIN (1000) and SPEED_MAX (2000)
  delay(500);                      // Wait for a while 
  myESC.stop(ESC_PIN);             // Stop the ESC altogether
  delay(5000);                     // Wait for a while until we restart the loop
}

