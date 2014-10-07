// This code is for controlling the
// 64 LEDs of a 4x4x4 LED cube via
// an Arduino Uno. 
// 
// Main features of this implementation:
// - prints characters to your Arduino LED cube
// - own font types can be created with the
//   file BitFont_Generator_for_ArduinoLEDCube4x.xls
// - Multiplexing with a maximum of
//   16 LEDs turned on at any time
//
// Instructions for building a 4x4x4 LED cube are 
// available e.g. here
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
const int SCROLLDELAY = 100; // speed of scrolling chars
int cube[4][4][4];
int tmp[4][4][4];

// number of LEDs on front and top combined is 7x4
const int charHeight = 7;
const int charWidth = 4;

// For creating your own 7x4 font
// you can use the 
// the BitFont_Generator_for_ArduinoLEDCube4x.xls
// and copy the bytes of the characters.
const byte font[][4] = {
  0,0,0,0,	//	32	 Space
  125,0,0,0,	//	33	 !
  96,0,96,0,	//	34	 "
  20,127,20,127,	//	35	 #
  58,107,107,46,	//	36	 $
  99,100,11,51,	//	37	 %
  54,73,54,5,	//	38	 &
  16,96,0,0,	//	39	 '
  28,34,65,0,	//	40	 (
  65,34,28,0,	//	41	 )
  20,56,56,20,	//	42	 *
  4,14,4,0,	//	43	 +
  1,6,0,0,	//	44	 ,
  4,4,4,4,	//	45	 -
  3,3,0,0,	//	46	 .
  0,0,0,0,	//	47	 
  127,65,65,127,	//	48	 0
  8,16,32,127,	//	49	 1
  67,69,73,113,	//	50	 2
  73,73,73,127,	//	51	 3
  120,8,8,127,	//	52	 4
  121,73,73,79,	//	53	 5
  127,73,73,79,	//	54	 6
  64,72,72,127,	//	55	 7
  127,73,73,127,	//	56	 8
  121,73,73,127,	//	57	 9
  20,0,0,0,	//	58	 :
  1,22,0,0,	//	59	 ;
  8,20,34,0,	//	60	 <
  20,20,20,20,	//	61	 =
  34,20,8,0,	//	62	 >
  88,85,85,52,	//	63	 ?
  30,33,45,61,	//	64	 @
  127,72,72,127,	//	65	 A
  127,73,73,54,	//	66	 B
  62,65,65,65,	//	67	 C
  127,65,65,62,	//	68	 D
  127,73,73,73,	//	69	 E
  127,72,72,72,	//	70	 F
  62,65,73,78,	//	71	 G
  127,8,8,127,	//	72	 H
  65,127,65,0,	//	73	 I
  66,65,65,126,	//	74	 J
  127,20,34,65,	//	75	 K
  127,1,1,1,	//	76	 L
  127,48,48,127,	//	77	 M
  127,48,12,127,	//	78	 N
  62,65,65,62,	//	79	 O
  127,72,72,48,	//	80	 P
  62,65,71,63,	//	81	 Q
  127,76,74,121,	//	82	 R
  121,73,73,79,	//	83	 S
  64,127,64,64,	//	84	 T
  126,1,1,127,	//	85	 U
  124,3,3,124,	//	86	 V
  127,14,14,127,	//	87	 W
  99,28,28,99,	//	88	 X
  112,12,15,112,	//	89	 Y
  67,77,89,97,	//	90	 Z
  127,65,65,0,	//	91	 [
  96,24,6,1,	//	92	 "\"
  65,65,127,0,	//	93	 ]
  32,64,32,0,	//	94	 ^
  1,1,1,1,	//	95	 _
  96,16,0,0,	//	96	 `
  14,17,17,31,	//	97	 a
  127,17,17,14,	//	98	 b
  14,17,17,17,	//	99	 c
  14,17,17,127,	//	100	 d
  31,21,21,29,	//	101	 e
  63,72,72,0,	//	102	 f
  29,21,21,31,	//	103	 g
  127,8,8,7,	//	104	 h
  47,1,0,0,	//	105	 i
  1,47,0,0,	//	106	 j
  127,4,10,17,	//	107	 k
  127,1,0,0,	//	108	 l
  15,8,15,7,	//	109	 m
  15,8,7,0,	//	110	 n
  14,17,17,14,	//	111	 o
  31,20,28,0,	//	112	 p
  0,28,20,31,	//	113	 q
  31,16,24,0,	//	114	 r
  29,21,21,23,	//	115	 s
  127,25,1,0,	//	116	 t
  30,1,1,31,	//	117	 u
  28,3,2,28,	//	118	 v
  31,7,7,31,	//	119	 w
  17,14,14,17,	//	120	 x
  1,29,7,28,	//	121	 y
  17,19,21,25,	//	122	 z
  8,54,65,65,	//	123	 {
  127,0,0,0,	//	124	 |
  65,65,54,8,	//	125	 }
  24,16,8,24,	//	126	 ~
  127,127,127,127,	//	127	 Full Filled
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
  //Serial.begin(9600);
  //Serial.println("output for debugging");
}


