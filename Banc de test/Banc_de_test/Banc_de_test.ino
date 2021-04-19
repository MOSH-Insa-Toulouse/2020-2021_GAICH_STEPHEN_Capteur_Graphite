#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Encoder_Polling_V2.h"

// Variables pour éviter le delay 
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change:
const long interval = 1000;           // interval at which to blink (milliseconds)

float R1= 100000;
float R2= 1000;
float R3= 100000;
float R5= 10000;
float Vcc= 5;

int capteurgraphitePin = 0;


//Bluetooth
#include <SoftwareSerial.h>
#define rxPin 6 // Correspondant à la broche tx du module bluetooth
#define txPin 7 // Correspondant à la broche Rx du module bluetooth
#define baudrate 9600 
SoftwareSerial mySerial(rxPin ,txPin); //Definition du software serial

// Rotary Encoder Module connections
const int pin_A = 3;  // Encoder input pins
const int pin_B = 4;
int compteur=0;
long lastdebouncetime=0;
long debouncedelay=100;



#define ENC_SW_PIN         2
byte enc_clk, enc_clk_old;
byte enc_switch, enc_switch_old;
String banc;


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET 4
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  encoder_begin();  // Start the library
  attach_encoder(0, pin_A, pin_B);  // Attach an encoder to pins A and B
  mySerial.begin(baudrate);
  pinMode (ENC_SW_PIN,INPUT_PULLUP);
  enc_switch_old = digitalRead(ENC_SW_PIN);
  Serial.println(enc_switch_old);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 10);
  // Display static text
  display.display();

 
}


void displaymessage(String message, String highlighted){
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 10);
  display.setTextColor(WHITE);
  display.println(message);
  display.setTextColor(BLACK,WHITE);
  display.println(highlighted);
  display.display();
  
}

void displaymessagemesure(float mesure, String highlighted){
  display.clearDisplay();
  display.setTextSize(3);
  display.setCursor(0, 10);
  display.setTextColor(WHITE);
  display.print(mesure);
  display.println("V");
  display.setTextSize(1);
  display.setTextColor(BLACK,WHITE);
  display.println(highlighted);
  display.display();
  
}

void displaymessagecompressionrayon(String message){
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 10);
  display.setTextColor(WHITE);
  display.println("Test en compression");
  display.println("Rayon de courbure:");
  display.println(message);
  display.println("Placer le capteur");
  display.setTextColor(BLACK,WHITE);
  display.println("START");
  //mySerial.print("Test en compression, Rayon de courbure:"+ message);
  display.display();
  
}

void displaymessagetensionrayon(String message){
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 10);
  display.setTextColor(WHITE);
  display.println("Test en tension");
  display.println("Rayon de courbure:");
  display.println(message);
  display.println("Placer le capteur");
  display.setTextColor(BLACK,WHITE);
  display.println("START");
  display.display();
  
}

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
   display.println("Banc de test sans spe");
   display.display();
  }
  if(choix==1){
   display.setTextColor(WHITE);
   display.println("Banc de test dechets");
   display.setTextColor(BLACK,WHITE);
   display.println("Banc de test carton");
   display.setTextColor(WHITE);
   display.println("Banc de teste imprime");
   display.println("Banc de test sans spe");
   display.display();
  }
  if(choix==2){
   display.setTextColor(WHITE);
   display.println("Banc de test dechets");
   display.println("Banc de test carton");
    display.setTextColor(BLACK,WHITE);
   display.println("Banc de teste imprime");
   display.setTextColor(WHITE);
   display.println("Banc de test sans spe");
   display.display();
  }
  if(choix==3){
   display.setTextColor(WHITE);
   display.println("Banc de test dechets");
   display.println("Banc de test carton");
   display.println("Banc de teste imprime");
   display.setTextColor(BLACK,WHITE);
   display.println("Banc de test sans spe");
   display.display();
  }
  
  //après choix avec encodeur rotatoire
  
}
void buildsubmenu(int choix){
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 10);
  display.setTextColor(WHITE);
  display.println("Test");
  if(choix==0){
   display.setTextColor(BLACK,WHITE);
   display.println("1cm");
   display.setTextColor(WHITE);
   display.println("1.5cm");
   display.println("2cm");
   display.println("3cm");
   display.println("4cm");
   display.display();
  }
  if(choix==1){
   display.setTextColor(WHITE);
   display.println("Banc de test dechets");
   display.setTextColor(BLACK,WHITE);
   display.println("Banc de test carton");
   display.setTextColor(WHITE);
   display.println("Banc de teste imprime");
   display.println("Banc de test sans spe");
   display.display();
  }
  if(choix==2){
   display.setTextColor(WHITE);
   display.println("Banc de test dechets");
   display.println("Banc de test carton");
    display.setTextColor(BLACK,WHITE);
   display.println("Banc de teste imprime");
   display.setTextColor(WHITE);
   display.println("Banc de test sans spe");
   display.display();
  }
  if(choix==3){
   display.setTextColor(WHITE);
   display.println("Banc de test dechets");
   display.println("Banc de test carton");
   display.println("Banc de teste imprime");
   display.setTextColor(BLACK,WHITE);
   display.println("Banc de test sans spe");
   display.display();
  }
  
  //après choix avec encodeur rotatoire
  
}

