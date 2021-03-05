#include <Arduino.h>

// Define Pin Numbers for the Esp32 Dev Board
// connections to shift Registers of LedPanel
int dataPin = 2;
int latchPin = 4;
int clockPin = 5;

// Arrays to hold values to be send to shift registers
int anode_values[8];
int red_values[8];
int green_values[8];
int blue_values[8];

// Final array to send the shift registers with correct order
int register_values[32];

// Details of the movement to be displayed (should recieve via bluetooth)
String moveNotation, moveEnd, moveStart;

// Details should extract from the movement details
int startRow, startCol;
int endRow, endCol;

// cells to be lightup in the matrix
int cells[8][8] = {
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0}
};

// set of functions need
void clearCells();
void displayPanel();
void clearRegisters();
void writeRegisters();
void setRegisterPin(char regType, int index, boolean value);
void decodeMove(String moveNotation, String moveEnd, String moveStart);

void setup() {
  // LedPanel
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
}

// function that set all the values of cell 2d array to zero 
void clearCells(){
  for (int i = 0; i < 8; i++){
    for (int j = 0; j < 8; j++){
      cells[i][j] = 0;
    }
  }
}

// function that clear all register values in order to off the ledPanel 
void clearRegisters(){
  for(int i = 0; i < 8; i++){
    // Since the led Panel is common anode: 
    // in order to off a led - anode should be LOW and cathodes shoul be HIGH  
    anode_values[i] = LOW;
    red_values[i] = HIGH;
    green_values[i] = HIGH;
    blue_values[i] = HIGH;
  }
}

// function to assign HIGH/LOW to required register index
void setRegisterPin(char regType, int index, boolean value){
  if (regType == 'R'){
    red_values[index] = value;
  }else if (regType == 'G'){
    green_values[index] = value;
  }else if(regType == 'B'){
    blue_values[index] =value;
  }else if(regType == 'A'){
    anode_values[index] = value;
  }
}
