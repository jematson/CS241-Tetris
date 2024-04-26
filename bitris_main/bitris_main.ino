// CS 241 Final Project: Bitris Game
// Jenae Matson and Elliott Lewandowski

#include"display_pattern.h"
#include"buttons.h"
#include"bitrimino.h"
#include"data.h"
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
  checkLeftButton();
  checkRightButton();
  checkDownButton();
  checkUpButton();

  if(!startState)
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
  else{
    play_background_music();
  }

  add_to_board(board, currBitrimino);
  display_board(board);
}
