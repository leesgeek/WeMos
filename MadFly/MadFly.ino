#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

int pinCS = 16; // Attach CS to this pin, DIN to MOSI and CLK to SCK (cf http://arduino.cc/en/Reference/SPI )
int numberOfHorizontalDisplays = 4;
int numberOfVerticalDisplays = 4;

Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

int pinRandom = A0;

int wait = 20; // In milliseconds

void setup() {
  matrix.setIntensity(4); // Set brightness between 0 and 15

//  ---------------------
//  |  2      | 3       | 
//  |     0,0 |     1,0 |  
//  ---------------------
//  |  1      | 0       |
//  |     0,1 |     1,1 | SPI IN
//  ---------------------

// Adjust to your own needs
  matrix.setPosition( 0, 3, 3); // 
  matrix.setPosition( 1, 2, 3); // 
  matrix.setPosition( 2, 1, 3); // 
  matrix.setPosition( 3, 0, 3); // 
  matrix.setPosition( 4, 0, 2); // 
  matrix.setPosition( 5, 1, 2); // 
  matrix.setPosition( 6, 2, 2); // 
  matrix.setPosition( 7, 3, 2); // 
  matrix.setPosition( 8, 3, 1); // 
  matrix.setPosition( 9, 2, 1); // 
  matrix.setPosition(10, 1, 1); // 
  matrix.setPosition(11, 0, 1); // 
  matrix.setPosition(12, 0, 0); // 
  matrix.setPosition(13, 1, 0); // 
  matrix.setPosition(14, 2, 0); // 
  matrix.setPosition(15, 3, 0); // 

  //  ...
  matrix.setRotation(0, 3);    // The first row is upside down
  matrix.setRotation(1, 3);    // 
  matrix.setRotation(2, 3);    // 
  matrix.setRotation(3, 3);    // 
  matrix.setRotation(4, 1);    // Second row is right side up
  matrix.setRotation(5, 1);    // 
  matrix.setRotation(6, 1);    // 
  matrix.setRotation(7, 1);    // 
  matrix.setRotation(8, 3);    // Third row is upside down
  matrix.setRotation(9, 3);    // 
  matrix.setRotation(10, 3);    // 
  matrix.setRotation(11, 3);    // 
  matrix.setRotation(12, 1);    // Fourth row is right side up
  matrix.setRotation(13, 1);    //
  matrix.setRotation(14, 1);    // 
  matrix.setRotation(15, 1);    // 

  randomSeed(analogRead(pinRandom)); // Initialize random generator
}

int x = numberOfHorizontalDisplays * 8 / 2;
int y = numberOfVerticalDisplays * 8 / 2;
int xNext, yNext;

void loop() {

  matrix.drawPixel(x, y, HIGH);
  matrix.write(); // Send bitmap to display

  delay(wait);

  matrix.drawPixel(x, y, LOW); // Erase the old position of our dot

  do {
    switch ( random(4) ) {
      case 0: xNext = constrain(x + 1, 0, matrix.width() - 1); yNext = y; break;
      case 1: xNext = constrain(x - 1, 0, matrix.width() - 1); yNext = y; break;
      case 2: yNext = constrain(y + 1, 0, matrix.height() - 1); xNext = x; break;
      case 3: yNext = constrain(y - 1, 0, matrix.height() - 1); xNext = x; break;
    }
  }
  while ( x == xNext && y == yNext ); // Repeat until we find a new coordinate

  x = xNext;
  y = yNext;
}
