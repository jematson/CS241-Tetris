#pragma once

#include"data.h"
#include"bitrimino.h"
#include"board.h"

// Initialize button states
bool left_state = false;
bool prev_left = left_state;
bool right_state = false;
bool prev_right = right_state;
bool down_state = false;
bool prev_down = down_state;
bool up_state = false;
bool prev_up = up_state;

void begin_buttons(const int left_button, const int right_button, const int down_button, const int up_button)
{
  pinMode(left_button, INPUT_PULLUP);
  pinMode(right_button, INPUT_PULLUP);
  pinMode(down_button, INPUT_PULLUP);
  pinMode(up_button, INPUT_PULLUP);
}

// Check button states and do stuff if pressed
void checkLeftButton() {
  left_state = !digitalRead(leftButton);

  if(left_state && left_state != prev_left) {
    currBitrimino = move_bitr_left(board, currBitrimino);
    left_state = true;
    startState = false;
  }
  prev_left = left_state;
  delay(1);
}
void checkRightButton() {
  right_state = !digitalRead(rightButton);

  if(right_state && right_state != prev_right) {
    currBitrimino = move_bitr_right(board, currBitrimino);
    right_state = true;
    startState = false;
  }
  prev_right = right_state;
  delay(1);
}
void checkDownButton() {
  down_state = !digitalRead(downButton);

  if(down_state && down_state != prev_down && !grounded) {
    currBitrimino = move_bitr_down(board, currBitrimino);
    down_state = true;
    startState = false;
  }
  prev_down = down_state;
  delay(1);
}
void checkUpButton() {
  up_state = !digitalRead(upButton);

  if(up_state && up_state != prev_up) {
    currBitrimino = hard_drop(board, currBitrimino);
    check_rows();
    up_state = true;
    startState = false;
  }
  prev_up = up_state;
  delay(1);
}