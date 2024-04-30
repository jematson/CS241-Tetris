// **********************************
// bitris_main.ino
// Elliot Lewandowski & Jenae Matson
// last updated: 2024-4-30
// CS 241 Final Project: Bitris
//  Code to run the game Bitris
//  on an Arduino Uno.
// **********************************


#include"data.h"
#include"bitrimino.h"
#include"display_pattern.h"
#include"buttons.h"
#include"board.h"


void setup() {

  randomSeed(analogRead(A0));
  Serial.begin(57600);
  Serial.println("****************");
  Serial.println("started up");
  Serial.println("****************");

  // Set pinmodes for shift registers and buttons
  begin_shift_reg(dataPin, shiftPin, outputPin);
  begin_buttons(leftButton, rightButton, downButton, upButton);
  begin_sound_pins();

  // Create the first bitrimino and add it to the board
  currBitrimino = create_bitrimino(board);
  add_to_board(board, currBitrimino);
  play_row_clear();
}

void loop() {

  check_left_button();
  check_right_button();
  check_down_button();
  check_up_button();

  if(!startState) {          // Run these functions if we are currently playing
  
    update_points_patterns();
    attempt_add_to_debris();
    check_auto_drop();

    check_collision();
    if(loss) {
    
      game_over();
    }
  }
  else {                     // Run this function if we are not currently playing

    play_background_music();
  }

  add_to_board(board, currBitrimino);
  display_board(board);
}
