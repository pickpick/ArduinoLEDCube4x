// This code is for controlling the
// 64 LEDs of a 4x4x4 LED cube via
// an Arduino Uno. 
// 
// Main features of this implemenation:
// - prints characters to your Arduino LED cube
// - several font types and font animations are available
// - Multiplexing to ensure that a maximum of
//   16 LEDs is turned on at any time
//
// Instructions for building the 4x4x4 cube:
// http://www.instructables.com/id/LED-Cube-4x4x4/

// Adjust the column and layer numbers below
// to the physical connection of your LED cube to your
// Arduino pins.

//#include "font.h"
#include <math.h>

const int layer[4] = {
  A0,A1,A2,A3};
const int column[16]={
  0,1,2,3,4,5,6,7,8,9,10,11,12,13,A4,A5};
const int DELAY = 5; // Delay for multiplexing
int cube[4][4][4];
int tmp[4][4][4];

// number of LEDs on front and top combined is 7x4
const int charHeight = 7;
const int charWidth = 4;

// 7x4 font
const byte font[][4] = {
        0x00, 0x00, 0x00, 0x00,         // Space
        0x5f, 0x00, 0x00, 0x00,         // !
        0x03, 0x00, 0x03, 0x00,         // "
        0x28, 0x7c, 0x28, 0x00,         // #
        0x2e, 0x6b, 0x3a, 0x00,         // $
        0x48, 0x20, 0x10, 0x48,         // %
        0x36, 0x49, 0x26, 0x50,         // &
        0x03, 0x00, 0x00, 0x00,         // '

        0x1c, 0x22, 0x41, 0x00,         // (
        0x41, 0x22, 0x1c, 0x00,         // )
        0x0a, 0x04, 0x0a, 0x00,         // *
        0x04, 0x0e, 0x04, 0x00,         // +
        0x60, 0x00, 0x00, 0x00,         // ,
        0x04, 0x04, 0x04, 0x00,         // -
        0x40, 0x00, 0x00, 0x00,         // .
        0x60, 0x18, 0x06, 0x00,         // /

        0x7f, 0x41, 0x7f, 0x00,         // 0
        0x42, 0x7f, 0x40, 0x00,         // 1
        0x7d, 0x45, 0x47, 0x00,         // 2
        0x45, 0x45, 0x7f, 0x00,         // 3
        0x3f, 0x20, 0x7f, 0x00,         // 4
        0x47, 0x45, 0x7d, 0x00,         // 5
        0x7f, 0x45, 0x7d, 0x00,         // 6
        0x01, 0x01, 0x7f, 0x00,         // 7

        0x7f, 0x45, 0x7f, 0x00,         // 8
        0x5f, 0x51, 0x7f, 0x00,         // 9
        0x50, 0x00, 0x00, 0x00,         // :
        0x68, 0x00, 0x00, 0x00,         // ;
        0x08, 0x14, 0x22, 0x00,         // <
        0x14, 0x14, 0x14, 0x00,         // =
        0x22, 0x14, 0x08, 0x00,         // >
        0x59, 0x0f, 0x00, 0x00,         // ?

        0x7a, 0x5a, 0x42, 0x7e,         // @
        0x7f, 0x21, 0x7f, 0x00,         // A
        0x7f, 0x45, 0x47, 0x7c,         // B
        0x7f, 0x41, 0x63, 0x00,         // C
        0x7f, 0x41, 0x41, 0x3e,         // D
        0x7f, 0x45, 0x45, 0x00,         // E
        0x7f, 0x05, 0x05, 0x00,         // F
        0x7f, 0x41, 0x7d, 0x00,         // G
        0x7f, 0x04, 0x7f, 0x00,         // H
        0x41, 0x7f, 0x41, 0x00,         // I
        0x40, 0x41, 0x7f, 0x01,         // J
        0x7f, 0x04, 0x0a, 0x71,         // K
        0x7f, 0x40, 0x40, 0x00,         // L
        0x7f, 0x01, 0x07, 0x7c,         // M
        0x7f, 0x01, 0x7f, 0x00,         // N
        0x7f, 0x41, 0x7f, 0x00,         // O

        0x7f, 0x21, 0x3f, 0x00,         // P
        0x7f, 0x41, 0x21, 0x5f,         // Q
        0x7f, 0x09, 0x79, 0x4f,         // R
        0x47, 0x45, 0x7d, 0x00,         // S
        0x01, 0x7f, 0x01, 0x00,         // T
        0x7F, 0x40, 0x7f, 0x00,         // U
        0x7f, 0x20, 0x10, 0x0f,         // V
        0x7f, 0x40, 0x70, 0x1f,         // W
        0x7b, 0x0e, 0x7b, 0x00,         // X
        0x07, 0x7c, 0x07, 0x00,         // Y
        0x79, 0x45, 0x43, 0x00,         // Z
        0x7f, 0x41, 0x00, 0x00,         // [
        0x06, 0x18, 0x60, 0x00,         // "\"
        0x41, 0x7f, 0x00, 0x00,         // ]
        0x02, 0x01, 0x02, 0x00,         // ^
        0x40, 0x40, 0x40, 0x00,         // _

        0x01, 0x02, 0x00, 0x00,         // `
        0x74, 0x54, 0x7c, 0x00,         // a
        0x7f, 0x44, 0x7c, 0x00,         // b
        0x7c, 0x44, 0x44, 0x00,         // c
        0x7c, 0x44, 0x7f, 0x00,         // d
        0x7c, 0x54, 0x5c, 0x00,         // e
        0x04, 0x7f, 0x05, 0x00,         // f
        0x5c, 0x54, 0x7c, 0x00,         // g
        0x7f, 0x04, 0x7c, 0x00,         // h
        0x7d, 0x00, 0x00, 0x00,         // i
        0x40, 0x7d, 0x00, 0x00,     // j
        0x7f, 0x10, 0x6c, 0x00,         // k
        0x7f, 0x40, 0x00, 0x00,         // l

        0x7c, 0x04, 0x1c, 0x70,         // m
        0x7c, 0x04, 0x7c, 0x00,         // n
        0x7c, 0x44, 0x7c, 0x00,         // o
        0x7c, 0x24, 0x3c, 0x00,         // p
        0x3c, 0x24, 0x7c, 0x00,         // q
        0x7c, 0x04, 0x04, 0x00,         // r
        0x5c, 0x54, 0x74, 0x00,         // s
        0x04, 0x7e, 0x44, 0x00,         // t
        0x7c, 0x40, 0x7c, 0x00,         // u
        0x7c, 0x20, 0x1c, 0x00,         // v
        0x7c, 0x40, 0x70, 0x1c,         // w
        0x6c, 0x10, 0x6c, 0x00,         // x
        0x5c, 0x50, 0x7c, 0x00,         // y
        0x64, 0x54, 0x4c, 0x00,         // z

        0x08, 0x7f, 0x41, 0x00,         // {
        0x7f, 0x00, 0x00, 0x00,         // |
        0x41, 0x7f, 0x08, 0x00,         // }
        0x01, 0x03, 0x02, 0x00,         // ~
        0x7f, 0x7f, 0x7f, 0x00         // Full Filled
};


