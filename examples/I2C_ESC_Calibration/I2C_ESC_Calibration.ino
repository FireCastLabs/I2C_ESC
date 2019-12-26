/*
  ESC_Calibration
    It's important to calibrate the ESC with the values (uS / microseconds) it will expect for Min and Max speed.
    This one requires a little procedure:  
      1 - Connect your Arduino board and your Adafruit PCA9685 16-Channel 12-bit PWM/Servo Driver - I2C interface
      2 - Load the sketch to your Arduino board, then remove power
      2 - Connect your ESC to the Arduino board
      3 - Power your Arduino board
      4 - Once the LED (LED_PIN) is HIGH/ON connect the power to your ESC, you have 5sec to do so
      5 - Once the LED is LOW/OFF the calibration should be done
      6 - Should now be calibrated between 1000us and 2000us
    
  Based on the 27 April 2017 Sketch by Eric Nantel and his RC_ESC library for Robot shop
  rewritten for use in the I2C_ESC library with the Adafruit PCA9685 16-Channel 12-bit PWM/Servo Driver - I2C interface
  
  Servo & Knob links
  http://www.arduino.cc/en/Tutorial/Knob
  http://people.interaction-ivrea.it/m.rinott
 */

#include "I2C_ESC.h"
#define LED_PIN (13)            // Pin for the LED 
#define SPEED_MIN (1000)        // Set the Zero throttle Speed in microseconds
#define SPEED_MAX (2000)        // Set the Maximum Speed in microseconds
#define ARM_VALUE (500)         // Set the Arm value in microseconds
#define SERVO_FREQ (50)         // Analog servos run at ~50 Hz updates
#define ESC_PIN (0)             // Pin for the ESC

/*
 * Instantiate the PWM extenders
 * ESC_Name (I2C_address, Minimum Value, Maximum Value, Default Speed, Arm Value)
 * 8 ESC/motors per I2C PWM/Servo extender, 16 signals per extender 2 lines per ESC with 1 for motor and 1 for reverse pin
 */
I2C_ESC myESC (0x40, SPEED_MIN, SPEED_MAX, ARM_VALUE);

void setup() {
  // Start serial port
  Serial.begin(9600);
  Serial.println("ESC calibration over the I2C based PWM/Servo control");
  
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

  delay(10); // Set a delay to allow the PCA9685 chips to set their frequency

  delay(10); // Set a delay to allow the PCA9685 chips to set their frequency

  // Start calibration cycle
  pinMode(LED_PIN, OUTPUT);       // LED Visual Output
  digitalWrite(LED_PIN, HIGH);    // LED High while signal is High indicating it's time to power the ESC
  myESC.calib(ESC_PIN);                  // Calibration of the Max and Min value the ESC is expecting
  myESC.stop(ESC_PIN);                   // Stop the ESC to avoid damage or injuries
  digitalWrite(LED_PIN, LOW);     // LED Low when the calibration is done (can be removed)
}

void loop() {
  // Noting to do in the loop, Calibration all happens in set up.
}
