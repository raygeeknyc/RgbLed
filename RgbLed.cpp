#include "RgbLed.h"

#define TEST_COLOR_CHANGE_DELAY 2000
#define RGB_CYCLE_STATE_DURATION 334

/******************************************************************************
 * Wiring/Arduino Includes
 ******************************************************************************/
extern "C" {
  // AVR LibC Includes
  #include <inttypes.h>
  #include <stdlib.h>
  #include "WConstants.h"

  // Wiring Core Includes
  #undef abs
  #include "WConstants.h"

  // Wiring Core Prototypes
  //void pinMode(uint8_t, uint8_t);
  //void digitalWrite(int, uint8_t);
}

/***
 Set the status LED to the specified color
***/
void RgbLed_::setColor(int color) {
  setRgbLedColor(data, color);
}

/**
  Return the pin setting for setting this LED's pin on or off corresponding to
  on_or_off.
***/
bool getRgbPinOn_(rgb_t &led, bool on_or_off) {
  return on_or_off?led.onState:!led.onState;
}

void setRgbLedColor(rgb_t &led, int color) {
  digitalWrite(led.redPin, getRgbPinOn_(led, color & COLOR_RED));
  digitalWrite(led.greenPin, getRgbPinOn_(led, color & COLOR_GREEN));
  digitalWrite(led.bluePin, getRgbPinOn_(led, color & COLOR_BLUE));
  led.currentColor = color;
}

/***
  Setup an RGB LED with the specified 3 pins and the on-state of high or low.
  Common anode LEDs typically set an output pin to LOW whereas common cathode
  LEDs set the output pin HIGH.
***/
void initRgbLed_(rgb_t &led, int red_pin, int green_pin, int blue_pin, bool on_state) {
 led.redPin = red_pin;
 led.greenPin = green_pin;
 led.bluePin = blue_pin;
 led.onState = on_state;
 pinMode(led.redPin, OUTPUT);     
 pinMode(led.greenPin, OUTPUT);     
 pinMode(led.bluePin, OUTPUT);
}

/***
 Cycle from the startColor through the primaries and secondaries in color-wheel order, ending up on the target color
***/
void RgbLed_::cycleFromTo(int startColor, int targetColor) {
  cycleRgbFromTo(data, startColor, targetColor);
}
void cycleRgbFromTo(rgb_t &led, int startColor, int targetColor) {
  // Really stupid way to do this
  int color = startColor;
  setRgbLedColor(led, color);
  do {
    delay(RGB_CYCLE_STATE_DURATION);
    color = nextColorInRgbSequence(color);
    // inject White into the sequence next to YELLOW
    if (targetColor == COLOR_WHITE && color == COLOR_YELLOW) color = COLOR_WHITE;
    setRgbLedColor(led, color);
  } 
  while (color != targetColor);
}

/***
 Return the next color in the wheel R-M-B-C-G|W-Y
***/
int nextColorInRgbSequence(int color) {
  if (color == COLOR_RED) return COLOR_MAGENTA;
  if (color == COLOR_MAGENTA) return COLOR_BLUE;
  if (color == COLOR_BLUE) return COLOR_CYAN;
  if (color == COLOR_CYAN) return COLOR_GREEN;
  if (color == COLOR_GREEN) return COLOR_YELLOW;
  if (color == COLOR_YELLOW) return COLOR_RED;
  if (color == COLOR_WHITE) return COLOR_YELLOW;
}

/***
 Pause for the specified duration in milliseconds, cycle the specified RGB LED
 once through the set of colors, leaving it in the current color.
***/
void RgbLed_::delayCyclingColors(int duration) {
  delayCyclingRgbColors(data, duration);
}

void delayCyclingRgbColors(rgb_t &led, int duration) {
  int savedColor = led.currentColor;
  int cycleDuration = duration / COUNT_COLOR;
  for (int i=0; i<COUNT_COLOR; i++) {
    setRgbLedColor(led, nextColorInRgbSequence(led.currentColor));
    delay(cycleDuration);
  }
  delay(duration - (cycleDuration * COUNT_COLOR));
  setRgbLedColor(led, savedColor);
}

/***
 Test each color and our cycling functions
***/
void RgbLed_::test() {
  setRgbLedColor(data, COLOR_RED);
  delay(TEST_COLOR_CHANGE_DELAY);
  setRgbLedColor(data, COLOR_GREEN);
  delay(TEST_COLOR_CHANGE_DELAY);
  setRgbLedColor(data, COLOR_BLUE);
  delay(TEST_COLOR_CHANGE_DELAY);
  setRgbLedColor(data, COLOR_YELLOW);
  delay(TEST_COLOR_CHANGE_DELAY);
  setRgbLedColor(data, COLOR_CYAN);
  delay(TEST_COLOR_CHANGE_DELAY);
  setRgbLedColor(data, COLOR_MAGENTA);
  delay(TEST_COLOR_CHANGE_DELAY);
  setRgbLedColor(data, COLOR_WHITE);
  delay(TEST_COLOR_CHANGE_DELAY);
  delayCyclingRgbColors(data, TEST_COLOR_CHANGE_DELAY);
}

RgbLedCommonAnode::RgbLedCommonAnode(int red_pin, int green_pin, int blue_pin) {
  initRgbLed_(data, red_pin, green_pin, blue_pin, getOnState());
}

RgbLedCommonCathode::RgbLedCommonCathode(int red_pin, int green_pin, int blue_pin) {
  initRgbLed_(data, red_pin, green_pin, blue_pin, getOnState());
}
