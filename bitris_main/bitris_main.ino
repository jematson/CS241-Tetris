// CS 241 Final Project: Bitris Game
// Jenae Matson and Elliott Lewandowski
// bitris_main.ino
// Code for running the game Bitris on an Arduino Uno

#include"display_pattern.h"
#include"buttons.h"
#include"bitrimino.h"
#include"data.h"
#include"board.h"

void setup() {
  // Seed the randomizer for generating bitriminos
  randomSeed(analogRead(A0));

  //Serial setup
  Serial.begin(57600);
  Serial.println("****************");
  Serial.println("started up");
  Serial.println("****************");

  // Set pinmodes for shift registers, buttons, and sound effects
  begin_shift_reg(dataPin, shiftPin, outputPin);
  begin_buttons(leftButton, rightButton, downButton, upButton);
  begin_sound_pins();

  // Create the first bitrimino and add it to the board
  curr_bitrimino = create_bitrimino();
  add_to_board(board, curr_bitrimino);

  // Initialize sound effects
  play_row_clear();
}

void loop() {
  // Check if a button has been pressed
  check_left_button();
  check_right_button();
  check_down_button();
  check_up_button();

  // Game loop
  if(!start_state)
  {
    update_points_patterns();
    attempt_add_to_debris();
    check_auto_drop();

    check_collision();
  }
  // If waiting between games, play Tetris theme song
  else{
    play_background_music();
  }

  // Display the board, including the current bitrimino
  add_to_board(board, curr_bitrimino);
  display_board(board);
}
