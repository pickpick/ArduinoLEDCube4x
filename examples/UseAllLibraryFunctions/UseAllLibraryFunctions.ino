#define byte uint8_t

#include <LEDCube.h> // use the LED cube's library
#include <Arduino.h>
#include <Math.h>


LEDCube lc(0); //

void setup()
{
}

void loop()
{
  lc.fillCube();
  lc.render(1000);
  lc.clearCube();
  lc.render(1000);
  lc.patternKnightRider(2);
  lc.render(1000);
  lc.patternBlinkIn();
  lc.patternBlinkOut();
  // print each letter of a text string
  String str1 = "ABCabc";
  String text1 = "_-= HELLO! Hello!";
  String text2 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~ !\"#$%&'()*+,-.0123456789:;<=>?@";
  lc.clearCube();
  lc.printChar(str1);
  lc.printUpward(text1);
  lc.printLeftward(text1);
  lc.printRandom(text1);
  lc.printLeftward(text2);
}
