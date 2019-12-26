/** 
This sketch is for running a drone motor using an ESC
using the serial monitor as an input for speed.

Maximum speed input:  2000
Minimum speed input:  1000 the zero throttle speed

Decreasing below the minimum will result in the motor stalling.
Increasing above the maximum will be adjusted to the maximum. 

Hardware: 1 * Arduino combatable board with I2C bus
          : 1 * ESC
          : 1 * external powersource for the ESC.
          : 1 * 


WireColor Coding:   black = ground
                    red = 
                    white = signal
**/

#include "I2C_ESC.h"
#define LED_PIN (13)       // Pin for the LED 
#define SPEED_MIN (1000)   // Set the Zero throttle Speed in microseconds
#define SPEED_MAX (2000)   // Set the Maximum Speed in microseconds
#define ARM_VALUE (500)    // Set the Arm value in microseconds
#define SERVO_FREQ (50)    // Analog servos run at ~50 Hz updates
#define ESC_PIN (0)        // Pin for the ESC on the I2C PWM/Servo extenders this value is the same for both extenders in this example
#define ESC_REV_PIN (1)    // Pin for the revers line singal to the ESC on the I2C PWM/Servo extenders this value is the same for both extenders in this example

int oESC;                                                 // Variable for the speed sent to the ESC

/*
 * Instantiate the PWM extenders
 * ESC_Name (I2C_address, Minimum Value, Maximum Value, Default Speed, Arm Value)
 * 8 ESC/motors per I2C PWM/Servo extender, 16 signals per extender 2 lines per ESC with 1 for motor and 1 for reverse pin
 */
I2C_ESC myESC (0x40, SPEED_MIN, SPEED_MAX, ARM_VALUE);
I2C_ESC myESC1 (0x41, SPEED_MIN, SPEED_MAX, ARM_VALUE);

void setup() {
  // start serial port
  Serial.begin(9600);
  Serial.println("I2C Controller Test with ESC");

  /*
   * Set up the I2C based PWM/Servo extenders
   * This is only done once per Adafruit PCA9685 PWM/Servo driver
   */
  myESC.begin();
  myESC1.begin();

  /*
   * In theory the internal oscillator (clock) is 25MHz but it really isn't that precise. 
   * You can 'calibrate' by tweaking this number till you get the frequency you're expecting!
   * The int.osc. is closer to 27MHz and is used for calculating things like writeMicroseconds
   * This is only done once per Adafruit PCA9685 PWM/Servo driver
   */
  myESC.setOscillatorFrequency(26075000);
  myESC1.setOscillatorFrequency(26075000);

  /*
  * Set the analog servo PWM frequency
  * alternativly you could set this using the prescale 50Hz is a prescale of about ### (depending on the internal oscillator frequency)
  * This is only done once per Adafruit PCA9685 PWM/Servo driver
  */
  myESC.setPWMFreq(SERVO_FREQ);  
  myESC1.setPWMFreq(SERVO_FREQ);


  delay(10); // Set a small delay to allow the PCA9685 chips time to set their frequency

  pinMode(LED_PIN, OUTPUT);    // Set Pin for LED Visual Output

  // Send the Arm value to each ESC so the ESCs will be ready to take commands
  myESC.arm(ESC_PIN);
  myESC1.arm(ESC_PIN);
  delay(5);                     // Wait for 5 milliseconds before showing the LED visual for Arming confirmation
  digitalWrite(LED_PIN, HIGH);  // LED High Once Armed
  delay(5000);                  // Wait for a while before going in to the loop
  myESC.speed(ESC_PIN, SPEED_MIN);       // Set ESC to minimum speed now that the ESC should be Armed
  myESC1.speed(ESC_PIN, SPEED_MIN);      // Set ESC to minimum speed now that the ESC should be Armed
}

void loop() {
  if (Serial.available() > 0)   // read the value from the serial
  {
    oESC = Serial.parseInt();
    if (oESC == 5)
    {
      Serial.println("stopping and setting all ESCs to reverse mode");
      myESC.reverse(ESC_REV_PIN);
      myESC1.reverse(ESC_REV_PIN);
    }
    else
    {
      myESC.speed(ESC_PIN, oESC);
      myESC1.speed(ESC_PIN, oESC);
      Serial.print(ESC_PIN, oESC);
      Serial.println(" speed for all ESCs");
    }

    delay(10);                                            // Wait for a while before restart
  }
}
