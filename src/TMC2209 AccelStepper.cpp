// programme modifié par Phil Dav le 13/11/23
#include <Arduino.h>
/*
    Controlling two stepper with the AccelStepper library

     by Dejan, https://howtomechatronics.com
 https://howtomechatronics.com/tutorials/arduino/stepper-motors-and-arduino-the-ultimate-guide/
*/

#include <AccelStepper.h>

// Define the stepper motor and the pins that is connected to
AccelStepper stepper1(1, 2, 3); // (Typeof driver: with 2 pins, STEP, DIR)
AccelStepper stepper2(1, 4, 5);

void setup()
{

  stepper1.setMaxSpeed(40000);    // Set maximum speed value for the stepper
  stepper1.setAcceleration(1000); // Set acceleration value for the stepper
  stepper1.setCurrentPosition(0); // Set the current position to 0 steps

  stepper2.setMaxSpeed(1000);
  stepper2.setAcceleration(500);
  stepper2.setCurrentPosition(0);
}

void loop()
{

  stepper1.moveTo(30000);   // Axe dec "63000" axe "33000" Définir le mouvement souhaité : 800 pas (en résolution d'un quart de pas, cela représente une rotation))
  stepper1.runToPosition(); // Moves the motor to target position w/ acceleration/ deceleration and it blocks until is in position

  stepper2.moveTo(800);
  stepper2.runToPosition();

  // Move back to position 0, using run() which is non-blocking - both motors will move at the same time
  stepper1.moveTo(0);
  stepper2.moveTo(0);
  while (stepper1.currentPosition() != 0 || stepper2.currentPosition() != 0)
  {
    stepper1.run(); // Move or step the motor implementing accelerations and decelerations to achieve the target position. Non-blocking function
    stepper2.run();
    //
    //
  }
}