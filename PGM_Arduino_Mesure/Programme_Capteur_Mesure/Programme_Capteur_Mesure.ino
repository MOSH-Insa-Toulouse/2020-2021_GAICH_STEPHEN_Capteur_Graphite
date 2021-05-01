// Variables pour éviter le delay 
unsigned long previousMillis = 0;        // will store last time LED was updated

// Variable pour cadencer l'acquisition
const long interval = 1000;           // interval at which to blink (milliseconds)



//Bluetooth
#include <SoftwareSerial.h>
#define rxPin 6 // Correspondant à la broche tx du module bluetooth
#define txPin 7 // Correspondant à la broche Rx du module bluetooth
#define baudrate 9600 
SoftwareSerial mySerial(rxPin ,txPin); //Definition du software serial

// Pin pour mesure de la tension du capteur
int capteurgraphitePin = 0;

void setup() {
  mySerial.begin(baudrate); // Initialiser le port bluetooth
  Serial.begin(baudrate); // Initialiser le port série
}


  
void loop() {
  unsigned long currentMillis = millis ();
  
   if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    byte Vadc = map(analogRead(capteurgraphitePin),0,1024,0,255); // permet de coder la mesure sur 1 byte
    Serial.println(Vadc); // Afficher sur le port série la valeur de la tension mesuré en bytes
    mySerial.write(Vadc); // Envoyer sur le port bluetooth la valeur acquise
  }

}