//Setup
void setup(){
  //Setup Pin-Outputs
  for (int i=0; i<4;i++)
    pinMode(layer[i], OUTPUT);  
  for (int i=0; i<16; i++)
    pinMode(column[i], OUTPUT);

  //Gets Random Seed from Analog Pin
  randomSeed(analogRead(5));
  clearCube();
}


void loop(){
  patternKnightRider(5);
  patternThrowDice();
  fillCube();
  render(1000);
  clearCube();
  render(1000);
  cube[0][0][0]=1;
  render(1000);
  cube[1][0][0]=1;
  render(1000);
  cube[2][0][0]=1;
  render(1000);
  cube[3][0][0]=1;
  render(1000);
  for (int i; i<3; i++)
    for (int j=0; j<3; j++)
      for (int k=0;k<3;k++){
        cube[i][j][k] = random(1);
      }
  render(1000);
  rotate(90);
  render(1000);

  // print each letter of a text string
  char text[100] = "Hello world!";
  for (int i=0; i<sizeof(text); i++){
    print(text[i]);
    render(500);
 }

  patternSpiralTopThenBottom(10);  
  render(1000);
  patternBlinkIn();
  patternBlinkOut();
  patternSpiralTop(8);
  patternSpiralBottom(8);
  patternFacesRandom(30);
  patternSlashesAlternating(10);
  patternBlinkCube(30);
  patternRotateClockwise(20);
  patternRandomLED(20);
}

