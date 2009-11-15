// Data structures, constants and functions for working with 3 color 4 pin
// LEDs
// 2009
// @author("Raymond Blum" <raymond@insanegiantrobots.com>)

#ifndef RgbLed_h
#define RgbLed_h

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
  int currentColor;
  int redPin;
  int greenPin;
  int bluePin;
} rgb_t;

/***
  Setup an RGB LED with the specified 3 pins
***/
void initRgbLed(rgb_t &led, int red_pin, int green_pin, int blue_pin);

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

#endif
