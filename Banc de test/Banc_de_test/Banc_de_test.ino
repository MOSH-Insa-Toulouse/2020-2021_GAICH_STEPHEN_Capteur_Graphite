#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Encoder_Polling_V2.h"

// Variables pour éviter le delay 
unsigned long previousMillis = 0;        // will store last time LED was updated

// Variable pour cadencer l'acquisition:
const long interval = 1000;           // interval at which to blink (milliseconds)

// Pin pour mesure de la tension du capteur
int capteurgraphitePin = 0;


// Bluetooth
#include <SoftwareSerial.h>
#define rxPin 6 // Correspondant à la broche tx du module bluetooth
#define txPin 7 // Correspondant à la broche Rx du module bluetooth
#define baudrate 9600 
SoftwareSerial mySerial(rxPin ,txPin); //Definition du software serial

// Variables pour le module encodeur rotatoire 
const int pin_A = 3;  // Encoder input pins
const int pin_B = 4;
int compteur=0;
long lastdebouncetime=0;
long debouncedelay=100;
#define ENC_SW_PIN         2
byte enc_clk, enc_clk_old;
byte enc_switch, enc_switch_old;
String banc;


// Variables pour l'OLED
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET 4
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);



void setup() {
  Serial.begin(9600); // Initialiser le port série
  encoder_begin();  // Initialiser l'encodeur rotatoire
  attach_encoder(0, pin_A, pin_B);  // Attacher l'encodeur aux pins A et B
  mySerial.begin(baudrate); // Initialiser le port bluetooth
  pinMode (ENC_SW_PIN,INPUT_PULLUP); // Attacher l'intérupteur l'encodeur au pin ENC_SW_PIN
  enc_switch_old = digitalRead(ENC_SW_PIN); // Lire l'état initial de l'intérupteur de l'encodeur rotatoire
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Initialiser l'affichage
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 10);
  display.display();
 
}



// fonction qui permet de bloquer le program tant que l'intérupteur de l'encodeur n'est pas appuyé
int buttonclicked(){
   while(enc_switch ==1){
    enc_switch=digitalRead(ENC_SW_PIN);
    if((enc_switch_old == 1) && (enc_switch == 0)) {// 1->0 transition
      delay(300);
      enc_switch=enc_switch_old;
      return 1;
    }
   }
}

// fonction qui permet d'afficher toutes les choix du banc de test
// permet également de surligner une des choix en fonction de la position de l'encodeur rotatoire
// stocke dans le string banc le type de banc de test selectionné

void buildmenu(int choix){
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 10);
  display.setTextColor(WHITE);
  display.println("Menu Principal");
  if(choix==0){
   display.setTextColor(BLACK,WHITE);
   display.println("Banc de test dechets");
   display.setTextColor(WHITE);
   display.println("Banc de test carton");
   display.println("Banc de teste imprime");
   display.println("Mesure");
   display.display();
   banc="Banc de test dechets";
  }
  if(choix==1){
   display.setTextColor(WHITE);
   display.println("Banc de test dechets");
   display.setTextColor(BLACK,WHITE);
   display.println("Banc de test carton");
   display.setTextColor(WHITE);
   display.println("Banc de teste imprime");
   display.println("Mesure");
   display.display();
   banc="Banc de test carton";
  }
  if(choix==2){
   display.setTextColor(WHITE);
   display.println("Banc de test dechets");
   display.println("Banc de test carton");
    display.setTextColor(BLACK,WHITE);
   display.println("Banc de teste imprime");
   display.setTextColor(WHITE);
   display.println("Mesure");
   display.display();
   banc="Banc de test imprimé";
  }
  if(choix==3){
   display.setTextColor(WHITE);
   display.println("Banc de test dechets");
   display.println("Banc de test carton");
   display.println("Banc de teste imprime");
   display.setTextColor(BLACK,WHITE);
   display.println("Mesure");
   display.display();
   banc="Mesure";
  }
  

  
}

// permet d'afficher les textes une après l'autre pour demander à l'utilisateur si le bluetooth est connecté
// puis si l'utilisateur est pret
void submenu(){
  //1er etape
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 10);
  display.setTextColor(WHITE);
  display.println("Le bluetooth est-il connecte?");
  display.setTextColor(BLACK,WHITE);
  display.println("Oui");
  display.display();
  buttonclicked();
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 10);
  display.setTextColor(WHITE);
  display.println("Etes vous prets?");
  display.setTextColor(BLACK,WHITE);
  display.println("Oui");
  display.display();
  buttonclicked();
  mesure();
 
}

// fonction qui permet de mesurer la tension sur le pin "capteurgraphite", l'afficher sur l'OLED et l'envoyer sur le port bluetooth

int mesure(){
  while(enc_switch ==1){
    enc_switch=digitalRead(ENC_SW_PIN);
    unsigned long currentMillis = millis ();
   if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
   float voltage = getVoltage(capteurgraphitePin);
   byte Vadc = map(analogRead(capteurgraphitePin),0,1024,0,255); // permet de coder la mesure sur 1 byte
    display.clearDisplay();
    display.setTextSize(3);
    display.setCursor(0, 10);
    display.setTextColor(WHITE);
    display.print(voltage);
    display.println("V");
    display.setTextSize(1);
    display.setTextColor(BLACK,WHITE);
    display.println("STOP");
    display.display();
    mySerial.write(Vadc);
   }
    if((enc_switch_old == 1) && (enc_switch == 0)) {// 1->0 transition
      delay(300);
      enc_switch=enc_switch_old;
      return 1;
    }
  }
  
}

// fonction qui permet de lire la valeur de la tension sur le pin 'capteurgraphite'
float getVoltage(int pin){
  return (analogRead(pin)*(5/1024.0)); //converting de 0 à 1023 digital range
                                        // à 0 à 5 volts 
}

// fonction qui permet de lire en permanence la position de l'encodeur rotatoire
// et en utilisant la fonction buildmenu() permet de surligner une des choix de type de banc de test
int mainmenu(){
  int compteurmenu=0;
  buildmenu(0);
 enc_switch=digitalRead(ENC_SW_PIN);
  while(enc_switch ==1){
  enc_switch=digitalRead(ENC_SW_PIN);
  int dir_0 = encoder_data(0);  // First encoder
  if(dir_0!=0){
  if(millis()-lastdebouncetime>debouncedelay){
    lastdebouncetime=millis();
    compteurmenu=compteurmenu+1;
  }
  }
  if(compteurmenu==4){
    compteurmenu=compteurmenu-4;
  }
  buildmenu(compteurmenu);

  if((enc_switch_old == 1) && (enc_switch == 0)) {// 1->0 transition
    delay(300);
    enc_switch = enc_switch_old; 
    //Serial.write("Envoi bluetooth ici"); 
    //mySerial.print(banc);
    return 1;

    }
  }
}


void loop() {
  mainmenu();
  submenu();

}
