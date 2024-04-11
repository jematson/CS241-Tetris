#pragma once
#include"bitrimino.h"

// Button pins
const int left_button = 10;
const int right_button = 9;
const int up_button = 8;
const int down_button = 7;

//Shift register pins
const int dataPin = 11;
const int shiftPin = 12;
const int outputPin = 13;

// Starting game state, empty board, 0 points
Bitrimino curr_bitrimino;

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

int points = 0;

bool grounded = false; // Stores wether the bitrimino is on the ground or not
unsigned long ground_time = 0; // Stores the time when the player touched the ground
unsigned long slide_duration = 500; // Time player can slide after hitting the ground

unsigned long last_drop = millis();
unsigned long drop_time = 1000; // Time between autodrop intervals in millis
