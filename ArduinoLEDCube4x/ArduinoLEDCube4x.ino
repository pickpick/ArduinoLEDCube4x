  // This code is for controlling the
  // 64 LEDs of a 4x4x4 LED cube via
  // an Arduino Uno and its 20 pins.
  // 16 columns and 4 layers.
  // Main features of this implemenation:
  // - print characters to your Arduino LED cube
  // - several font types and font animations  available
  // - Multiplexing to ensure that a maximum of
  //   16 LEDs is turned on at any time
  
  
  // Adjust the column and layer numbers below
  // to the physical connection of your LED cube to your
  // Arduino pins.
const int layer[2] = {A0,A1};
const int column[16]={
  0,1,2,3,4,5,6,7,8,9,10,11,12,13,A4,A5};
const int DELAY = 5; //Delay between cube layer alternations, in milliseconds. 
int cube[4][4][4];

//Setup
void setup(){
  //Setup Pin-Outputs
  for (int i=0; i<4;i++)
  pinMode(layer[i], OUTPUT);  
  for (int i; i<16; i++)
  pinMode(column[i], OUTPUT);  
  //Gets Random Seed from Analog Pin
  randomSeed(analogRead(5));
  clearCube();
}

void loop(){
  clearCube();
  render(1000);
  patternBlinkIn();
  fillCube();
  render(2000);
  patternBlinkOut();
  render(1000);
  patternSpiralTop(8);
  patternSpiralBottom(8);
  patternSpiralTopThenBottom(10);  
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
    if(cube[y][x][z]==0){
      cube[y][x][z]=1;
      count--;
      render(100);
      }
  }
  clearCube();
}

void patternBlinkOut(){
  int count, x, y, z;
  count = 8;
  fillCube();
  while(count > 0){
    x = random(2);
    y = random(2);
    z = random(2);
    if(cube[y][x][z]==1){
      cube[y][x][z]=0;
      count--;
      render(500);
    }
  }
  clearCube();
}

void patternSpiralTopThenBottom(int repetitions){
  int i;
  for (i=0;i<repetitions;i++){
    patternSpiralTop(1);
    patternSpiralBottom(1);
  }
}

void patternSpiralTop(int repetitions){
  int i;
  for (i=0;i<repetitions;i++){
    cube[1][0][0] = 1;
    render(100);
    clearCube();
    cube[1][1][0] = 1;
    render(100);
    clearCube();
    cube[1][1][1] = 1;
    render(100);
    clearCube();
    cube[1][0][1] = 1;
    render(100);
    clearCube();
  }
}

void patternSpiralBottom(int repetitions){
  int i;
  for (i=0;i<repetitions;i++){
    cube[0][0][0] = 1;
    render(100);
    clearCube();
    cube[0][1][0] = 1;
    render(100);
    clearCube();
    cube[0][1][1] = 1;
    render(100);
    clearCube();
    cube[0][0][1] = 1;
    render(100);
    clearCube();
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
    x = random(2);
    y = random(2);
    z = random(2);
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

//Function to draw cube map for specified number of milliseconds. 
//Alternates betwween layers for multiplexing.
//Draws the current binary cube matrix to the Arduino for 'pausetime' milliseconds.
void render(int pauseTime){
  long timer = 0;
  while(timer<=pauseTime){
    //**** Draw Top ****
    digitalWrite(layer[1], HIGH);
    for (int i=0;i<4;i++)
    {
      for (int j=0;j<4;j++)
      {
        if(cube[i][j][0] == 1){
          digitalWrite(column[i +4*j], HIGH);
        }
        else{
          digitalWrite(column[i +4*j], LOW);
        };
      }
    }
    delay(DELAY);
    digitalWrite(layer[1], LOW);

    //**** Draw Bottom ****
    digitalWrite(layer[0], HIGH);
    for (int i=0;i<4;i++)
    {
      for (int j=0;j<4;j++)
      {
        if(cube[i][j][0] == 1){
          digitalWrite(column[i +4*j], HIGH);
        }
        else{
          digitalWrite(column[i +4*j], LOW);
        };
      }
    }
    delay(DELAY);
    digitalWrite(layer[0], LOW);
    timer += DELAY * 2;
  }
}

//turn all LEDs off
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

//turn all LEDs on
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