void loop(){
  fillCube();
  render(1000);
  clearCube();
  render(1000);
  patternBlinkIn();
  patternBlinkOut();
  // print each letter of a text string
  char text1[14] = "HELLO! Hello!";
  char text2[100] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~ !\"#$%&'()*+,-.0123456789:;<=>?@";
  int size1 = sizeof(text1);
  int size2 = sizeof(text2);
  printUpward(text1, size1);
  printChar(text1, size1);
  printLeftward(text1, size1);
  printRandom(text1, size1);
  printLeftward(text2, size2);

  patternKnightRider(2);
  clearCube();
  render(100);
  patternBlinkIn();
  patternBlinkOut();
  patternSpiralTop(1);
  patternSpiralBottom(1);
  patternSpiralTopThenBottom(2);  
  render(1000);
  patternRandomLED(20);

  cube[0][0][0] = 1;
  cube[1][1][1] = 1;
  cube[1][1][0] = 1;
  cube[2][2][0] = 1;
  cube[2][2][1] = 1;
  cube[2][2][2] = 1;
  cube[3][3][0] = 1;
  cube[3][3][1] = 1;
  cube[3][3][2] = 1;
  cube[3][3][3] = 1;
  cube[3][2][0] = 1;
  cube[3][1][0] = 1;
  for (int i=0; i<=8; i++){
    rotateZAxis(90.0/360.0*2.0*PI);
    render(1000);
  }

  /*
  patternThrowDice();
   rotateZAxis(90);
   render(1000);
   */
}

void printChar(char chars[], int size)
{ 
  for (int p=0; p<size; p++){
    char ch = chars[p];
    // print char by char
    byte b;
    // If the character is not within the alphabet bounds
    // make it a blank character
    if (ch < 32 || ch > 126)
      ch = 32;
    // converts the ASCII number to the font index number
    ch -= 32;
    // step through each byte of the character array
    for (int i=0; i<charWidth; i++) {
      b = font[ch][i];
      // bit shift through the byte and output it to the pin
      for (int j=3; j>=0; j--)
        cube[i][j][3] = !!(b & (1 << (3+j)));
      for (int k=2; k>=0; k--) 
        cube[i][0][k] =  !!(b & (1 << k));
    }
    render(1000);
    clearCube();
    render(100);
  }
}


void printUpward(char chars[], int size)
{ // have chars floating upwards
  for (int p=0; p<size; p++){
    char ch = chars[p];
    byte b[4];
    if (ch < 32 || ch > 126)
      ch = 32;
    // converts the ASCII number to the font index number
    ch -= 32;

    // shift current status of LEDs two rows upwards
    // in order to have two blank rows between chars
    printMoveUp();
    printMoveUp();
    // step through each of the 7 rows of the character array
    for (int i=0; i<charWidth; i++)
      b[i] = font[ch][i];
    for (int j=charHeight-1; j>=0; j--) {
      printMoveUp();
      for (int i=0; i<charWidth; i++)
        // shift row by row through the char 
        // and output 4 bits of each row to the bottom 
        cube[i][0][0] =  !!(b[i] & (1 << j));
      render(SCROLLDELAY); 
    } 
    render(1000);
  }
}


void printLeftward(char chars[], int size)
{ // have chars floating form right to left
  for (int p=0; p<size; p++){
    char ch = chars[p];
    byte b;
    byte bRight; 
    // If the character is not within the alphabet bounds
    // make it a blank character
    if (ch < 32 || ch > 126)
      ch = 32;
    // converts the ASCII number to the font index number
    ch -= 32;

    // shift current status of LEDs two columns to the left
    // in order to have two blank space between the chars
    for (int p=0; p<3; p++){
      printMoveLeft();
      // turn last column off to have space between chars
      for (int k=0; k<3; k++) 
        cube[3][0][k] = 0 ;

      // shift bit by bit through the byte 
      // and output the bottom 3 bits to 
      // the right sight  of the cube
      b = font[ch][p];
      for (int k=0; k<3; k++) 
        cube[3][3][k] =  !!(b & (1 << k));

      render(SCROLLDELAY); // render right side
    }

    // step through each of the 4 bytes of the character array
    for (int i=0; i<charWidth; i++) {
      printMoveLeft();
      // print right side of cube
      if (i+3 < charWidth){  // only last byte in 7x4 fontsize
        bRight = font[ch][i+3];
        for (int k=0; k<2; k++) 
          cube[3][3][k] =  !!(bRight & (1 << k));
      } 
      else {
        for (int k=0; k<2; k++) 
          cube[3][3][k] =  0;
      }

      b = font[ch][i];
      // shift bit by bit through the byte 
      // and output it to the pin
      for (int j=3; j>=0; j--)
        cube[3][j][3] = !!(b & (1 << (3+j)));
      for (int k=2; k>=0; k--) 
        cube[3][0][k] =  !!(b & (1 << k));
      render(SCROLLDELAY); // render right side, front and left side
    }  
    render(1000);
  }
}

