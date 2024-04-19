// CS 241 Final Project: Bitris Game
// Jenae Matson and Elliott Lewandowski

#include"display_pattern.h"
#include"buttons.h"
#include"bitrimino.h"
#include"config.h"
#include"board.h"



void setup() {
  randomSeed(analogRead(A0));
  Serial.begin(57600);
  Serial.println("****************");
  Serial.println("started up");
  Serial.println("****************");

  // Set pinmodes for shift registers and buttons
  begin_shift_reg(dataPin, shiftPin, outputPin);
  begin_buttons(left_button, right_button, down_button, up_button);
  begin_sound_pins();

  // Create the first bitrimino and add it to the board
  curr_bitrimino = create_bitrimino(board);
  add_to_board(board, curr_bitrimino);
  playRowClear();
}

void loop() {
  checkLeftButton();
  checkRightButton();
  checkDownButton();
  checkUpButton();

  if(!start_state)
  {
    update_points_patterns();
    attempt_add_to_debris();
    check_auto_drop();

    checkCollision();
    if(loss)
    {
      game_over();
    }
  }

  add_to_board(board, curr_bitrimino);
  display_board(board);
}
