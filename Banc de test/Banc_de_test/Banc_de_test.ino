#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

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
const int PinSW=2;   // Rotary Encoder Switch
const int PinDT=4;    // DATA signal
const int PinCLK=3;    // CLOCK signal

// Variables to debounce Rotary Encoder
long TimeOfLastDebounce = 0;
int DelayofDebounce = 0.1;

// Store previous Pins state
int PreviousCLK;   
int PreviousDATA;

int displaycounter=0; // Store current counter value

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
  mySerial.begin(baudrate);
  PreviousCLK=digitalRead(PinCLK);
  PreviousDATA=digitalRead(PinDT);
  pinMode (ENC_SW_PIN,INPUT_PULLUP);
  enc_switch_old = digitalRead(ENC_SW_PIN);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  
  display.setCursor(0, 10);

  // Display static text
 

}

void check_rotary() {

 if ((PreviousCLK == 0) && (PreviousDATA == 1)) {
    if ((digitalRead(PinCLK) == 1) && (digitalRead(PinDT) == 0)) {
      displaycounter++;
       Serial.println(displaycounter);
    }
    if ((digitalRead(PinCLK) == 1) && (digitalRead(PinDT) == 1)) {
      displaycounter--;
       Serial.println(displaycounter);
    }
  }

if ((PreviousCLK == 0) && (PreviousDATA == 0)) {
    if ((digitalRead(PinCLK) == 1) && (digitalRead(PinDT) == 0)) {
      displaycounter++;
       Serial.println(displaycounter);
    }
    if ((digitalRead(PinCLK) == 1) && (digitalRead(PinDT) == 1)) {
      displaycounter--;
           Serial.println(displaycounter);
    }
  }
           
 }

void displaymessage(String message, String highlighted){
  delay(100);
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
   banc="Banc de test dechets";
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
   banc="Banc de test carton";
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
   banc="Banc de teste imprime";
   display.display();
  }
  if(choix==3){
   display.setTextColor(WHITE);
   display.println("Banc de test dechets");
   display.println("Banc de test carton");
   display.println("Banc de teste imprime");
   display.setTextColor(BLACK,WHITE);
   display.println("Banc de test sans spe");
   banc="Banc de test sans spe";
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
  mesure();
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
  displaymessage("Le bluetooth est-il connecte?","Oui");
  enc_switch=digitalRead(ENC_SW_PIN);
  buttonclicked();
  displaymessage("Etes vous prets?","Oui");
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
   //byte Vadc = map(analogRead(capteurgraphitePin),0,1024,0,255);
    /*String reading = String(voltage, 5);*/
    //Serial.println(voltage);
    displaymessagemesure(voltage,"STOP");
    //mySerial.write(Vadc);
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



void loop() {
  // put your main code here, to run repeatedly
   if ((millis() - TimeOfLastDebounce) > DelayofDebounce) {
    
    check_rotary(); // Rotary Encoder check routine below
    if(displaycounter==3){
      displaycounter= displaycounter-4;
    }
    PreviousCLK=digitalRead(PinCLK);
    PreviousDATA=digitalRead(PinDT);
    //buildmenu(displaycounter);
    TimeOfLastDebounce=millis();  // Set variable to current millis() timer
  }
  //buildmenu(2);

}