void printMoveUp(){ // used for shifting chars on the cube one row upwards
  for (int j=3; j>0; j--) // move rows on top side
    for (int k=0; k<=3; k++) 
      cube[k][j][3] = cube[k][j-1][3] ;

  for (int j=3; j>0; j--){
    for (int m=0; m<=3; m++) // move rows on front side
      cube[m][0][j] = cube[m][0][j-1];
  }
  for (int m=0; m<=3; m++) // turn off bottom LEDs on front side
    cube[m][0][0] = 0;
  render(SCROLLDELAY);
}


void printMoveLeft(){ // used for shifting chars on the cube one column to the left
  //copy LED status on the left side of the cube one step to the left
  for (int j=3; j>0; j--)
    for (int k=0; k<3; k++) 
      cube[0][j][k] = cube[0][j-1][k] ;

  for (int m=0; m<3; m++){
    for (int j=3; j>=0; j--) //copy top LED status one step to the left
      cube[m][j][3] = cube[m+1][j][3];
    for (int k=2; k>=0; k--) //copy front LED status one step to the left
      cube[m][0][k] = cube[m+1][0][k] ;
  }

  //copy LED status on the right side of the cube one step to the left
  for (int j=1; j<3; j++)
    for (int k=0; k<3; k++) 
      cube[3][j][k] = cube[3][j+1][k] ; 

  render(SCROLLDELAY);
  for (int k=0; k<3; k++)  // most right LED is off on right side
    cube[3][3][k] = 0; 
  for (int k=0; k<4; k++)  // most right LED is off on top side
    cube[3][k][3] = 0; 
}

void printRandom(char chars[], int size)
{ // pixels of each char turn randomly
  int count, x, z;
  byte b;
  for (int p=0; p<size; p++){
    count = 64;
    clearCube();
    render(100);

    char ch = chars[p];
    if (ch < 32 || ch > 126)
      ch = 32;
    ch -= 32;

    while(count > 0){
      x = random(4);
      z = random(7);
      b = font[ch][x];
      if (z<=3) {
        if (!!(b & (1 << z))){
          cube[x][0][z] = 1; 
          count--;
          render(5);
        }
      }
      else if(!!(b & (1 << z))){
        cube[x][z-3][3] = 1;
        count--;
        render(5);  
      }
      else if (b==0)
        count--;     
    }      
    render(1000);
  }
}

/*
void patternThrowDice(){
 printLeftward(1+random(6),1);
 }
 */

void rotateZAxis(double theta){
  // rotate around the z axis
  //this function needs some debugging
  for (int i=0; i<=3; i++)
    for (int j=0; j<=3; j++)
      for (int k=0; k<=3; k++){
        int l = (int)(0.5 +1.5 +(double(i)-1.5)*cos(theta) - ((double)(j)-1.5)*sin(theta));
        int m = (int)(0.5 +1.5 +(double(i)-1.5)*sin(theta) + ((double)(j)-1.5)*cos(theta));
        tmp[l][m][k]=cube[i][j][k];
      }
  for (int i=0; i<=3; i++)
    for (int j=0; j<=3; j++)
      for (int k=0; k<=3; k++){
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
      render(20);
    }
  }
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
      render(20);
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
  for (int i=0; i<repetitions; i++){
    for (int l=0;l<4;l++){
      for (int k=0;k<4;k++){
        for (int j=0;j<4;j++){
          cube[j][k][l] = 1;
          render(10);
        }
      }
    }
  }
}

void patternSpiralBottom(int repetitions){
  for (int i=0; i<repetitions;i ++){
    for (int l=3;l>=0;l--){
      for (int k=3;k>=0;k--){
        for (int j=3;j>=0;j--){
          cube[j][k][l] = 0;
          render(10);
        }
      }
    }
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







































