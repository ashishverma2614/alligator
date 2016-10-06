// Alli-gait-or Project
// https://hackaday.io/project/11154-alli-gait-or-analysis
// chiprobot.00@gmail.com
#define PIN            2
#define NUMPIXELS      1
#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#include <SoftwareSerial.h>
#include <MCP3008.h>
#define CS_PIN1    3
#define CLOCK_PIN1 4
#define MOSI_PIN1  5
#define MISO_PIN1  6

#define CS_PIN2    7
#define CLOCK_PIN2 8
#define MOSI_PIN2  9
#define MISO_PIN2  10

  int z =0,scanFlag=1,incomingByte=00,liveFlag=0; 
 int16_t adc[256];
 int16_t adc3[256];
// put pins inside MCP3008 constructor
MCP3008 adc1(CLOCK_PIN1, MOSI_PIN1, MISO_PIN1, CS_PIN1);
MCP3008 adc2(CLOCK_PIN2, MOSI_PIN2, MISO_PIN2, CS_PIN2);
//SoftwareSerial SoleSerial(10,11); // RX, TX
void setup() { 
 // SoleSerial.begin(38400);  //ie. bluetooth linking SoleSerial.println("Hello, world?");
 pixels.begin();
     pixels.setPixelColor((0), pixels.Color(255,0,0)); pixels.show();delay(200);
     pixels.setPixelColor((0), pixels.Color(0,255,0)); pixels.show();delay(200);
     pixels.setPixelColor((0), pixels.Color(0,0,255)); pixels.show();delay(200);
     pixels.setPixelColor((0), pixels.Color(0,255,0)); pixels.show();delay(200);
     pixels.setPixelColor((0), pixels.Color(255,0,0)); pixels.show();delay(200);
     pixels.setPixelColor((0), pixels.Color(0,0,0)); pixels.show();
  Serial.begin(38400);
 
}
void loop() {
    pixels.setPixelColor((0), pixels.Color(0,0,0)); pixels.show();;
    if (liveFlag==1) { live();}  
    if (Serial.available() > 0) {
         incomingByte = Serial.read();// read the incoming byte:
           if (incomingByte ==83){pixels.setPixelColor((0), pixels.Color(0,0,255)); pixels.show();scan();scanFlag=1;}//scan
           if (incomingByte ==76){pixels.setPixelColor((0), pixels.Color(255,0,00)); pixels.show();liveFlag=1;pixels.setPixelColor((0), pixels.Color(255,0,0)); pixels.show();}  //live
           if (incomingByte ==82){pixels.setPixelColor((0), pixels.Color(255,0,255)); pixels.show();liveFlag=0;pixels.setPixelColor((0), pixels.Color(0,0,0));}
     }
  delay(100);
}
void scan(){
//while (adc1.readADC(0)<0) {pixels.setPixelColor((0), pixels.Color(0,0,255)); pixels.show();}
   
 if (scanFlag==1){
 scanFlag=0;
  //int j=0;
   pixels.setPixelColor((0), pixels.Color(255,0,255)); pixels.show();
  for (int j=0; j <= 63; j++){ 
   for (int i=0; i <= 7; i++){ adc[i] = adc1.readADC(i);Serial.write(lowByte(adc[i]))  ;Serial.write(highByte(adc[i]));}
   for (int i=0; i <= 7; i++){adc3[i] = adc2.readADC(i);Serial.write(lowByte(adc3[i])) ;Serial.write(highByte(adc3[i]));}
   delay(10);
    }
  }
    pixels.setPixelColor((0), pixels.Color(0,0,0)); pixels.show();delay(200);
    pixels.setPixelColor((0), pixels.Color(255,0,255)); pixels.show();delay(200);
     pixels.setPixelColor((0), pixels.Color(0,0,0)); pixels.show();delay(200);
     pixels.setPixelColor((0), pixels.Color(255,0,255)); pixels.show();delay(200);
      pixels.setPixelColor((0), pixels.Color(0,0,0)); pixels.show();delay(200);
      pixels.setPixelColor((0), pixels.Color(255,0,255)); pixels.show();
  }

void live(){
for (int i=0; i <= 7; i++) {adc[i] = adc1.readADC(i); Serial.write(lowByte(adc[i])); Serial.write(highByte(adc[i]));}
for (int i=0; i <= 7; i++) {adc3[i] = adc2.readADC(i); Serial.write(lowByte(adc3[i])); Serial.write(highByte(adc3[i])); }
       
}

