// programme modifié par Phil Dav le 13/11/23
#include <Arduino.h>
#include <TMCStepper.h>     // TMCstepper - https://github.com/teemuatlut/TMCStepper
#include <SoftwareSerial.h> // Série logicielle pour l'UART à TMC2209 - https://www.arduino.cc/en/Reference/softwareSerial
#include <Streaming.h>      // Pour la sortie de débogage série - https://www.arduino.cc/reference/en/libraries/streaming/

#define EN_PIN 2            // Activer - PURPLE
#define DIR_PIN 3           // Direction - WHITE
#define STEP_PIN 4          // Pas - ORANGE
#define SW_SCK 5            // Horloge esclave logicielle (SCK)
#define SW_TX 6             // Réception SoftwareSerial
#define SW_RX 7             // LogicielBroche de transmission série
#define DRIVER_ADDRESS 0b00 // TMC2209 Adresse du driver selon MS1 et MS2
#define R_SENSE 0.11f       // La série SilentStepStick utilise 0.11... tout comme mon fysetc TMC2209 (?)

SoftwareSerial SoftSerial(SW_RX, SW_TX);                        // Assurez-vous de connecter RX à TX et TX à RX entre les deux appareils
                                                                // fonctionne avec TX uniquement connecté
TMC2209Stepper TMCdriver(&SoftSerial, R_SENSE, DRIVER_ADDRESS); // Création du driver TMC

int accel;
long maxSpeed;
int speedChangeDelay;
bool dir = false;

//== Setup ===============================================================================

void setup()
{

  Serial.begin(11520);          // initialiser la série matérielle pour le débogage
  SoftSerial.begin(11520);      // initialiser la série du logiciel pour le contrôle du moteur UART
  TMCdriver.beginSerial(11520); // initialiser UART

  pinMode(EN_PIN, OUTPUT); // Set pinmodes
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  digitalWrite(EN_PIN, LOW); // Enable TMC2209 board

  TMCdriver.begin();          // UART: Initialise SW UART (si sélectionné) avec un débit en bauds par défaut de 115200
  TMCdriver.toff(5);          // Active le pilote dans le logiciel
  TMCdriver.rms_current(500); // Régler le courant RMS du moteur
  TMCdriver.microsteps(128);  // Définir des micropas

  TMCdriver.en_spreadCycle(false);
  TMCdriver.pwm_autoscale(true); // Nécessaire pour la furtivité
}

//== Loop =================================================================================

void loop()
{

  accel = 1000;           // Montant d'augmentation/diminution de la vitesse
  maxSpeed = 45000;       // Vitesse maximale à atteindre
  speedChangeDelay = 100; // Délai entre les changements de vitesse

  for (long i = 0; i <= maxSpeed; i = i + accel)
  {                       // Accélérer jusqu'à maxSpeed
    TMCdriver.VACTUAL(i); // Régler la vitesse du moteur
    Serial << TMCdriver.VACTUAL() << endl;
    delay(50);
  }

  for (long i = maxSpeed; i >= 0; i = i - accel)
  { // Réduire la vitesse à zéro
    TMCdriver.VACTUAL(i);
    Serial << TMCdriver.VACTUAL() << endl;
    delay(50);
  }

  dir = !dir;           // DIRECTION INVERSE
  TMCdriver.shaft(dir); // DÉFINIR LA DIRECTION
}