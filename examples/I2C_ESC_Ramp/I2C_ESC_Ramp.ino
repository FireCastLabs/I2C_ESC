/*
  ESC_Ramp
    Based on the Sweep example in the Servo library, this allow a ramp up and down of the ESC speed based on the Min and Max values.
    The Min and Max speed are defined so you can change them at one location and it will be used in the ramp as well.

    Based on the 27 April 2017 Sketch by Eric Nantel and his RC_ESC library for Robot shop
    rewritten for use in the I2C_ESC library with the Adafruit PCA9685 16-Channel 12-bit PWM/Servo Driver - I2C interface
 */

#include "I2C_ESC.h"
#define LED_PIN (13)             // Pin for the LED 
#define SPEED_MIN (1000)         // Set the Minimum Speed in microseconds
#define SPEED_MAX (2000)         // Set the Minimum Speed in microseconds
#define ARM_VALUE (500)          // Set the Arm value in microseconds
#define FREQ (60)                // Analog servos run at ~60 Hz updates

I2C_ESC myESC (0x40, 0, 1, SPEED_MIN, SPEED_MAX, 500);       // ESC_Name (I2C_address, ESC PIN, Minimum Value, Maximum Value, Default Speed, Arm Value)
int oESC;                                                 // Variable for the speed sent to the ESC

void setup() {
  // start serial port
  Serial.begin(9600);
  Serial.println("ESC Ramp test over the I2C PWM/Servo extension interface");

  /*
   * Set up the I2C based PWM/Servo extenders
   * This is only done once per Adafruit PCA9685 PWM/Servo driver
   */
  myESC.begin();

  /*
   * In theory the internal oscillator (clock) is 25MHz but it really isn't that precise. 
   * You can 'calibrate' by tweaking this number till you get the frequency you're expecting!
   * The int.osc. is closer to 27MHz and is used for calculating things like writeMicroseconds
   * This is only done once per Adafruit PCA9685 PWM/Servo driver
   */
  myESC.setOscillatorFrequency(26075000);

 /*
  * Set the analog servo PWM frequency
  * alternativly you could set this using the prescale 60Hz is a prescale of about 105 (depending on the internal oscillator frequency)
  * This is only done once per Adafruit PCA9685 PWM/Servo driver
  */
  myESC.setPWMFreq(SERVO_FREQ);

  delay(10); // Set a small delay to allow the PCA9685 chips time to set their frequency

  pinMode(LED_PIN, OUTPUT);                               // LED Visual Output
  myESC.arm();                                            // Send the Arm value so the ESC will be ready to take commands
  digitalWrite(LED_PIN, HIGH);                            // LED High Once Armed
  delay(5000);                                            // Wait for a while
  myESC.speed(SPEED_MIN);                                 // Set to minimum speed now that the ESC should be Armed
}

void loop() {
  Serial.println("ESC Ramp up");
  for (oESC = SPEED_MIN; oESC <= SPEED_MAX; oESC += 1) {  // goes from Minimum microseconds to Maximum microseconds
    myESC.speed(oESC);                                    // tell ESC to go to the oESC speed value
    delay(10);                                            // waits 10ms for the ESC to reach speed
  }
  delay(1000);
  Serial.println("ESC Ramp down");
  for (oESC = SPEED_MAX; oESC >= SPEED_MIN; oESC -= 1) {  // goes from Maximum microseconds to Minimum microseconds
    myESC.speed(oESC);                                    // tell ESC to go to the oESC speed value
    delay(10);                                            // waits 10ms for the ESC to reach speed  
   }
  delay(5000);                                            // Wait for a while before restarting the loop
}
