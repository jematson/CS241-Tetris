// CS 241 Final Project: Bitris Game
// Jenae Matson and Elliott Lewandowski

#include"display_pattern.h"
#include"buttons.h"
#include"bitrimino.h"
#include"config.h"

// Checks if correct time interval has passed to drop block
void check_auto_drop()
{
  if(millis() - last_drop > drop_time)
  {
    last_drop = millis();
    move_bitr_down(board, curr_bitrimino);
    add_to_board(board, curr_bitrimino);
  }
}

void checkCollision() {
  // Reached bottom of board, add to debris and make new bitrimino
  if(check_bottom_edge(curr_bitrimino)) {
    check_rows();
    curr_bitrimino = create_bitrimino();
    
    last_drop = millis();
  // Hit debris pile, add to debris and make new bitrimino
  } else if (check_debris_below(board, curr_bitrimino)) {
    check_rows();
    curr_bitrimino = create_bitrimino();
    
    last_drop = millis();
  }
}

void check_rows() {
  // Loop through rows of board, starting at the bottom
  for(int i = 0; i <= 7; i++) {
    // check if the row has all columns filled
    if((board[i] & 0x00FF) == 0b11111111) {
      Serial.print("removing row ");
      Serial.println(i);
      remove_row(i);
      // If row cleared, add a point and display
      points ++;
      Serial.print("Points: ");
      Serial.println(points);
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

  // Set pinmodes for shift registers and buttons
  begin_shift_reg(dataPin, shiftPin, outputPin);
  begin_buttons(left_button, right_button, down_button, up_button);

  // Create the first bitrimino and add it to the board
  curr_bitrimino = create_bitrimino();
  add_to_board(board, curr_bitrimino);
}

void loop() {
  check_auto_drop();
  display_board(board);
  checkLeftButton();
  checkRightButton();
  checkDownButton();
  checkUpButton();
  
  if(right_state || left_state || down_state || up_state) {
    add_to_board(board, curr_bitrimino);
  }
  checkCollision();
}
