/******************************************************************************
** TEXT SCROLL SAMPLE FOR ALTAIRIS ESP8266-FC16 LIBRARY
**
** This sample will scroll text on the display. Available characters are
** defined in FC16_Font.h. In addition to the ASCII table, the following glyphs
** are defined (inspired by CP437, but not fully compatible):
** \x01 :-)
** \x02 :-(
** \x03 heart
** \x04 diamond
** \x05 club
** \x06 spade
** \x07 bullet
** \x08 empty bullet
** \x09 big bullet
** \x0A big bullet inverse
** \x0B checkbox empty
** \x0C checkbox cross
** \x0D checkbox check
** \x0E checkbox full
** \x0F sunny
** \x10 triangle right
** \x11 triangle left
** \x18 arrow up
** \x19 arrow down
** \x1A arrow right
** \x1B arrow left
** \x7F full-width space (8 pixels)
**
** Hardware setup (ESP8266 <-> FC16):
** 3V3 <-> VCC, GND <-> GND, D7 <-> DIN, D8 <-> CS, D5 <-> CLK
******************************************************************************/

#include <FC16.h>

const int csPin = D8;			// CS pin used to connect FC16
const int displayCount = 4;		// Number of displays; usually 4 or 8
const int scrollDelay = 100;		// Scrolling speed - pause in ms
char display_text[] = "\x10 Merry Christmas! \x11";
int scrollCount, thisCount;
int i = 0;
bool firstRun = 1;

const byte BMP_4D[] = {
  0x40, 0x50, 0x54, 0xfe, 0x54, 0x50, 0x40, 0x00,
  0x40, 0x50, 0x54, 0xfe, 0x54, 0x50, 0x40, 0x00,
  0x40, 0x50, 0x54, 0xfe, 0x54, 0x50, 0x40, 0x00,
  0x40, 0x50, 0x54, 0xfe, 0x54, 0x50, 0x40, 0x00
};

const byte BMP_Blank[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

FC16 display = FC16(csPin, displayCount);

void setup() {
  display.shutdown(false);  // turn on display
  display.setIntensity(8);  // set medium brightness
  display.clearDisplay();   // turn all LED off

  scrollCount = ((strlen(display_text) - 1) * 5) + (displayCount * 8) + 1;
}

void loop() {
  i = 0;
  if (firstRun) {
    thisCount = scrollCount - (displayCount * 8);
    firstRun = 0;
  } else {
    thisCount = scrollCount;
  }
  display.setText(display_text);

  while (i < thisCount) {
    // Perform scroll
    display.update();

    // Wait for 30 ms
    delay(scrollDelay);
    i++;
  }
  for (int n = 0; n < 4; n++) {
    display.setBitmap(BMP_4D);
    delay(300);
    display.setBitmap(BMP_Blank);
    delay(300);
  }

}
