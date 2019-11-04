/** 
This sketch is for running a drone motor using an ESC
using the serial monitor as an input for speed.

Maximum speed input:  2000
Minimum speed input:  1060

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
#define LED_PIN (13)            // Pin for the LED 
#define SPEED_MIN (1000)        // Set the Minimum Speed in microseconds
#define SPEED_MAX (2000)        // Set the Maximum Speed in microseconds
#define ARM_VALUE (500)         // Set the Arm value in microseconds
#define SERVO_FREQ (60)         // Analog servos run at ~60 Hz updates

I2C_ESC myESC (0x40, 0, 1, SPEED_MIN, SPEED_MAX, ARM_VALUE);       // ESC_Name (I2C_address, ESC PIN, Minimum Value, Maximum Value, Default Speed, Arm Value)
I2C_ESC myESC1 (0x41, 0, 1, SPEED_MIN, SPEED_MAX, ARM_VALUE);      // ESC_Name (I2C_address, ESC PIN, Minimum Value, Maximum Value, Default Speed, Arm Value)
int oESC;                                                 // Variable for the speed sent to the ESC

void setup() {
  // start serial port
  Serial.begin(9600);
  Serial.println("I2C Controller Test with ESC");

  //Set up the PWM extenders
  myESC.begin();
  myESC1.begin();

  /*
   * In theory the internal oscillator (clock) is 25MHz but it really isn't that precise. 
   * You can 'calibrate' by tweaking this number till you get the frequency you're expecting!
   * The int.osc. is closer to 27MHz and is used for calculating things like writeMicroseconds
   */
  myESC.setOscillatorFrequency(26075000);
  myESC1.setOscillatorFrequency(26075000);

  /*
  * Set the analog servo PWM frequency
  * alternativly you could set this using the prescale 60Hz is a prescale of about 105 (depending on the internal oscillator frequency)
  */
  myESC.setPWMFreq(SERVO_FREQ);  
  myESC1.setPWMFreq(SERVO_FREQ);

  pinMode(LED_PIN, OUTPUT);    // Set Pin for LED Visual Output

  // Send the Arm value to each ESC so the ESCs will be ready to take commands
  myESC.arm();
  myESC1.arm();
  delay(5);                     // Wait for 5 milliseconds before showing the LED visual for Arming confirmation
  digitalWrite(LED_PIN, HIGH);  // LED High Once Armed
  delay(1000);                  // Wait for a while before going in to the loop
}

void loop() {
  if (Serial.available() > 0)                             // read the value from the serial
  {
    oESC = Serial.parseInt();
    if (oESC == 5)
    {
      Serial.println("stopping and setting all ESCs to reverse mode");
      myESC.reverse();
      myESC1.reverse();
    }
    else
    {
      myESC.speed(oESC);
      myESC1.speed(oESC);
      Serial.print(oESC);
      Serial.println(" speed for all ESCs");
    }

    delay(10); 
  }                                           // Wait for a while before restart
}
