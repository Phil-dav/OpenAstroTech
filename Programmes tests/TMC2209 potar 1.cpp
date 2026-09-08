// programme modifié par Phil Dav le 13/11/23
#include <Arduino.h>
/*
 *   Basic example code for controlling a stepper with the AccelStepper library
 *
 *   by Dejan, https://howtomechatronics.com
 */

#include <AccelStepper.h>

// Define the stepper motor and the pins that is connected to
AccelStepper stepper1(1, 2, 3); // (Type of driver: with 2 pins, STEP, DIR)

void setup()
{
  Serial.begin(9600);
  // Set maximum speed value for the stepper
  stepper1.setMaxSpeed(1000);
}

void loop()
{
  stepper1.setSpeed(analogRead(A0));
  // Step the motor with a constant speed previously set by setSpeed();
  Serial.println(analogRead(A0));
  stepper1.runSpeed();
}