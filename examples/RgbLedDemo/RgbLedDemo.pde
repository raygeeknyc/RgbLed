/**
 * RgbLed example showing both supported RGB LED types
 * and both RGB and Primary+Secondary color setting
 * techniques.
 *
 * This file and supporting library files can be found at:
 * http://www.insanegiantrobots.com/arduino/rgbled.zip
 *
 * @author("Raymond Blum" <raymond@insanegiantrobots.com>) 
 **/

#include <RgbLed.h>

// These Pins are connected through 220 ohm resistors to 3 cathodes
#define LED1_PIN_RED   12
#define LED1_PIN_BLUE  14
#define LED1_PIN_GREEN 15

// These pins are connected through 220 ohm resistors to 3 anodes
#define LED2_PIN_RED 5
#define LED2_PIN_GREEN  10
#define LED2_PIN_BLUE 9

#define DURATION_BLINK 2000
#define DURATION_DELAY 2000

// Create objects of the appropriate types for the two connected LEDs
// Last arg=true indicates that all of these pins are PWM enabled, omit for no PWM
// If you don't specify this and then setPwm, the library sets the LED to RGB_WHITE
RgbLedCommonAnode led_rgb1(LED1_PIN_RED, LED1_PIN_GREEN, LED1_PIN_BLUE, true);
RgbLedCommonCathode led_rgb2(LED2_PIN_RED, LED2_PIN_GREEN, LED2_PIN_BLUE, true);

void setup() {
  Serial.begin(9600);
  Serial.println("setup()");
 
  // Show some primaries
  Serial.println("<GREEN/RED>");
  led_rgb1.setColor(Color::RED);
  led_rgb2.setColor(Color::GREEN);
  delay(DURATION_BLINK);
  Serial.println("</GREEN/RED>");
  
  // Show some secondaries
  Serial.println("<CYAN/MAGENTA>");
  led_rgb1.setColor(Color::CYAN);
  led_rgb2.setColor(Color::MAGENTA);
  delay(DURATION_BLINK);
  Serial.println("</CYAN/MAGENTA>");
  Serial.println("<TELLOW>");
  led_rgb1.setColor(Color::YELLOW);
  led_rgb2.setColor(Color::YELLOW);
  delay(DURATION_BLINK);
  Serial.println("</YELLOW>");

  Serial.println("<CycleLED1Colors>");
  led_rgb1.cycleFromTo(Color::RGB_WHITE, Color::RGB_WHITE);
  Serial.println("</CycleLED1Colors>");
  delay(DURATION_BLINK);

  // Cycle an LED for a specific time
  Serial.println("<DelayCycleLED2Colors>");
  led_rgb2.delayCyclingColors(DURATION_DELAY);
  Serial.println("</DelayCycleLED2Colors>");
  delay(DURATION_BLINK);

  Serial.println("<CycleLED2Colors>");
  led_rgb2.cycleFromTo(Color::MAGENTA, Color::CYAN);
  Serial.println("</CycleLED2Colors>");
  delay(DURATION_BLINK);
}

void setPwm(unsigned int r, unsigned int g, unsigned int b) {
  led_rgb1.setColor(r, g, b);
  led_rgb2.setColor(r, g, b);
}

// Repeatedly mix the two LEDs to different colors using PWM 
// This only works if you have all LED pins on PWM enabled pins
void loop() {
  int r=0;
  int g=0;
  int b=0;
  
  setPwm(r, g, b);
  for (r=0; r<=255; r+=2) {
    for (g=0; g<=255; g+=2) {
      for (b=0; b<=255; b+=2) {
        setPwm(r, g, b);
      }  
    }
  }
}
