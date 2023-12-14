#include <Arduino.h>
// defines pins

#define stepPin 26 // carte RAMPS E0
#define dirPin 28  // carte RAMPS E0
#define VRX_PIN A0 // Broche Arduino Nano connectée à la broche VRX
#define VRY_PIN A1

int value_X = 0; // La variable pour stocker la valeur de l’axe X
int value_Y = 0;
int nbpas = 400;


    void
    setup()
{
  // Sets the two pins as Outputs
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  //Serial.begin(9600);
  //Serial.println("TMC2208 + joystick");
}

void loop()
{
  value_X = analogRead(VRX_PIN); // lecture analog X et Y analog values
  value_X = map(value_X, 0, 1023, 0, 3000);
  //Serial.println(value_X);
  //value_Y = analogRead(VRY_PIN);
  if (value_X > 1300 && value_X < 1600)
  {
    // Serial.println("Moteur stop");
    // Serial.println(value_X);
  }

  if (value_X > 0 && value_X < 1000)
  {
    digitalWrite(dirPin, LOW);
    for (int x = 0; x < 200; x++)
    {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(nbpas);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(nbpas);
    }
  }

  if (value_X > 1800 && value_X < 3000)
  {
    digitalWrite(dirPin, HIGH);
    for (int x = 0; x < 200; x++)
    {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(nbpas);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(nbpas);
    }
  }


}