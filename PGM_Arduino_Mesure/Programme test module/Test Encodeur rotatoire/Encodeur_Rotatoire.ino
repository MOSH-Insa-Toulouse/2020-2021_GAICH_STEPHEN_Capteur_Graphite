/* Read a rotary encoder with interrupts
   Encoder hooked up with common to GROUND,    encoder0PinA to pin 2, encoder0PinB to pin 4
   it doesn't matter which encoder pin you use for A or B  
*/ 

#define encoder0PinA  3  //CLK Output A Do not use other pin for clock as we are using interrupt
#define encoder0PinB  4  //DT Output B
#define Switch 2 // Switch connection if available

volatile unsigned int encoder0Pos = 0;

void setup() { 
  pinMode(encoder0PinA, INPUT); 
  digitalWrite(encoder0PinA, HIGH);       // turn on pullup resistor

  pinMode(encoder0PinB, INPUT); 
  digitalWrite(encoder0PinB, HIGH);       // turn on pullup resistor

  attachInterrupt(0, doEncoder, RISING); // encoder pin on interrupt 0 - pin2

  Serial.begin (9600);
  Serial.println("start");                // a personal quirk
} 

void loop(){
  //do some stuff here - the joy of interrupts is that they take care of themselves
  Serial.print("Position:");
  Serial.println (encoder0Pos, DEC);  //Angle = (360 / Encoder_Resolution) * encoder0Pos
}

void doEncoder() {
  if (digitalRead(encoder0PinB)==HIGH) {
    encoder0Pos++;
  } else {
    encoder0Pos--;
  }
}
