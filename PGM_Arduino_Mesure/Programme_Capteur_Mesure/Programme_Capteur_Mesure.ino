
//Bluetooth
#include <SoftwareSerial.h>
#define rxPin 6 
#define txPin 7 
#define baudrate 9600
SoftwareSerial mySerial(rxPin ,txPin); //Definition du software serial

//Encodeur rotatoire
#define encoder0PinA  2  //CLK Output A Do not use other pin for clock as we are using interrupt
#define encoder0PinB  4  //DT Output B
#define Switch 5 // Switch connection if available

//OLED
#include <Wire.h>
#include <string.h>
//#undef int
#include <stdio.h>
#include <Adafruit_GFX.h>
#include <Adafruit_GrayOLED.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>
#include <Adafruit_SSD1306.h>
#include <splash.h>

int OLEDPinSCL = 4;
int OLEDPinSDA = 5;


int capteurgraphitePin = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(OLEDPinSCL, OUTPUT);
  pinMode(OLEDPinSDA, OUTPUT);
  pinMode(rxPin,INPUT);
  pinMode(txPin,OUTPUT); 
  mySerial.begin(baudrate);
  Serial.begin(baudrate);

  //encodeur rotatoire
 /* pinMode(encoder0PinA, INPUT); 
  digitalWrite(encoder0PinA, HIGH);       // turn on pullup resistor

  pinMode(encoder0PinB, INPUT); 
  digitalWrite(encoder0PinB, HIGH);       // turn on pullup resistor

  attachInterrupt(0, doEncoder, RISING); // encoder pin on interrupt 0 - pin2 .........doEncoder quand il se passe qqch sur le pin 2

  Serial.begin (9600);
  Serial.println("start");          */      // a personal quirk
  
}

/*void doEncoder() {
  if (digitalRead(encoder0PinB)==HIGH) {
    encoder0Pos++;
  } else {
    encoder0Pos--;
  }
}
*/

float getVoltage(int pin){
  
  return (analogRead(pin)*(5/1024.0)); //converting from a 0 to 1023 digital range
                                        // to 0 to 5 volts (each 1 reading equals ~ 5 millivolts
}
  
void loop() {
  
  float voltage = getVoltage(capteurgraphitePin);
  String reading = String(voltage, 5);
  Serial.println(reading);
  mySerial.println(reading);
  delay(100);
  /*Serial.print("Position:");
  Serial.println (encoder0Pos, DEC);  //Angle = (360 / Encoder_Resolution) * encoder0Pos*/
}
