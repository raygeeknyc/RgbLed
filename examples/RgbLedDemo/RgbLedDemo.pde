/**
 * RgbLed example showing both supported RGB LED types
 *
 * This file and supporting library files can be found at:
 * http://www.insanegiantrobots.com/arduino/RgbLed.zip
 *
 * @author("Raymond Blum" <raymond@insanegiantrobots.com>) 
 **/

#include <RgbLed.h>

// These Pins are connected through 220 ohm resistors to 3 cathodes
#define LED1_PIN_RED   PIN_C2
#define LED1_PIN_BLUE  PIN_C1
#define LED1_PIN_GREEN PIN_C0

// These pins are connected through 220 ohm resistors to 3 anodes
#define LED2_PIN_RED PIN_F2
#define LED2_PIN_GREEN  PIN_F0
#define LED2_PIN_BLUE PIN_F1

#define DURATION_BLINK 2000
#define DURATION_DELAY 2000

// create objects of the appropriate types for the two connected LEDs
RgbLedCommonAnode led_rgb1(LED1_PIN_RED, LED1_PIN_GREEN, LED1_PIN_BLUE);
RgbLedCommonCathode led_rgb2(LED2_PIN_RED, LED2_PIN_GREEN, LED2_PIN_BLUE);

void setup() {
  Serial.begin(9600);
  Serial.println("setup()");
 
  Serial.println("<TestLED1>");
  led_rgb1.test();
  Serial.println("</TestLED1>");
  Serial.println("<TestLED2>");
  led_rgb2.test();
  Serial.println("</TestLED2>");

  Serial.println("<Yellow>");
  led_rgb1.setColor(Color::YELLOW);
  led_rgb2.setColor(Color::YELLOW);
  delay(DURATION_BLINK);
  Serial.println("</Yellow>");

  Serial.println("<CycleLED1Colors>");
  led_rgb1.cycleFromTo(Color::WHITE, Color::WHITE);
  Serial.println("</CycleLED1Colors>");
  Serial.println("<CycleLED2Colors>");
  led_rgb2.cycleFromTo(Color::MAGENTA, Color::MAGENTA);
  Serial.println("</CycleLED2Colors>");
  Serial.println("<LED1AllColors1Second>");
  led_rgb1.delayCyclingColors(DURATION_DELAY);
  Serial.println("</LED1AllColors1Second>");
  Serial.println("<LED2AllColors1Second>");
  led_rgb2.delayCyclingColors(DURATION_DELAY);
  Serial.println("</LED2AllColors1Second>");
}

// Repeatedly set the LEDs to complementary colors
void loop() {
  led_rgb1.setColor(Color::BLUE);
  led_rgb2.setColor(Color::RED);
  delay(DURATION_BLINK);
   
  led_rgb1.setColor(Color::CYAN);
  led_rgb2.setColor(Color::YELLOW);
  delay(DURATION_BLINK);
   
  led_rgb1.setColor(Color::MAGENTA);
  led_rgb2.setColor(Color::GREEN);
  delay(DURATION_BLINK);    
 
  led_rgb1.setColor(Color::WHITE);
  led_rgb2.setColor(Color::WHITE);
  delay(DURATION_BLINK);    
 
  led_rgb1.setColor(Color::GREEN);
  led_rgb2.setColor(Color::MAGENTA);
  delay(DURATION_BLINK);    
   
  led_rgb1.setColor(Color::YELLOW);
  led_rgb2.setColor(Color::CYAN);
  delay(DURATION_BLINK);

  led_rgb1.setColor(Color::RED );
  led_rgb2.setColor(Color::BLUE);
  delay(DURATION_BLINK);    
}
