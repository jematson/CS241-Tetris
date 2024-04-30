#pragma once

bool loss = false; // True when game is over

// Button pins
const int leftButton = 10;
const int rightButton = 9;
const int upButton = 8;
const int downButton = 7;

//Shift register pins
const int dataPin = 11;
const int shiftPin = 12;
const int outputPin = 13;

// Bitrimino struct
// Stores bit patterns in array
struct Bitrimino {
  unsigned int pattern[2];
};

// Starting game state
Bitrimino currBitrimino;

// Empty Game board
unsigned int board[8] {
  0b0000000100000000,
  0b0000001000000000,
  0b0000010000000000,
  0b0000100000000000,
  0b0001000000000000,
  0b0010000000000000,
  0b0100000000000000,
  0b1000000000000000
};
// Starting points, set patterns to 0000
int points = 0;
unsigned int pointsPatterns[4]{
  0b0000000111111100,
  0b0000001011111100, 
  0b0000010011111100, 
  0b0000100011111100  
};


bool grounded = false;             // True if the bitrimino is on the ground
unsigned long groundTime = 0;      // Stores most recent time the current bitrimino touched the ground
unsigned long slideDuration = 500; // Time after hitting the ground before the bitrimino is placed

unsigned long lastDrop = millis(); // Stores last time an autodrop was performed
unsigned long dropTime = 1000;     // Time between autodrop intervals in millis

bool startState = true;            // Game stalls until a button is pressed

