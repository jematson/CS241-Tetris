// CS 241 Final Project: Tetris Game
// Jenae Matson and Elliott Lewandowski

#include"display_pattern.h"
#include"buttons.h"
#include"bitrimino.h"
#include"config.h"

// Define Bitrimino Types
// Horizontal Bitrimino
Bitrimino bitrimino_h = { .pattern = {0b0000000100011000} };
// Vertical Bitrimino
Bitrimino bitrimino_v = { .pattern = {0b0000001100001000} };
// Forward Diagonal Bitrimino
Bitrimino bitrimino_f = { .pattern = {0b0000000100010000, 0b0000001000001000} };
// Back Diagonal Bitrimino
Bitrimino bitrimino_b = { .pattern = {0b0000000100001000, 0b0000001000010000} };

Bitrimino curr_bitrimino = bitrimino_v;

/*
    8x8 coordinate system
      12345678
      ________
    1|00000000
    2|00000000
    3|00000000
    4|00000000
    5|00000000
    6|00000000
    7|00000000
    8|00000000
*/

// Start with an empty board
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

// Initialize button states
bool left_state = false;
bool prev_left = left_state;
bool right_state = false;
bool prev_right = right_state;
bool down_state = false;
bool prev_down = down_state;

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

void display_board(unsigned int board[8]) {
  send_pattern(board[0], 1);
  send_pattern(board[1], 1);
  send_pattern(board[2], 1);
  send_pattern(board[3], 1);
  send_pattern(board[4], 1);
  send_pattern(board[5], 1);
  send_pattern(board[6], 1);
  send_pattern(board[7], 1);
}


void setup() {
  randomSeed(analogRead(A0));
  Serial.begin(57600);
  Serial.println("started up");
  begin_shift_reg(dataPin, shiftPin, outputPin);
  pinMode(left_button, INPUT_PULLUP);
  pinMode(right_button, INPUT_PULLUP);
  pinMode(down_button, INPUT_PULLUP);
}

void loop() {
  display_board(board);
  checkLeftButton();
  checkRightButton();
  checkDownButton();
  //send_pattern(curr_bitrimino, 1);
}
