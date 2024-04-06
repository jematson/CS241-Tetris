// CS 241 Final Project: Bitris Game
// Jenae Matson and Elliott Lewandowski

#include"display_pattern.h"
#include"buttons.h"
#include"bitrimino.h"
#include"config.h"

Bitrimino curr_bitrimino;

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
bool up_state = false;
bool prev_up = up_state;

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

bool check_debris_below(Bitrimino curr_bitrimino) {
  int num_patterns = sizeof(curr_bitrimino.pattern) / sizeof(curr_bitrimino.pattern[0]);
  for (int i=0; i<num_patterns; i++) {
    unsigned int low_block = curr_bitrimino.pattern[i];

    unsigned int high_bits = get_row_bits(low_block);
    unsigned int low_bits = get_col_bits(low_block);
    high_bits = high_bits << 1;
    // loop through rows of board
    for(int j = 0; j < 8; j++) {
      if((high_bits & board[j]) != 0) {
        if((low_bits & get_col_bits(board[j])) != 0) {
          return true;
        }
      }
    }
  }
  return false;
}

void checkCollision() {
  // Reached bottom of board, add to debris and make new bitrimino
  if(check_bottom_edge(curr_bitrimino)) {
    curr_bitrimino = create_bitrimino();
  } else if (check_debris_below(curr_bitrimino)) {
    curr_bitrimino = create_bitrimino();
  }
}

void check_rows() {
  // Loop through rows of board, starting at the bottom
  for(int i = 7; i >= 0; i--) {
    // check if the row has all columns filled
    if((board[i] & 0x00FF) == 0b11111111) {
      Serial.print("removing row ");
      Serial.println(i);
      remove_row(i);
    }
  }
}

void remove_row(int row) {
  Serial.println("In remove_row function");
  for(int i=row; i > 0; i--) {
    // replace current row with the row above it.
    board[i] = board[i-1];
    // shift the row to match the new spot
    board[i] = shift_rows_down(board[i]);
  }
  // add new empty row at top
  board[0] = 0b0000000100000000;
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
  Serial.println("****************");
  Serial.println("started up");
  Serial.println("****************");
  begin_shift_reg(dataPin, shiftPin, outputPin);
  pinMode(left_button, INPUT_PULLUP);
  pinMode(right_button, INPUT_PULLUP);
  pinMode(down_button, INPUT_PULLUP);

  // Create the first bitrimino and add it to the board
  //curr_bitrimino = create_bitrimino();
  curr_bitrimino = bitrimino_v;
  add_to_board(board, curr_bitrimino);
  Serial.println((unsigned int)board[0], BIN);
  Serial.println((unsigned int)board[1], BIN);
}

void loop() {
  display_board(board);
  checkLeftButton();
  checkRightButton();
  checkDownButton();
  if(prev_left || prev_right || prev_down) {
    check_rows();
    add_to_board(board, curr_bitrimino);
    Serial.println("-----------------");
    Serial.println((unsigned int)board[0], BIN);
    Serial.println((unsigned int)board[1], BIN);
    Serial.println("-----------------");
    checkCollision();
  }
}
