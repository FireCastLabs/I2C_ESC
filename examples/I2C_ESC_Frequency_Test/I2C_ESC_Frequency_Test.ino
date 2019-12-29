/** 
 * This sketch is for checking frequency control over the PWM signal
 * using the serial monitor as an input for Frequency
 * Maximum input Frequency:  1600
 * Minimum input Frequency:  40
 *
 * Hardware: : 1 * Arduino compatable board 
 *           : 2 * Adafruit PCA9685 16-Channel 12-bit PWM/Servo Driver - I2C interface
**/

#include "I2C_ESC.h"
#define LED_PIN (13)            // Pin for the LED
#define SPEED_MIN (1000)        // Set the Zero throttle Speed in microseconds
#define SPEED_MAX (2000)        // Set the Maximum Speed in microseconds
#define ARM_VALUE (500)         // Set the Arm value in microseconds
#define SERVO_FREQ (50)         // Analog servos run at ~50 Hz updates

int oFrequency;                 // Variable for the frequency sent to the ESC

/*
 * Instantiate the PWM extenders
 * ESC_Name (I2C_address, Minimum Value, Maximum Value, Default Speed, Arm Value)
 * 8 ESC/motors per I2C PWM/Servo extender, 16 signals per extender 2 lines per ESC with 1 for motor and 1 for reverse pin
 */
I2C_ESC myESC (0x40, SPEED_MIN, SPEED_MAX, ARM_VALUE);
I2C_ESC myESC1 (0x41, SPEED_MIN, SPEED_MAX, ARM_VALUE);

void setup()
{
  // Start serial port
  Serial.begin(9600);
  Serial.println("I2C Controller Test with ESC");

  /*
   * Set up the I2C based PWM/Servo extenders
   * begin() calls the wire.begin()
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
  myESC1.setOscillatorFrequency(25000000);

  /*
   * Set the analog servo PWM frequency
   * alternativly you could set this using the prescale 50Hz is a prescale of about ### (depending on the internal oscillator frequency)
   * This is only done once per Adafruit PCA9685 PWM/Servo driver
   */
  myESC.setPWMFreq(SERVO_FREQ);
  myESC1.setPWMFreq(SERVO_FREQ);

  delay(10); // Set a small delay to allow the PCA9685 chips time to set their frequency

  pinMode(LED_PIN, OUTPUT);    // Set Pin for LED Visual Output
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

void loop()
{
  if (Serial.available() > 0)                             // read the value from the serial
  {
    oFrequency = Serial.parseInt();
    // Lets try changing the pulse frequency of the I2C PWM/Servo extender chip range 40-1000Hz
    myESC.setPWMFreq(oFrequency);
    myESC1.setPWMFreq(oFrequency);
    Serial.print("Input frequency 0x40:: ");
    Serial.println(oFrequency);
    Serial.print("Actual prescale 0x40:: ");
    Serial.println(myESC.readPrescale());
    Serial.print("Input frequency 0x41:: ");
    Serial.println(oFrequency);
    Serial.print("Actual prescale 0x41:: ");
    Serial.println(myESC1.readPrescale());

    delay(10);                                            // Wait for a while before restarting the loop
  }
}
