//2.4" TFT Touchscreen Shield Basic Example 
//By Kreezy(KRosa) 1.20.2018

// IMPORTANT: Adafruit_TFTLCD LIBRARY MUST BE SPECIFICALLY
// CONFIGURED FOR EITHER THE TFT SHIELD OR THE BREAKOUT BOARD.
// SEE RELEVANT COMMENTS IN Adafruit_TFTLCD.h FOR SETUP.

#include <Adafruit_GFX.h>    // Core graphics library
#include "Andersmmg_TFTLCD.h" // Hardware-specific library

// The control pins for the LCD can be assigned to any digital or
// analog pins...but we'll use the analog pins as this allows us to
// double up the pins with the touch screen (see the TFT paint example).
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

// When using the BREAKOUT BOARD only, use these 8 data lines to the LCD:
// For the Arduino Uno, Duemilanove, Diecimila, etc.:
//   D0 connects to digital pin 8  (Notice these are
//   D1 connects to digital pin 9   NOT in order!)
//   D2 connects to digital pin 2
//   D3 connects to digital pin 3
//   D4 connects to digital pin 4
//   D5 connects to digital pin 5
//   D6 connects to digital pin 6
//   D7 connects to digital pin 7
// For the Arduino Mega, use digital pins 22 through 29
// (on the 2-row header at the end of the board).

// Assign human-readable names to some common 16-bit color values:
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

Andersmmg_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
// If using the shield, all control and data lines are fixed, and
// a simpler declaration can optionally be used:
// Adafruit_TFTLCD tft;

int switchState = 0;   // A variable to store the virtual switch state 

void setup(void) {
  Serial.begin(9600);
  Serial.println(F("TFT LCD test"));

#ifdef USE_ADAFRUIT_SHIELD_PINOUT
  Serial.println(F("Using Adafruit 2.8\" TFT Arduino Shield Pinout"));
#else
  Serial.println(F("Using Adafruit 2.8\" TFT Breakout Board Pinout"));
#endif

  Serial.print("TFT size is "); Serial.print(tft.width()); Serial.print("x"); Serial.println(tft.height());

  tft.reset();

  uint16_t identifier = tft.readID();

  if(identifier == 0x9325) {
    Serial.println(F("Found ILI9325 LCD driver"));
  } else if(identifier == 0x9328) {
    Serial.println(F("Found ILI9328 LCD driver"));
  } else if(identifier == 0x7575) {
    Serial.println(F("Found HX8347G LCD driver"));
  } else if(identifier == 0x9341) {
    Serial.println(F("Found ILI9341 LCD driver"));
  } else if(identifier == 0x8357) {
    Serial.println(F("Found HX8357D LCD driver"));
  } else {
    Serial.print(F("Unknown LCD driver chip: "));
    Serial.println(identifier, HEX);
    Serial.println(F("If using the Adafruit 2.8\" TFT Arduino shield, the line:"));
    Serial.println(F("  #define USE_ADAFRUIT_SHIELD_PINOUT"));
    Serial.println(F("should appear in the library header (Adafruit_TFT.h)."));
    Serial.println(F("If using the breakout board, it should NOT be #defined!"));
    Serial.println(F("Also if using the breakout, double-check that all wiring"));
    Serial.println(F("matches the tutorial."));
    return;
  }

  tft.begin(identifier);

}

void loop(void) {
  tft.setRotation(1);                                // Sets screen orientation to horizontal
  tft.fillScreen(BLACK);                             // Fills the background with black
  tft.setCursor(0, 0);                               // Sets where the first letter will start on screen
  tft.setTextColor(WHITE);  tft.setTextSize(6);      // Sets text color to white and text size to 6
  tft.println("Kreezy's");                           // prints first line of text
  tft.println();                                    // blank line for spacing
  tft.setTextColor(RED);  tft.setTextSize(3);       // Sets text color to red and text size to 3
  tft.println("Arduino for Noobz");                 // prints next line of text
  tft.println();                                    // blank line for spacing
  tft.setTextColor(YELLOW);  tft.setTextSize(3);    // Sets text color to yellow and text size to 3
  tft.println("   Subscribe");                      // prints the next 3 lines of text on new lines
  tft.println("      on");
  tft.println("    YouTube");
  delay(5000);                                      // delay of 5 seconds

  switch (switchState) {                                 // switch to change transition color
    
    case 0:                                              // case 0 runs first because switchState starts at 0
      tft.fillScreen(BLUE);                             //  blue transition screen 
      switchState = (switchState+1);                    // adds 1 to switchState
      break;  
    case 1:                                             // case 1 will now run because switchState is now at 1
      tft.fillScreen(RED);                              // red transition screen
      switchState = (switchState+1);                    // adds another 1 to switchState
      break;
    case 2:                                             // case 2 will now run because switchState is now at 2
      tft.fillScreen(YELLOW);                           // yellow transition screen
      switchState = 0;                                  // switchState is returned to the default of 0
      break;                                            // so the loop will start all over again after this one
  }
  delay(1);
}

 
