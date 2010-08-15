/**
 * This library provides both Object Oriented and non-OO interfaces to RGB LEDs
 * These are available in two types, common Anode and Common Cathode. We
 * provide a support for each of these with identical operations.
 *
 * This library, demo sketch and docs are available at:
 * http://www.insanegiantrobots.com/arduino/rgbled.zip
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

#ifndef RgbLed_h
#define RgbLed_h

#include <stdint.h>

typedef struct _drgb_t {
  bool onState;
  int currentColor;
  int redPin;
  int greenPin;
  int bluePin;
} rgb_t;


typedef struct _argb_t {
  bool onState;
  int currentRed;
  int currentGreen;
  int currentBlue;
  int redPin;
  int greenPin;
  int bluePin;
} rgb_t;

/***
  Setup an RGB LED with the specified 3 pins and the pin state (LOW or HIGH) for "on".
***/
void initRgbLed_(rgb_t &led, int red_pin, int green_pin, int blue_pin, bool on_state);

/***
 Set the status LED to the specified color
***/
void setRgbLedColor(rgb_t &led, int color);

/***
 Set the analog status LED to the specified RGB value
***/
void setRgbLedColor(rgb_t &led, int red, int green, int blue);

/***
 Cycle from the startColor through the primaries and secondaries
 in color-wheel order, ending up on the target color
***/
void cycleRgbFromTo(rgb_t &led, int startColor, int targetColor);

/***
 Return the next color in the wheel R-M-B-C-G|W-Y
***/
int nextColorInRgbSequence(int color);

/***
 Pause for the specified duration in milliseconds, cycle the specified RGB LED
 once through the set of colors, leaving it in the current color.
***/
void delayCyclingRgbColors(rgb_t &led, int duration);

/**
  Class to hold our Color constants for primary and secondary colors.
  Declare a private constructor to prevent instantiation.
***/
class Color {
private:
 inline Color() {};
public:
 static const int NONE = 0;
 static const int RED = 1;
 static const int GREEN = 2;
 static const int BLUE = 4;
 static const int YELLOW = (GREEN + RED);
 static const int CYAN = (GREEN + BLUE);
 static const int MAGENTA = (RED + BLUE);
 static const int WHITE = (RED + GREEN + BLUE);

 static const int COUNT = 7;
};

/**
 Abstract class to represent a 4 pin RGB LED on digital pins. These LEDs come in two varieties,
 common anode and common cathode, thus only the two subclasses can be
 instantiated.
**/
class DRgbLed_ {
private:
protected:
  drgb_t data;
public:
  void delayCyclingColors(int);
  /**
   Test each color and our cycling functions
  **/
  void test();
  void setColor(int color);
  void cycleFromTo(int start_color, int target_color);
};

/**
 Abstract class to represent a 4 pin RGB LED on analog pins.
**/
class ARgbLed_ {
private:
protected:
  argb_t data;
public:
  void setColor(int red, int green, int blue);
};

/**
  Class to represent a 4 pin RGB LED with 3 Cathodes and 1 common Anode on digital pins.
  These are typically wired through a resistor to each of 3 LED legs
  with the 4th LED leg to VCC. 
**/
class DRgbLedCommonAnode : public DRgbLed_ {
private:
  inline bool getOnState() { return false; };
public:
  DRgbLedCommonAnode(int red_pin, int green_pin, int blue_pin);
};

/**
  Class to represent a 4 pin RGB LED with 3 Anodes and 1 common Cathode on digital pins.
  These are typically wired through a resistor to each of 3 LED legs
  with 4th LED leg to ground.
**/
class DRgbLedCommonCathode : public DRgbLed_ {
private:
  inline bool getOnState() { return true; };
public:
  DRgbLedCommonCathode(int red_pin, int green_pin, int blue_pin);
};

/**
  Class to represent a 4 pin RGB LED with 3 Cathodes and 1 common Anode on analog pins.
  These are typically wired through a resistor to each of 3 LED legs
  with the 4th LED leg to VCC. 
**/
class ARgbLedCommonAnode : public ARgbLed_ {
private:
  inline bool getOnState() { return false; };
public:
  DRgbLedCommonAnode(int red_pin, int green_pin, int blue_pin);
};

/**
  Class to represent a 4 pin RGB LED with 3 Anodes and 1 common Cathode on analog pins.
  These are typically wired through a resistor to each of 3 LED legs
  with 4th LED leg to ground.
**/
class ARgbLedCommonCathode : public ARgbLed_ {
private:
  inline bool getOnState() { return true; };
public:
  ARgbLedCommonCathode(int red_pin, int green_pin, int blue_pin);
};
#endif