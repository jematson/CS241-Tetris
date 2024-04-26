// buttons.h
// Header to define functions related to the buttons

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

// Set pinModes for the button pins
void begin_buttons(const int leftButton, const int rightButton, const int downButton, const int upButton)
{
  pinMode(leftButton, INPUT_PULLUP);
  pinMode(rightButton, INPUT_PULLUP);
  pinMode(downButton, INPUT_PULLUP);
  pinMode(upButton, INPUT_PULLUP);
}

// Check button states and do stuff if pressed
void check_left_button() {
  leftState = !digitalRead(leftButton);

  if(leftState && leftState != prevLeft) {
    currBitrimino = move_bitr_left(board, currBitrimino);
    leftState = true;
    startState = false;
  }
  prevLeft = leftState;
  delay(1);
}
void check_right_button() {
  rightState = !digitalRead(rightButton);

  if(rightState && rightState != prevRight) {
    currBitrimino = move_bitr_right(board, currBitrimino);
    rightState = true;
    startState = false;
  }
  prevRight = rightState;
  delay(1);
}
void check_down_button() {
  downState = !digitalRead(downButton);

  if(downState && downState != prevDown && !grounded) {
    currBitrimino = move_bitr_down(board, currBitrimino);
    downState = true;
    startState = false;
  }
  prevDown = downState;
  delay(1);
}
void check_up_button() {
  upState = !digitalRead(upButton);

  if(upState && upState != prevUp) {
    currBitrimino = hard_drop(board, currBitrimino);
    check_rows();
    upState = true;
    startState = false;
  }
  prevUp = upState;
  delay(1);
}