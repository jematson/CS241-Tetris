// CS 241 Final Project: Tetris Game
// Jenae Matson and Elliott Lewandowski

#include"display_pattern.h"

// Declare Pin constants
//const int dataPin = 11;
//const int shiftPin = 12;
//const int outputPin = 13;

const int left_button = 10;
const int right_button = 9;
const int up_button = 8;
const int down_button = 7;

// Define starting bitriminos
typedef enum {
  bitrimino_h = 0b0000000100011000,
  bitrimino_v = 0b0000001100001000
} bitriminoes;

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

// Movement functions
// Take pattern and shift bits as needed to move item
unsigned int moveRight(unsigned int curr_pattern) {
  remove_from_board(board, curr_pattern);
  // save the high bits, the rows
  unsigned int newPattern = curr_pattern & 0xFF00;
  // copy the low bits, the cols
  unsigned int oldCols = curr_pattern & 0x00FF;
  // left shift the cols by 1
  oldCols = oldCols << 1;
  //       | rows  | cols  |
  // ex. 0b7654321076543210
  //     0b0000000100001000
  // to  0b0000000100010000

  // recombine the old rows with the old cols
  newPattern = newPattern | oldCols;
  add_to_board(board, newPattern);
  return newPattern;
}
unsigned int moveLeft(unsigned int curr_pattern) {
  remove_from_board(board, curr_pattern);
  // save the high bits, the rows
  unsigned int newPattern = curr_pattern & 0xFF00;
  // copy the low bits, the cols
  unsigned int oldCols = curr_pattern & 0x00FF;
  // right shift the cols by 1
  oldCols = oldCols >> 1;
  //       | rows  | cols  |
  // ex. 0b7654321076543210
  //     0b0000000100001000
  // to  0b0000000100000100

  // recombine the old rows with the new cols
  newPattern = newPattern | oldCols;
  add_to_board(board, newPattern);
  return newPattern;
}
unsigned int moveDown(unsigned int curr_pattern) {
  remove_from_board(board, curr_pattern);
  // save the low bits, the cols
  unsigned int newPattern = curr_pattern & 0x00FF;
  // copy the high bits, the rows
  unsigned int oldRows = curr_pattern & 0xFF00;
  // left shift the rows by 1 to move down
  oldRows = oldRows << 1;
  //       | rows  | cols  |
  // ex. 0b7654321076543210
  //     0b0000100000001000
  // to  0b0001000000001000

  // recombine the new rows with the old cols
  newPattern = oldRows | newPattern;
  add_to_board(board, newPattern);
  return newPattern;
}

//unsigned int bitrimino = 0b0000000100001000;
unsigned int curr_bitrimino = bitrimino_h;

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
int x_pos = 4; //Starting 
int y_pos = 1;

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

  if(left_state && left_state != prev_left && x_pos > 1) {
    curr_bitrimino = moveLeft(curr_bitrimino);
    x_pos--;
    left_state = true;
  }
  prev_left = left_state;
  delay(1);
}
void checkRightButton() {
  right_state = !digitalRead(right_button);

  if(right_state && right_state != prev_right && x_pos < 8) {
    curr_bitrimino = moveRight(curr_bitrimino);
    x_pos++;
    right_state = true;
  }
  prev_right = right_state;
  delay(1);
}
void checkDownButton() {
  down_state = !digitalRead(down_button);

  if(down_state && down_state != prev_down && y_pos < 8) {
    curr_bitrimino = moveDown(curr_bitrimino);
    y_pos++;
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

void add_to_board(unsigned int board[8], unsigned int bitrimino) {
  unsigned int high_bits = bitrimino & 0xFF00;
  for(int i = 0; i < 8; i++) {
    if((high_bits & board[i]) != 0) {
      board[i] = board[i] | bitrimino;
    }
  }
}

void remove_from_board(unsigned int board[8], unsigned int bitrimino) {
  unsigned int bitr_high_bits = bitrimino & 0xFF00;
  
  for(int i = 0; i < 8; i++) {
    if((bitr_high_bits & board[i]) != 0) {
      unsigned int board_high_bits = board[i] & 0xFF00;
      unsigned int board_low_bits = board[i] & 0x00FF;
      unsigned int bitr_low_bits = bitrimino & 0x00FF;
      board[i] = board_high_bits | ((~bitr_low_bits) & board_low_bits);
    }
  }
}

void setup() {
  Serial.begin(57600);
  Serial.println("started up");
  begin_shift_reg(dataPin, shiftPin, outputPin);
  pinMode(left_button, INPUT_PULLUP);
  pinMode(right_button, INPUT_PULLUP);
  pinMode(down_button, INPUT_PULLUP);
}

void loop() {
  checkLeftButton();
  checkRightButton();
  checkDownButton();
  //send_pattern(curr_bitrimino, 1);
  display_board(board);
}
