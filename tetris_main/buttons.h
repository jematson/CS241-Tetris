#pragma once

#include"config.h"
#include"bitrimino.h"

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
  left_state = !digitalRead(left_button);

  if(left_state && left_state != prev_left) {
    curr_bitrimino = move_bitr_left(board, curr_bitrimino);
    left_state = true;
  }
  prev_left = left_state;
  delay(1);
}
void checkRightButton() {
  right_state = !digitalRead(right_button);

  if(right_state && right_state != prev_right) {
    curr_bitrimino = move_bitr_right(board, curr_bitrimino);
    right_state = true;
  }
  prev_right = right_state;
  delay(1);
}
void checkDownButton() {
  down_state = !digitalRead(down_button);

  if(down_state && down_state != prev_down) {
    curr_bitrimino = move_bitr_down(board, curr_bitrimino);
    down_state = true;
  }
  prev_down = down_state;
  delay(1);
}
void checkUpButton() {
  up_state = !digitalRead(up_button);

  if(up_state && up_state != prev_up) {
    //hard_drop();
    up_state = true;
  }
  prev_up = up_state;
  delay(1);
}