/** 
This sketch is for checking frequency control over the PWM signal
using the serial monitor as an input for Frequency
Maximum input Frequency:  1000
Minimum input Frequency:  40

Hardware: : 1 * Arduino compatable board 
          : 1 * 
          : 1 * 

WireColor Coding:   black = ground
                    red = + 12vDC 
                    white = signal
**/

#include "I2C_ESC.h"
#define LED_PIN (13)            // Pin for the LED 
#define SPEED_MIN (1000)        // Set the Minimum Speed in microseconds
#define SPEED_MAX (2000)        // Set the Maximum Speed in microseconds
#define ARM_VALUE (500)         // Set the Arm value in microseconds
#define SERVO_FREQ (50)         // Analog servos run at ~50 Hz updates

I2C_ESC myESC (0x40, 0, 1, SPEED_MIN, SPEED_MAX, ARM_VALUE);       // ESC_Name (I2C_address, ESC PIN, Minimum Value, Maximum Value, Default Speed, Arm Value)
I2C_ESC myESC1 (0x41, 0, 1, SPEED_MIN, SPEED_MAX, ARM_VALUE);      // ESC_Name (I2C_address, ESC PIN, Minimum Value, Maximum Value, Default Speed, Arm Value)
int oESC;                                                 // Variable for the speed sent to the ESC

void setup() {
  // Start serial port
  Serial.begin(9600);
  Serial.println("I2C Controller Test with ESC");
  /*
   * Set up the I2C based PWM/Servo extenders
   * This is only done once per Adafruit PCA9685 PWM/Servo driver
   */
  myESC.begin();
  myESC1.begin();

  int prescaleValue = myESC.readPrescale();
  int prescaleValue1 = myESC1.readPrescale();
  Serial.print(prescaleValue); Serial.println(" Initialized Prescale value for 0x40");
  Serial.print(prescaleValue1); Serial.println(" Initialized Prescale value for 0x41");

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
  myESC.arm();
  myESC1.arm();
  delay(5);                     // Wait for 5 milliseconds before showing the LED visual for Arming confirmation
  digitalWrite(LED_PIN, HIGH);  // LED High Once Armed

  prescaleValue = 0;
  prescaleValue1 = 0;
  Serial.println(" read Current Prescale value cleared");
  prescaleValue = myESC.readPrescale();
  prescaleValue1 = myESC.readPrescale();
  Serial.print(prescaleValue); Serial.println(" Current Prescale value 0x40");
  Serial.print(prescaleValue1); Serial.println(" Current Prescale value 0x41");
  delay(1000);                  // Wait for a while before starting the loop
}

void loop() {
  if (Serial.available() > 0)                             // read the value from the serial
  {
    oESC = Serial.parseInt();
    // Lets try changing the pulse frequency of the I2C PWM/Servo extender chip range 40-1000Hz
    myESC.setPWMFreq(oESC);
    myESC1.setPWMFreq(oESC);
    Serial.print("Input frequency 0x40:: ");
    Serial.println(oESC);
    Serial.print("Actual prescale 0x40:: ");
    Serial.println(myESC.readPrescale());
    Serial.print("Input frequency 0x41:: ");
    Serial.println(oESC);
    Serial.print("Actual prescale 0x41:: ");
    Serial.println(myESC1.readPrescale());
    

    delay(10); 
  }                                           // Wait for a while before restarting the loop
}
