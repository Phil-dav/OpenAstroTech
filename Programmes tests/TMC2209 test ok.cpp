// programme modifié par Phil Dav le 13/11/23
#include <Arduino.h>
/*
 *   Basic example code for controlling a stepper without library
 *
 *   by Dejan, https://howtomechatronics.com
      https://howtomechatronics.com/tutorials/arduino/stepper-motors-and-arduino-the-ultimate-guide/
 */

// defines pins
#define stepPin 2
#define dirPin 3
int nbpas = 3000;
void setup()
{
  // Sets the two pins as Outputs
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

}
void loop()
{
  digitalWrite(dirPin, HIGH); // Enables the motor to move in a particular direction
  // Makes 200 pulses for making one full cycle rotation
  for (int x = 0; x < nbpas*10; x++)
  {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1000); // by changing this time delay between the steps we can change the rotation speed
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1000);
  }
  delay(1000); // One second delay

  digitalWrite(dirPin, LOW); // Changes the rotations direction
  // Makes 400 pulses for making two full cycle rotation
  for (int x = 0; x < nbpas*10; x++)
  {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(200);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(200);
  }
  delay(1000);
}