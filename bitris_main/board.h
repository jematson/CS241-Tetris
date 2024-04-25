#pragma once

#include"data.h"
#include"bitrimino.h"
#include"sound_comm.h"
#include"pointboard.h"

// Checks if correct time interval has passed to drop block
void check_auto_drop()
{
  if(millis() - last_drop > drop_time && !grounded)
  {
    last_drop = millis();
    move_bitr_down(board, curr_bitrimino);
    //add_to_board(board, curr_bitrimino);
  }
}

void checkCollision() {
  // Reached bottom of board or hit debris pile
  if(check_bottom_edge(curr_bitrimino) || check_debris_below(board, curr_bitrimino)) {
    if(grounded == false)
    {
      ground_time = millis();
    }
    grounded = true;
  } 
  // Resets grounded state if bitrimino no longer has debris/ground below it
  else { 
    grounded = false;
  }
}

void game_over()
{
  Serial.println("Game is over");
  playGameOver();

  board[0] = 0b0000000100000000;
  board[1] = 0b0000001000000000;
  board[2] = 0b0000010000000000;
  board[3] = 0b0000100000000000;
  board[4] = 0b0001000000000000;
  board[5] = 0b0010000000000000;
  board[6] = 0b0100000000000000;
  board[7] = 0b1000000000000000;

  points = 0;
  start_state = true;
}

void remove_row(int row) {
  playRowClear();
  for(int i=row; i > 0; i--) {
    // replace current row with the row above it.
    board[i] = board[i-1];
    // shift the row to match the new spot
    board[i] = shift_rows_down(board[i]);
  }
  // add new empty row at top
  board[0] = 0b0000000100000000;
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

// Adds the current bitrimino to the debris pile if it is grounded and 
void attempt_add_to_debris()
{
   if(grounded == true && millis() - ground_time > drop_time) {
      if(check_upper_rows(board, curr_bitrimino) && check_middle_cols(board, curr_bitrimino))
      {
        game_over();
      }
      check_rows();
      curr_bitrimino = create_bitrimino();
    
      last_drop = millis();
   }
}

void display_board(unsigned int board[8]) {
  send_pattern(board[0], points_patterns[0], 1);
  send_pattern(board[1], points_patterns[0], 1);
  send_pattern(board[2], points_patterns[1], 1);
  send_pattern(board[3], points_patterns[1], 1);
  send_pattern(board[4], points_patterns[2], 1);
  send_pattern(board[5], points_patterns[2], 1);
  send_pattern(board[6], points_patterns[3], 1);
  send_pattern(board[7], points_patterns[3], 1);
}
