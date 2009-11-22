// Class, Data structures, constants and functions for working with 3 color 4 pin
// LEDs
// 2009
// @author("Raymond Blum" <raymond@insanegiantrobots.com>)
//
// Provides both Object Oriented and non-OO interfaces to RGB LEDs
//

#ifndef RgbLed_h
#define RgbLed_h

#include <stdint.h>

enum {
 COLOR_NONE = 0,
 COLOR_RED = 1,
 COLOR_GREEN = 2,
 COLOR_BLUE = 4,
 COLOR_YELLOW = (COLOR_GREEN + COLOR_RED),
 COLOR_CYAN = (COLOR_GREEN + COLOR_BLUE),
 COLOR_MAGENTA = (COLOR_RED + COLOR_BLUE),
 COLOR_WHITE = (COLOR_RED + COLOR_GREEN + COLOR_BLUE)
};

#define COUNT_COLOR 7

typedef struct _rgb_t {
  bool onState;
  int currentColor;
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


class RgbLed_ {
private:
protected:
  rgb_t data;
public:
  void _init_(int, int, int);
  void delayCyclingColors(int);
  /***
   Test each color and our cycling functions
  ***/
  void test();
  void setColor(int);
  void cycleFromTo(int, int);
};

/**
  Class to represent a 4 pin RGB LED with 3 Cathodes and 1 common Anode.
  These are typically wired through a resistor to each of 3 LED legs
  with the 4th LED leg to VCC. 
***/
class RgbLedCommonAnode : public RgbLed_ {
private:
  inline bool getOnState() { return false; };
public:
  RgbLedCommonAnode(int, int, int);
};

/**
  Class to represent a 4 pin RGB LED with 3 Anodes and 1 common Cathode.
  These are typically wired through a resistor to each of 3 LED legs
  with 4th LED leg to ground.
***/
class RgbLedCommonCathode : public RgbLed_ {
private:
  inline bool getOnState() { return true; };
public:
  RgbLedCommonCathode(int, int, int);
};
#endif
