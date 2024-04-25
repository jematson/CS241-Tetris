#pragma once
#include"bitrimino.h"

// Button pins
const int leftButton = 10;
const int rightButton = 9;
const int upButton = 8;
const int downButton = 7;

//Shift register pins
const int dataPin = 11;
const int shiftPin = 12;
const int outputPin = 13;

// ********** Starting game state **********

Bitrimino curr_bitrimino;

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

// Starting points, displays "0000"
int points = 0;
unsigned int points_patterns[4]{
  0b0000000111111100,
  0b0000001011111100, 
  0b0000010011111100, 
  0b0000100011111100  
};


bool grounded = false; // Stores whether the bitrimino is on the ground or not
unsigned long ground_time = 0; // Stores the time when the player touched the ground
unsigned long slide_duration = 500; // Time player can slide after hitting the ground

unsigned long last_drop = millis();
unsigned long drop_time = 1000; // Time between autodrop intervals in millis

bool start_state = true; // Game stalls until a button is pressed
bool loss = false; // True when game is over