void submenu1(){
  //1er etape
  //delay(100);
  //displaymessage("Le bluetooth est-il connecte?","Oui");
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 10);
  display.setTextColor(WHITE);
  display.println("Le bluetooth est-il connecte?");
  display.setTextColor(BLACK,WHITE);
  display.println("Oui");
  display.display();
  enc_switch=digitalRead(ENC_SW_PIN);
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
/*
  display.println("Test en compression");
  display.println("Rayon de courbure: 1cm");
  display.setTextColor(BLACK,WHITE);
  display.println("START");
  display.display();
  displaymessagecompressionrayon("1cm");
  buttonclicked();
  mesure();
  displaymessagecompressionrayon("1.5cm");
  buttonclicked();
  mesure();
  displaymessagecompressionrayon("2cm");
  buttonclicked();
  mesure();
  displaymessagecompressionrayon("3cm");
  buttonclicked();
  mesure();
  displaymessagecompressionrayon("4cm");
  buttonclicked();
  mesure();
  displaymessagetensionrayon("1cm");
  buttonclicked();
  mesure();
  displaymessagetensionrayon("1.5cm");
  buttonclicked();
  mesure();
  displaymessagetensionrayon("2cm");
  buttonclicked();
  mesure();
  displaymessagetensionrayon("3cm");
  buttonclicked();
  mesure();
  displaymessagetensionrayon("4cm");
  buttonclicked();
  mesure();*/
}

void submenu2(){
  //1er etape
  displaymessage("Le bluetooth est-il connecte?","Oui");
  enc_switch=digitalRead(ENC_SW_PIN);
  buttonclicked();
  displaymessage("Etes vous prets?","Oui");
  buttonclicked();
  displaymessagecompressionrayon("1cm");
  buttonclicked();
  mesure();
  displaymessagecompressionrayon("2cm");
  buttonclicked();
  mesure();
  displaymessagecompressionrayon("3cm");
  buttonclicked();
  mesure();
  displaymessagecompressionrayon("4cm");
  buttonclicked();
  mesure();
  displaymessagetensionrayon("1cm");
  buttonclicked();
  mesure();
  displaymessagetensionrayon("1.5cm");
  buttonclicked();
  mesure();
  displaymessagetensionrayon("2cm");
  buttonclicked();
  mesure();
  displaymessagetensionrayon("3cm");
  buttonclicked();
  mesure();
  displaymessagetensionrayon("4cm");
  buttonclicked();
  mesure();
}

void submenu3(){
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

int mesure(){
  while(enc_switch ==1){
    enc_switch=digitalRead(ENC_SW_PIN);
    unsigned long currentMillis = millis ();
   if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
   float voltage = getVoltage(capteurgraphitePin);
   byte Vadc = map(analogRead(capteurgraphitePin),0,1024,0,255);
    /*String reading = String(voltage, 5);*/
    //Serial.println(voltage);
    displaymessagemesure(voltage,"STOP");
    mySerial.write(Vadc);
   }
    if((enc_switch_old == 1) && (enc_switch == 0)) {// 1->0 transition
      delay(300);
      enc_switch=enc_switch_old;
      return 1;
    }
  }
  
}

float getVoltage(int pin){
  return (analogRead(pin)*(5/1024.0)); //converting from a 0 to 1023 digital range
                                        // to 0 to 5 volts (each 1 reading equals ~ 5 millivolts
}

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
    if(compteurmenu==0){
    enc_switch = enc_switch_old;   
    }
    return 1;

    }
  }
}


void loop() {
  // put your main code here, to run repeatedly
 /* buildmenu(0);
 enc_switch=digitalRead(ENC_SW_PIN);
  while(enc_switch ==1){
  enc_switch=digitalRead(ENC_SW_PIN);
  Serial.println(banc);
  int dir_0 = encoder_data(0);  // First encoder
  if(dir_0!=0){
  if(millis()-lastdebouncetime>debouncedelay){
    lastdebouncetime=millis();
    compteur=compteur+1;
    Serial.println(compteur);
  }
  }
  if(compteur==4){
    compteur=compteur-4;
  }
  buildmenu(compteur);

  if((enc_switch_old == 1) && (enc_switch == 0)) {// 1->0 transition
    delay(300);
    enc_switch=enc_switch_old;
    Serial.println(compteur);
    if(compteur== 0){
      banc="Banc de test dechets";
      Serial.println(banc);
    }
    if(compteur== 1){
      banc="Banc de test carton";
    }
    if(compteur== 2){
      banc="Banc de teste imprime";
    }    
    if(compteur== 3){
      banc="Banc de test sans spe";
    }
  }
  
  }*/
  /*mainmenu();
  Serial.print("here");*/
  mainmenu();
  submenu3();

}
