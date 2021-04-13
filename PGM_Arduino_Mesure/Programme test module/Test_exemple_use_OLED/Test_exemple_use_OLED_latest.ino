#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define ENC_SW_PIN         2
byte enc_clk, enc_clk_old;
byte enc_switch, enc_switch_old;
String banc;


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET 4
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
int selected=1;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode (ENC_SW_PIN,INPUT_PULLUP);
  enc_switch_old = digitalRead(ENC_SW_PIN);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  
  display.setCursor(0, 10);
  // Display static text
 

}

void buildmenu(){
  display.setTextColor(WHITE);
  display.println("Menu Principal");
  display.setTextColor(BLACK,WHITE);
  display.println("Banc de test dechets");
  display.setTextColor(WHITE);
  display.println("Banc de test carton");
  display.println("Banc de teste imprime");
  display.println("Banc de test sans spe");
  //après choix avec encodeur rotatoire
  banc="";
}

void submenu(){
  //1er etape
  display.setTextColor(WHITE);
  display.println("Le bluetooth est-il connecte?");
  display.setTextColor(BLACK,WHITE);
  display.println("Oui");

  enc_switch = digitalRead(ENC_SW_PIN);
  if((enc_switch_old == 1) && (enc_switch == 0)) { // 1->0 transition
   Serial.println("SWITCH is PRESSED");
   display.clearDisplay();
  // mySerial.print(banc);
   delay(1000);
  }
  enc_switch_old = enc_switch;
  

 
  /*//2eme etape
   
       
   display.setTextColor(WHITE);
   display.println("Etes vous prets?");
   display.setTextColor(BLACK,WHITE);
   display.println("Oui");
   display.display();


  //4eme-7eme etape
  
  display.setTextColor(WHITE);
  display.println("Test en compression");
  display.println("Rayon de courbure: 1cm");
  display.println("Placer le capteur");
  display.setTextColor(BLACK,WHITE);
  display.println("START");
  mySerial.print("Rayon de courbure: 1cm");

  
  //8eme etape
  
  display.setTextColor(BLACK,WHITE);
  display.println("STOP");
  mySerial.print("Stop");
  
  //repetition
  
  display.setTextColor(WHITE);
  display.println("Test en compression");
  display.println("Rayon de courbure: 1.5cm");
  display.println("Placer le capteur");
  display.setTextColor(BLACK,WHITE);
  display.println("START");
  mySerial.print("Rayon de courbure: 1.5cm");

  //8eme etape
  display.setTextColor(BLACK,WHITE);
  display.println("STOP");
  mySerial.print("Stop");

  //repetition
  
  display.setTextColor(WHITE);
  display.println("Test en compression");
  display.println("Rayon de courbure: 2cm");
  display.println("Placer le capteur");
  display.setTextColor(BLACK,WHITE);
  display.println("START");
  mySerial.print("Rayon de courbure: 2cm");

  //8eme etape
  display.setTextColor(BLACK,WHITE);
  display.println("STOP");
  mySerial.print("Stop");

  //repetition
  
  display.setTextColor(WHITE);
  display.println("Test en compression");
  display.println("Rayon de courbure: 3cm");
  display.println("Placer le capteur");
  display.setTextColor(BLACK,WHITE);
  display.println("START");
  mySerial.print("Rayon de courbure: 3cm");

  //8eme etape
  display.setTextColor(BLACK,WHITE);
  display.println("STOP");
  mySerial.print("Stop");

  //repetition
  
  display.setTextColor(WHITE);
  display.println("Test en compression");
  display.println("Rayon de courbure: 4cm");
  display.println("Placer le capteur");
  display.setTextColor(BLACK,WHITE);
  display.println("START");
  mySerial.print("Rayon de courbure: 4cm");

  //8eme etape
  display.setTextColor(BLACK,WHITE);
  display.println("STOP");
  mySerial.print("Stop");

  //tension

  //4eme-7eme etape
  
  display.setTextColor(WHITE);
  display.println("Test en tension");
  display.println("Rayon de courbure: 1cm");
  display.println("Placer le capteur");
  display.setTextColor(BLACK,WHITE);
  display.println("START");
  mySerial.print("Rayon de courbure: 1cm");
  
  //8eme etape
  display.setTextColor(BLACK,WHITE);
  display.println("STOP");
  mySerial.print("Stop");

  //repetition
  
  display.setTextColor(WHITE);
  display.println("Test en tension");
  display.println("Rayon de courbure: 1.5cm");
  display.println("Placer le capteur");
  display.setTextColor(BLACK,WHITE);
  display.println("START");
  mySerial.print("Rayon de courbure: 1.5cm");

  //8eme etape
  display.setTextColor(WHITE);
  display.println("STOP");
  mySerial.print("Stop");


  //repetition
  
  display.setTextColor(WHITE);
  display.println("Test en tension");
  display.println("Rayon de courbure: 2cm");
  display.println("Placer le capteur");
  display.setTextColor(BLACK,WHITE);
  display.println("START");
  mySerial.print("Rayon de courbure: 2cm");

  //8eme etape
  display.setTextColor(BLACK,WHITE);
  display.println("STOP");
  mySerial.print("Stop");

  //repetition
  
  display.setTextColor(WHITE);
  display.println("Test en tension");
  display.println("Rayon de courbure: 3cm");
  display.println("Placer le capteur");
  display.setTextColor(BLACK,WHITE);
  display.println("START");
  mySerial.print("Rayon de courbure: 3cm");

  //8eme etape
  display.setTextColor(BLACK,WHITE);
  display.println("STOP");
  mySerial.print("Stop");

  //repetition
  
  display.setTextColor(WHITE);
  display.println("Test en tension");
  display.println("Rayon de courbure: 4cm");
  display.println("Placer le capteur");
  display.setTextColor(BLACK,WHITE);
  display.println("START");
  mySerial.print("Rayon de courbure: 4cm");

  //8eme etape
  display.setTextColor(BLACK,WHITE);
  display.println("STOP");
  mySerial.print("Stop");*/

  
  
  
  
}


void loop() {
  // put your main code here, to run repeatedly:
  submenu();
   
}
