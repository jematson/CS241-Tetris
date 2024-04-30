// **********************************
// buttons.h
// Elliot Lewandowski & Jenae Matson
// last updated: 2024-4-30
// Header for the buttons and
//  associated functions
// **********************************

#pragma once

#include"data.h"
#include"bitrimino.h"
#include"board.h"

// Initialize button states
bool leftState = false;
bool prevLeft = leftState;
bool rightState = false;
bool prevRight = rightState;
bool downState = false;
bool prevDown = downState;
bool upState = false;
bool prevUp = upState;

// Setup button pins (call from setup)
void begin_buttons(const int left_button, const int right_button, const int down_button, const int up_button) {

  pinMode(left_button, INPUT_PULLUP);
  pinMode(right_button, INPUT_PULLUP);
  pinMode(down_button, INPUT_PULLUP);
  pinMode(up_button, INPUT_PULLUP);
}

// Button checking functions
// 
void check_left_button() {

  leftState = !digitalRead(leftButton);

  if(leftState && leftState != prevLeft) {               // Check that the button is pressed down and changed state from our last check

    currBitrimino = move_bitr_left(board, currBitrimino); // Left button moves bitrimino to the left one block
    leftState = true;
    startState = false;
  }

  prevLeft = leftState;
  delay(1);
}

void check_right_button() {

  rightState = !digitalRead(rightButton);

  if(rightState && rightState != prevRight) {

    currBitrimino = move_bitr_right(board, currBitrimino);  // Right button moves bitrimino to the right one block
    rightState = true;
    startState = false;
  }

  prevRight = rightState;
  delay(1);
}

void check_down_button() {

  downState = !digitalRead(downButton);

  if(downState && downState != prevDown && !grounded) {

    currBitrimino = move_bitr_down(board, currBitrimino); // Down button moves bitrimino down one block
    downState = true;
    startState = false;
  }

  prevDown = downState;
  delay(1);
}

void check_up_button() {

  upState = !digitalRead(upButton);

  if(upState && upState != prevUp) {

    currBitrimino = hard_drop(board, currBitrimino);  // Up button performs a hard drop (moves bitrimino to bottom of board)
    check_rows();
    upState = true;
    startState = false;
  }

  prevUp = upState;
  delay(1);
}
