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

void begin_buttons(const int leftButton, const int rightButton, const int downButton, const int upButton)
{
  pinMode(leftButton, INPUT_PULLUP);
  pinMode(rightButton, INPUT_PULLUP);
  pinMode(downButton, INPUT_PULLUP);
  pinMode(upButton, INPUT_PULLUP);
}

// Check button states and do stuff if pressed
void check_left_button() {
  left_state = !digitalRead(leftButton);

  if(left_state && left_state != prev_left) {
    curr_bitrimino = move_bitr_left(board, curr_bitrimino);
    left_state = true;
    start_state = false;
  }
  prev_left = left_state;
  delay(1);
}
void check_right_button() {
  right_state = !digitalRead(rightButton);

  if(right_state && right_state != prev_right) {
    curr_bitrimino = move_bitr_right(board, curr_bitrimino);
    right_state = true;
    start_state = false;
  }
  prev_right = right_state;
  delay(1);
}
void check_down_button() {
  down_state = !digitalRead(downButton);

  if(down_state && down_state != prev_down && !grounded) {
    curr_bitrimino = move_bitr_down(board, curr_bitrimino);
    down_state = true;
    start_state = false;
  }
  prev_down = down_state;
  delay(1);
}
void check_up_button() {
  up_state = !digitalRead(upButton);

  if(up_state && up_state != prev_up) {
    curr_bitrimino = hard_drop(board, curr_bitrimino);
    check_rows();
    up_state = true;
    start_state = false;
  }
  prev_up = up_state;
  delay(1);
}