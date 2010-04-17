/**
 * This library provides both Object Oriented and non-OO interfaces to RGB LEDs
 * These are available in two types, common Anode and Common Cathode. We
 * provide a support for each of these with identical operations.
 *
 * This library, demo sketch and docs are available at:
 * http://www.insanegiantrobots.com/arduino/rgbled.zip
 * @see RgbLed.h
 * @author("Raymond Blum" <raymond@insanegiantrobots.com>)
 *
 * Copyright (c) 2010 by Raymond Blum
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * See file LICENSE.txt for further informations on licensing terms.
 */

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

/**
 Set the status LED to the specified color
**/
void RgbLed_::setColor(int color) {
  setRgbLedColor(data, color);
}

/**
  Return the pin setting for setting this LED's pin on or off corresponding to
  on_or_off.
**/
bool getRgbPinOn_(rgb_t &led, bool on_or_off) {
  return on_or_off?led.onState:!led.onState;
}

/**
  Set the 3 pins of the LED as neeed to make the specified color.
**/
void setRgbLedColor(rgb_t &led, int color) {
  digitalWrite(led.redPin, getRgbPinOn_(led, color & Color::RED));
  digitalWrite(led.greenPin, getRgbPinOn_(led, color & Color::GREEN));
  digitalWrite(led.bluePin, getRgbPinOn_(led, color & Color::BLUE));
  led.currentColor = color;
}

/**
  Setup an RGB LED with the specified 3 pins and the on-state of high or low.
  Common anode LEDs typically set an output pin to LOW whereas common cathode
  LEDs set the output pin HIGH.
**/
void initRgbLed_(rgb_t &led, int red_pin, int green_pin, int blue_pin, bool on_state) {
 led.redPin = red_pin;
 led.greenPin = green_pin;
 led.bluePin = blue_pin;
 led.onState = on_state;
 pinMode(led.redPin, OUTPUT);     
 pinMode(led.greenPin, OUTPUT);     
 pinMode(led.bluePin, OUTPUT);
}

/**
 Cycle from the startColor through the primaries and secondaries in color-wheel order, ending up on the target color
**/
void RgbLed_::cycleFromTo(int startColor, int targetColor) {
  cycleRgbFromTo(data, startColor, targetColor);
}
void cycleRgbFromTo(rgb_t &led, int start_color, int target_color) {
  // Really stupid way to do this
  int color = start_color;
  setRgbLedColor(led, color);
  do {
    delay(RGB_CYCLE_STATE_DURATION);
    color = nextColorInRgbSequence(color);
    // inject White into the sequence next to YELLOW
    if (target_color == Color::WHITE && color == Color::YELLOW) color = Color::WHITE;
    setRgbLedColor(led, color);
  } 
  while (color != target_color);
}

/**
 Return the next color in the wheel R-M-B-C-G|W-Y
**/
int nextColorInRgbSequence(int color) {
  switch (color)  {
    case Color::RED:
      return Color::MAGENTA;
    case Color::MAGENTA:
      return Color::BLUE;
    case Color::BLUE:
      return Color::CYAN;
    case Color::CYAN:
      return Color::GREEN;
    case Color::GREEN:
      return Color::YELLOW;
    case Color::YELLOW:
      return Color::RED;
    case Color::WHITE:
      return Color::YELLOW;
    default:
      return Color::WHITE;
  }
}

/**
 Pause for the specified duration in milliseconds, cycle the specified RGB LED
 once through the set of colors, leaving it in the current color.
**/
void RgbLed_::delayCyclingColors(int duration) {
  delayCyclingRgbColors(data, duration);
}

void delayCyclingRgbColors(rgb_t &led, int duration) {
  int savedColor = led.currentColor;
  int cycleDuration = duration / Color::COUNT;
  for (int i=0; i<Color::COUNT; i++) {
    setRgbLedColor(led, nextColorInRgbSequence(led.currentColor));
    delay(cycleDuration);
  }
  delay(duration - (cycleDuration * Color::COUNT));
  setRgbLedColor(led, savedColor);
}

/**
 Test each color and our cycling functions
**/
void RgbLed_::test() {
  setRgbLedColor(data, Color::RED);
  delay(TEST_COLOR_CHANGE_DELAY);
  setRgbLedColor(data, Color::GREEN);
  delay(TEST_COLOR_CHANGE_DELAY);
  setRgbLedColor(data, Color::BLUE);
  delay(TEST_COLOR_CHANGE_DELAY);
  setRgbLedColor(data, Color::YELLOW);
  delay(TEST_COLOR_CHANGE_DELAY);
  setRgbLedColor(data, Color::CYAN);
  delay(TEST_COLOR_CHANGE_DELAY);
  setRgbLedColor(data, Color::MAGENTA);
  delay(TEST_COLOR_CHANGE_DELAY);
  setRgbLedColor(data, Color::WHITE);
  delay(TEST_COLOR_CHANGE_DELAY);
  delayCyclingRgbColors(data, TEST_COLOR_CHANGE_DELAY);
}

RgbLedCommonAnode::RgbLedCommonAnode(int red_pin, int green_pin, int blue_pin) {
  initRgbLed_(data, red_pin, green_pin, blue_pin, getOnState());
}

RgbLedCommonCathode::RgbLedCommonCathode(int red_pin, int green_pin, int blue_pin) {
  initRgbLed_(data, red_pin, green_pin, blue_pin, getOnState());
}