void print(char ch)
{
  byte b;
  // make sure the character is within the alphabet bounds (defined by the font.h file)
  // if it's not, make it a blank character
  if (ch < 32 || ch > 126)
    ch = 32;
  // converts the ASCII number to the font index number
  ch -= 32;
  // step through each byte of the character array
  for (int i=0; i<charWidth; i++) {
    b = font[ch][i];
    // bit shift through the byte and output it to the pin
    for (int k=0; k<4; k++) 
     cube[i][0][k] =  !!(b & (1 << k));
    for (int j=1; j<4; j++)
     cube[i][j][3] = !!(b & (1 << (3+j)));
  }
}


void patternThrowDice(){
  //print(random(6));
}


void rotate(double theta){
  for (int i; i<3; i++)
    for (int j=0; j<3; j++)
      for (int k=0;k<3;k++){
        int l = (int) (0.5 +i*cos(theta) - j*sin(theta));
        int m = (int) (0.5 +i*sin(theta) + j*cos(theta));
        if (l>=0 && l<4 && m>=0 && k <4){
          tmp[l][m][k]=cube[i][j][k];
          // rotate around the z axis
        }
      }
  for (int i=0; i<3; i++)
    for (int j=0; j<3; j++)
      for (int k=0; k<3; k++){
        cube[i][j][k]=tmp[i][j][k];
      }
}

void patternBlinkIn(){
  int count, x, y, z;
  count = 64;
  clearCube();
  while(count > 0){
    x = random(4);
    y = random(4);
    z = random(4);
    if(cube[x][y][z]==0){
      cube[x][y][z]=1;
      count--;
      render(500);
    }
  }
  clearCube();
}

void patternBlinkOut(){
  int count, x, y, z;
  count = 64;
  fillCube();
  while(count > 0){
    x = random(4);
    y = random(4);
    z = random(4);
    if(cube[x][y][z]==1){
      cube[x][y][z]=0;
      count--;
      render(500);
    }
  }
  clearCube();
}

void patternKnightRider(int repetitions){
  for (int j=0;j<repetitions;j++){
    for (int i=0;i<3;i++){
      cube[i][0][0] = 1;
      render(30);
      cube[i+1][0][0] = 1;
      render(30);
      cube[i][0][0] = 0;
    }
    for (int i=0;i<3;i++){
      cube[3][i][0] = 1;
      render(30);
      cube[3][i+1][0] = 1;
      render(30);
      cube[3][i][0] = 0;
      render(60);
    }
    for (int i=3;i>0;i--){
      cube[3][i][0] = 1;
      render(30);
      cube[3][i-1][0] = 1;
      render(30);
      cube[3][i][0] = 0;
      render(60);
    }
    for (int i=3;i>0;i--){
      cube[i][0][0] = 1;
      render(30);
      cube[i-1][0][0] = 1;
      render(30);
      cube[i][0][0] = 0;
    }
  }
}

void patternSpiralTopThenBottom(int repetitions){
  int i;
  for (i=0;i<repetitions;i++){
    patternSpiralTop(1);
    patternSpiralBottom(1);
  }
}

void patternSpiralTop(int repetitions){
  for (int i=0;i<repetitions;i++){
    for (int l=0;l<4;l++){
      for (int k=0;k<4;k++){
        for (int j=0;j<4;j++){
          cube[j][k][l] = 1;
          render(100);
          cube[j][k][l] = 0;
          render(100);
        }
      }
    }
  }
}

void patternSpiralBottom(int repetitions){
  for (int i=0;i<repetitions;i++){
    for (int l=3;l>=0;l--){
      for (int k=3;k>=0;k--){
        for (int j=3;j>=0;j--){
          cube[j][k][l] = 1;
          render(100);
          cube[j][k][l] = 0;
          render(1);
        }
      }
    }
  }
}

