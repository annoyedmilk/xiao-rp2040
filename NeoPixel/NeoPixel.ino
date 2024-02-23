/*
 * Project: NeoPixel Color Wipe Effect
 * Author: annoyedmilk
 *
 * Description:
 * This Arduino sketch controls a single NeoPixel LED, cycling it through a spectrum of colors
 * using a color wipe effect. It demonstrates the use of Adafruit_NeoPixel library to create
 * smooth color transitions. The sketch includes functionality to control the power and color
 * of the LED via specified GPIO pins.
 * Revision History:
 * - Version 1.0: Initial release
 */

#include <Adafruit_NeoPixel.h>

// Define pin numbers and constants
const int PowerPin = 11;
const int RGBControlPins[] = {17, 16, 25}; // R, G, B control pins
const int PixelPin = 12;
const int NumPixels = 1;

Adafruit_NeoPixel pixels(NumPixels, PixelPin, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin(); // Initialize the NeoPixel library

  // Set up the power and individual RGB control pins as outputs
  pinMode(PowerPin, OUTPUT);
  pinMode(RedPin, OUTPUT);
  pinMode(GreenPin, OUTPUT);
  pinMode(BluePin, OUTPUT);

  digitalWrite(RedPin, HIGH); // Initially turn off the Red control pin
  digitalWrite(GreenPin, HIGH); // Initially turn off the Green control pin
  digitalWrite(BluePin, HIGH); // Initially turn off the Blue control pin
  digitalWrite(PowerPin, HIGH); // Turn on the power pin to power up the NeoPixel
}

void loop() {
  colorWipe(); // Execute the Color Wipe effect
}

// Implement the Color Wipe effect across the NeoPixel
void colorWipe() {
  for (int i = 0; i < 256; i++) {
    pixels.setPixelColor(0, Wheel(i & 255));
    pixels.show();
    delay(10); // Control the speed of the color transition
  }
}

// Generate a color from the color wheel
// Input: Value from 0 to 255 representing the color position on the color wheel
// Output: 32-bit color value
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
    WheelPos -= 170;
    return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}
