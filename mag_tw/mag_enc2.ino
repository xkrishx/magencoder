#include "ArduPID.h"
#include <AS5145.h>

ArduPID myController;
AS5145 myAS5145(9);
long value;
double input;
double output;

// Arbitrary setpoint and gains - adjust these as fit for your project:
double setpoint = 150;
double p = 4;
double i = 0.7;
double d = 0.25;

void setup()
{
  Serial.begin(9600);
  myController.begin(&input, &output, &setpoint, p, i, d);

  // myController.reverse()               // Uncomment if controller output is "reversed"
  // myController.setSampleTime(10);      // OPTIONAL - will ensure at least 10ms have past between successful compute() calls
 // myController.setOutputLimits(0, 255);
  // myController.setBias(255.0 / 2.0);
  myController.setWindUpLimits(-10, 10); // Groth bounds for the integral term to prevent integral wind-up
  
  myController.start();
  // myController.reset();               // Used for resetting the I and D terms - only use this if you know what you're doing
  // myController.stop();                // Turn off the PID controller (compute() will not do anything until start() is called)
}




void loop()
{
   value= myAS5145.pwm_degrees();
  input = map(value, 0, 4095, 0, 255); // Replace with sensor feedback

  myController.compute();
  myController.debug(&Serial, "myController", PRINT_INPUT    | // Can include or comment out any of these terms to print
                                              PRINT_OUTPUT   | // in the Serial plotter
                                              PRINT_SETPOINT |
                                              PRINT_BIAS     |
                                              PRINT_P        |
                                              PRINT_I        |
                                              PRINT_D);
  
  analogWrite(11, output); // Replace with plant control signal
}