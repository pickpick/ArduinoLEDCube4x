/*
  LEDCube.h - Library for animating the LEDs of a cube of 4x4x4 LEDs.
  Created by pickpick in 2014.
  Released into the public domain.
*/
#ifndef LEDCube_h
#define LEDCube_h

#include <Math.h>
#include <Arduino.h>

class LEDCube
{
  public:
    LEDCube(int test);
    void fillCube();
    void clearCube();
    void render(int pauseTime);
    void patternBlinkIn();
    void patternBlinkOut();
    void printChar(String text);
    void printUpward(String text);
    void printLeftward(String text);
    void printRandom(String text);
    void rotateZAxis(double theta);
    void patternKnightRider(int repetitions);   
    void patternSpiralTopThenBottom(int repetitions); 
    void patternSpiralTop(int repetitions); 
    void patternSpiralBottom(int repetitions); 
    void patternRandomLED(int repetitions);

    const int DELAY = 7; // Delay for multiplexing
    const int SCROLLDELAY = 100; // speed of scrolling chars
    int cube[4][4][4];
    int tmp[4][4][4];
    int l0;
    int l1;
    int l2;
	// number of LEDs on front and top combined is 7x4
	const int charHeight = 7;
	const int charWidth = 4;
    void printMoveUp();
    void printMoveLeft();

  private:

  };

#endif