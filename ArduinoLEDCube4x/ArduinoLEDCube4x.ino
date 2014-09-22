// This code is for controlling the
// 64 LEDs of a 4x4x4 LED cube via
// an Arduino Uno and its 20 pins.
// 16 columns and 4 layers.
// Main features of this implemenation:
// - print characters to your Arduino LED cube
// - several font types and font animations  available
// - Multiplexing to ensure that a maximum of
//   16 LEDs is turned on at any time
//
// Instructions for building the 4x4x4 cube:
// http://www.instructables.com/id/LED-Cube-4x4x4/

// Adjust the column and layer numbers below
// to the physical connection of your LED cube to your
// Arduino pins.

const int layer[4] = {
  A0,A1,A2,A3};
const int column[16]={
  0,1,2,3,4,5,6,7,8,9,10,11,12,13,A4,A5};
const int DELAY = 5; //Delay between cube layer alternations, in milliseconds. 
int cube[4][4][4];

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






