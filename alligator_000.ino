Copyright (c) <2016> <chiprobot>
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include <SoftwareSerial.h>
#include <MCP3008.h>
#include <Adafruit_NeoPixel.h>
#define PIN            5
#define NUMPIXELS      16
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
// define pin connections
#define CS_PIN 15
#define CLOCK_PIN 14
#define MOSI_PIN 13
#define MISO_PIN 12
int val1,val2;
// allocate MCP3008 pins times 2 as we have 16 analogues
MCP3008 adc1(CLOCK_PIN, MOSI_PIN, MISO_PIN, 15);
MCP3008 adc2(CLOCK_PIN, MOSI_PIN, MISO_PIN, 16);
SoftwareSerial SoleSerial(2,4); // RX, TX
void setup() { 
SoleSerial.begin(38400);
  Serial.begin(9600);
  pixels.begin();
}

void loop() {
for (int i=0; i<8; i++) {
     val1 = adc1.readADC(i);
    pixels.setPixelColor((i), pixels.Color(val1,0,0)); 
   SoleSerial.write(val1);
  }
  for (int i=0; i<8; i++) {
     val1 = adc2.readADC(i);
    pixels.setPixelColor((i+8), pixels.Color(val1,0,0));
    SoleSerial.write(val1);
  }
 pixels.show();delay(100);

 //Serial.println("");
 SoleSerial.println();
}

