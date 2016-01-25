/* (C) 2014 by MSchmidl

  Required Connections as defined by OctoWS2811
  ---------------------------------------------
    pin 2:  LED Strip #1    OctoWS2811 drives 8 LED Strips.
    pin 14: LED strip #2    All 8 are the same length.
    pin 7:  LED strip #3
    pin 8:  LED strip #4    A 100 ohm resistor should used
    pin 6:  LED strip #5    between each Teensy pin and the
    pin 20: LED strip #6    wire to the LED strip, to minimize
    pin 21: LED strip #7    high frequency ringining & noise.
    pin 5:  LED strip #8
    pin 15 & 16 - Connect together, but do not use
    pin 4 - Do not use
    pin 3 - Do not use as PWM.  Normal use is ok.
*/

#include <OctoWS2811.h>

const int ledsPerStrip = 120; // adopt these value to your needs

DMAMEM int displayMemory[ledsPerStrip*6];
int drawingMemory[ledsPerStrip*6];

const int ledPin = LED_BUILTIN; // used to indicate a packet start

int pixelIndex = 0;
const int stateR = 0;
const int stateG = 1;
const int stateB = 2;
int state = stateR;
unsigned long pixelColor = 0;

const int config = WS2811_RGB | WS2811_800kHz;

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config);

void setup() {
  pinMode(ledPin, OUTPUT);
  leds.begin();
  for (int i=0; i < 8*ledsPerStrip; i++){
    leds.setPixel(i, 0x0F0000); // all red
  }
  leds.show();
  Serial.begin(9600); // parameter does not matter - USB is always 12 Mbit/sec
}


void loop() {
  digitalWrite(ledPin, LOW);   // set the LED off
  if (Serial.available()) {
    byte incomingByte = Serial.read();  // will not be -1
    switch (incomingByte) {
      case 1: // packet state indicator used be GLEDIATOR
        digitalWrite(ledPin, HIGH);   // set the LED on
        leds.show();                  // show the current data
        pixelIndex = 0;               // restart with new data
        state = 0;
        break;
      default: // all values !=1 are payload data
        switch (state) {
          case stateR:
            pixelColor = long(incomingByte) & 0xFF;
            state = stateG;
            break;
          case stateG:
            pixelColor <<= 8;
            pixelColor |= long(incomingByte) & 0xFF;
            state = stateB;
            break;
          case stateB:
            pixelColor <<= 8;
            pixelColor |= long(incomingByte) & 0xFF;
            if (pixelIndex < 8*ledsPerStrip) {
              leds.setPixel(pixelIndex++, pixelColor);
            }
            state = stateR;
            break;
          default:
            state = 0;
        } // switch state
    } // switch incomingByte
  } // if available
}

