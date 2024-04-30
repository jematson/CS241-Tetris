#pragma once

#include"data.h"
#include"bitrimino.h"
#include"sound_comm.h"
#include"pointboard.h"

// Checks if correct time interval has passed to drop block
void check_auto_drop() {

  if(millis() - lastDrop > dropTime && !grounded) {
  
    lastDrop = millis();
    move_bitr_down(board, currBitrimino);
  }
}

void check_collision() {
  
  if(check_bottom_edge(currBitrimino) || check_debris_below(board, currBitrimino)) { // Reached bottom of board or hit debris pile
    if(grounded == false)
    {
      groundTime = millis();
    }
    grounded = true;
  } 
  else {                // Resets grounded state if bitrimino no longer has debris/ground below it
    grounded = false;
  }
}

void game_over() {

  Serial.println("Game is over");
  play_game_over();

  board[0] = 0b0000000100000000;
  board[1] = 0b0000001000000000;
  board[2] = 0b0000010000000000;
  board[3] = 0b0000100000000000;
  board[4] = 0b0001000000000000;
  board[5] = 0b0010000000000000;
  board[6] = 0b0100000000000000;
  board[7] = 0b1000000000000000;

  points = 0;
  startState = true;
  loss = false;
}

void remove_row(int row) {

  play_row_clear();
  for(int i=row; i > 0; i--) {
   
    board[i] = board[i-1];                // Replace current row with the row above it.
    
    board[i] = shift_rows_down(board[i]); // Shift the row to match the new spot
  }
 
  board[0] = 0b0000000100000000;          // Add new empty row at top
}

void check_rows() {

  for(int i = 0; i <= 7; i++) {             // Loop through rows of board, starting at the bottom
    
    if((board[i] & 0x00FF) == 0b11111111) { // Check if the row has all columns filled

      Serial.print("removing row ");
      Serial.println(i);
      remove_row(i);                       
      
      points ++;                            // If row cleared, add a point and display
      Serial.print("Points: ");
      Serial.println(points);
    }
  }
}

// Adds the current bitrimino to the debris pile if it is grounded and 
void attempt_add_to_debris() {

   if(grounded == true && millis() - groundTime > dropTime) {

      check_rows();
      currBitrimino = create_bitrimino(board);
    
      lastDrop = millis();
   }
}

void display_board(unsigned int board[8]) {
  
  send_pattern(board[0], pointsPatterns[0], 1);
  send_pattern(board[1], pointsPatterns[0], 1);
  send_pattern(board[2], pointsPatterns[1], 1);
  send_pattern(board[3], pointsPatterns[1], 1);
  send_pattern(board[4], pointsPatterns[2], 1);
  send_pattern(board[5], pointsPatterns[2], 1);
  send_pattern(board[6], pointsPatterns[3], 1);
  send_pattern(board[7], pointsPatterns[3], 1);
}