void patternFacesRandom(int repetitions){
  int i, face;
  for(i = 0; i<repetitions;i++){
    face = random(6);
    switch (face){
    case 0: //Top
      {
        cube[1][0][0] = 1;
        cube[1][1][0] = 1;
        cube[1][0][1] = 1;
        cube[1][1][1] = 1;
      }
      break;
    case 1://Bottom
      {
        cube[0][0][0] = 1;
        cube[0][1][0] = 1;
        cube[0][0][1] = 1;
        cube[0][1][1] = 1;
      }
      break;
    case 2://Left
      {
        cube[0][0][0] = 1;
        cube[1][0][0] = 1;
        cube[0][0][1] = 1;
        cube[1][0][1] = 1;
      }
      break;
    case 3://Right
      {
        cube[0][1][0] = 1;
        cube[1][1][0] = 1;
        cube[0][1][1] = 1;
        cube[1][1][1] = 1;
      }
      break;
    case 4://Front
      {
        cube[0][0][1] = 1;
        cube[0][1][1] = 1;
        cube[1][0][1] = 1;
        cube[1][1][1] = 1;
      }
      break;
    case 5://Back
      {
        cube[0][1][0] = 1;
        cube[0][0][0] = 1;
        cube[1][1][0] = 1;
        cube[1][0][0] = 1;
      }
      break;
    }
    render(400);
    clearCube();
  }
}

void patternSlashesAlternating(int repetitions){
  int i;
  for(i=0;i<repetitions;i++){
    cube[0][0][0] = 1;  
    cube[1][0][0] = 1;
    cube[0][1][1] = 1;
    cube[1][1][1] = 1;
    render(350);
    clearCube();
    cube[0][1][0] = 1;  
    cube[1][1][0] = 1;
    cube[0][0][1] = 1;
    cube[1][0][1] = 1;
    render(350);
    clearCube();
  } 
}

void patternBlinkCube(int repetitions){
  int i;
  for(i=0;i<repetitions;i++){
    fillCube();
    render(100);
    clearCube();
    render(100);
  } 
}

void patternRandomLED(int repetitions){
  int i, x, y, z;
  for(i=0;i<repetitions;i++){
    x = random(4);
    y = random(4);
    z = random(4);
    cube[y][x][z]=1;
    render(250);
    clearCube();
  }
}

void patternRotateClockwise(int repetitions){
  int i;
  int speedDelay = 125;
  for (i = 0;i<repetitions;i++){
    cube[0][0][0] = 1; 
    cube[1][0][0] = 1;
    render(speedDelay);
    clearCube();
    cube[0][1][0] = 1; 
    cube[1][1][0] = 1;
    render(speedDelay);
    clearCube();
    cube[0][1][1] = 1; 
    cube[1][1][1] = 1;
    render(speedDelay);
    clearCube();
    cube[0][0][1] = 1; 
    cube[1][0][1] = 1;
    render(speedDelay);
    clearCube();
  }
}

// Function to draw cube map for specified number of milliseconds. 
// Alternates betwween layers for multiplexing.
// Draws the current binary cube matrix to the Arduino for 'pausetime' milliseconds.
void render(int pauseTime){
  long timer = 0;
  while(timer<=pauseTime){
    for (int k=0;k<4;k++){  // turn on only one layer of LEDs at a time
      digitalWrite(layer[k], LOW);
      for (int i=0;i<4;i++)
      {
        for (int j=0;j<4;j++)
        {
          if(cube[i][j][k] == 1){
            digitalWrite(column[i +4*j], HIGH);
          }
          else{
            digitalWrite(column[i +4*j], LOW);
          };
        }
      }
      delay(DELAY);
      digitalWrite(layer[k], HIGH);
    }
    timer += DELAY * 4;
  }
}

// turn all LEDs off
void clearCube(){
  int i, j, k;
  for(i=0;i<4;i++)
  {
    for(j=0;j<4;j++)
    {
      for(k=0;k<4;k++)
      {
        cube[i][j][k] = 0;
      }
    }
  }
}

// turn all LEDs on
void fillCube(){
  int i, j, k;
  for(i=0;i<4;i++)
  {
    for(j=0;j<4;j++)
    {
      for(k=0;k<4;k++)
      {
        cube[i][j][k] = 1;
      }
    }
  }
}






