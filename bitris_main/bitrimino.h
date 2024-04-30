#pragma once
#include"data.h"
#include"sound_comm.h"


// Define Bitrimino Types
Bitrimino bitrimino_h = { .pattern = {0b0000000100011000} };                     // Horizontal Bitrimino

Bitrimino bitrimino_v = { .pattern = {0b0000001000001000, 0b0000000100001000} }; // Vertical Bitrimino

Bitrimino bitrimino_f = { .pattern = {0b0000001000001000, 0b0000000100010000} }; // Forward Diagonal Bitrimino

Bitrimino bitrimino_b = { .pattern = {0b0000001000010000, 0b0000000100001000} }; // Back Diagonal Bitrimino

// Return high bits (rows) from a bit pattern
unsigned int get_row_bits(unsigned int pattern) {
  return pattern & 0xFF00;
}
// Return low bits (cols) from a bit pattern
unsigned int get_col_bits(unsigned int pattern) {
  return pattern & 0x00FF;
}

// Return the number of bit patterns a Bitrimino object has (1 or 2)
int num_patterns(Bitrimino bitrimino) {
  return sizeof(bitrimino.pattern) / sizeof(bitrimino.pattern[0]);
}

// Returns a new randomly selected bitrimino pattern located 
//    in the top two rows and checks for game over
Bitrimino create_bitrimino(unsigned int board[8]) {
  Bitrimino newBitr;
  switch(random(1, 5)) {
    case 1:
      newBitr = bitrimino_h;
      break;
    case 2:
      newBitr =  bitrimino_v;
      break;
    case 3:
      newBitr =  bitrimino_f;
      break;
    case 4:
      newBitr =  bitrimino_b; 
      break;
  }

  //Game Over Logic:

  // Get top two rows of the board
  unsigned int boardTopRow = get_col_bits(board[0]);
  unsigned int boardSecRow = get_col_bits(board[1]);

  // Check if the bitrimino is overlapping with anything in the top two rows
  for (int i=0; i < num_patterns(newBitr); i++) {
    unsigned int bitrCols = get_col_bits(newBitr.pattern[i]);
    if(((bitrCols & boardTopRow) != 0) || ((bitrCols & boardSecRow) != 0))
    {
      loss = true;
    }
  }

  return newBitr;;
}


//************************************
//  Move Bitrimino Pattern Functions
//************************************

// Shift the col bits of a bit pattern to move right on the board
unsigned int shift_cols_right(unsigned int pattern) {
  
  unsigned int newPattern = get_row_bits(pattern);  // Save the old rows
  unsigned int newCols = get_col_bits(pattern);     // Copy the cols

  newCols = newCols << 1;                           // The patterns are backwards so we must leftshift to move right
  newPattern = newPattern | newCols;                // Recombine the old rows with the new cols and return

  return newPattern;
}

// Shift the col bits of a bit pattern to move left on the board
unsigned int shift_cols_left(unsigned int pattern) {
  
  unsigned int newPattern = get_row_bits(pattern);
  unsigned int newCols = get_col_bits(pattern);
    
  newCols = newCols >> 1;
  newPattern = newPattern | newCols;

  return newPattern;
}

// Shift the row bits of a bit pattern to move down on the board
unsigned int shift_rows_down(unsigned int pattern) {
 
  unsigned int newPattern = get_col_bits(pattern);
  unsigned int newRows = get_row_bits(pattern);
  
  newRows = newRows << 1;                           // Left shifting the rows corresponds to a downward movement
  newPattern = newRows | newPattern;

  return newPattern;
}

//******************************
//  Update Board Functions
//******************************

// Add the given Bitrimino object to the board
void add_to_board(unsigned int board[8], Bitrimino& bitrimino) {
 
  for(int j = 0; j < 8; j++) {                          // iterate over the rows of the board
    
    for (int i=0; i < num_patterns(bitrimino); i++) {   // iterate over the patterns of the bitrimino
    
      unsigned int bitrRows = get_row_bits(bitrimino.pattern[i]);
        
      if((bitrRows & board[j]) != 0) {                // If the bitrimino has a block in this row of the board, add it to the row.

        board[j] = board[j] | bitrimino.pattern[i];
      }
    }
  }
}

// Remove the given Bitrimino object from the board
void remove_from_board(unsigned int board[8], Bitrimino& bitrimino) {
  
  for(int i = 0; i < 8; i++) {                                   // loop through rows of board

    for (int j=0; j < num_patterns(bitrimino); j++) {
      
      if((get_row_bits(bitrimino.pattern[j]) & board[i]) != 0) { // Checking if the bitrimino has something in the ith row of the board

        unsigned int boardRows = get_row_bits(board[i]);
        unsigned int boardCols = get_col_bits(board[i]);
        unsigned int bitrCols = get_col_bits(bitrimino.pattern[j]);
        board[i] = boardRows | ((~bitrCols) & boardCols);
      }
    }
  }
}


//************************************
//  Position/Edge Checking Functions
//************************************
// true = hitting edge or debris

bool check_right_edge(unsigned int board[8], Bitrimino& currBitrimino) {
  
  remove_from_board(board, currBitrimino);                             // remove the bitrimino from the board so it doesn't count itself as debris
  
  for (int i=0; i < num_patterns(currBitrimino); i++) {                // Loop through patterns of Bitrimino
    unsigned int bitrCols = get_col_bits(currBitrimino.pattern[i]);
    unsigned int bitrRows = get_row_bits(currBitrimino.pattern[i]);
    
    if((bitrCols & 0x0080) != 0) {                                      //  0x0080 corresponds to the right edge of the board, 
                                                                        //      Check if current pattern is at the right edge of the board
      return true;
    } 
    
    for (int j = 0; j < 8; j++) {                                      // Check if the bitrimino is running into debris on the right

      if((bitrRows & get_row_bits(board[j])) != 0 && ((bitrCols << 1) & get_col_bits(board[j])) != 0) {

        return true;
      }
    }
  }
  return false;
}

bool check_left_edge(unsigned int board[8], Bitrimino& currBitrimino) {

  remove_from_board(board, currBitrimino);

  for (int i=0; i < num_patterns(currBitrimino); i++) {

    unsigned int bitrCols = get_col_bits(currBitrimino.pattern[i]);
    unsigned int bitrRows = get_row_bits(currBitrimino.pattern[i]);

    if((bitrCols & 0x0001) != 0) {                                     // 0x0001 Corresponds to the left edge of the board
    
      return true;
    }
   
    for (int j = 0; j < 8; j++) {

      if((bitrRows & get_row_bits(board[j])) != 0 && ((bitrCols >> 1) & get_col_bits(board[j])) != 0) {

        return true;
      }
    }
  }
  return false;
}

bool check_bottom_edge(Bitrimino& currBitrimino) {
  for (int i=0; i < num_patterns(currBitrimino); i++) {

    unsigned int bitrRows = get_row_bits(currBitrimino.pattern[i]);
   
    if((bitrRows & 0x8000) != 0) {                                      // Check if the bitrimino is at the bottom of the board

      return true;
    }
  }
  return false;
}

// Checks the for collision with previously placed bitriminos
bool check_debris_below(unsigned int board[8], Bitrimino& currBitrimino) {
 
  remove_from_board(board, currBitrimino);             // remove the bitrimino from the board so it doesn't count itself as debris

  for (int i=0; i < num_patterns(currBitrimino); i++) {

    unsigned int lowBlock = currBitrimino.pattern[i];

    unsigned int bitrRows = get_row_bits(lowBlock);
    unsigned int bitrCols = get_col_bits(lowBlock);

    bitrRows = bitrRows << 1;

    for(int j = 0; j < 8; j++) {                       // Loop over the board

      if((bitrRows & board[j]) != 0) {                 // Check if the current row of the board would the bitrimino after a down shift

        if((bitrCols & get_col_bits(board[j])) != 0) { // Check if there is overlap between the bitr cols and board cols

          add_to_board(board, currBitrimino);          // Undo initial remove_from_board
          return true;
        }
      }
    }
  }

  add_to_board(board, currBitrimino);                  // Undo initial remove_from_board
  return false;
}

// Checks if the bitr is in upper row
bool check_upper_rows(unsigned int board[8], Bitrimino& currBitrimino)
{
  for (int i=0; i < num_patterns(currBitrimino); i++) {
    unsigned int bitrRows = get_row_bits(currBitrimino.pattern[i]);
    if((bitrRows & 0x0300) != 0)                       // Checks if bitrimino has an entry in the top two rows of the board
    {
      return true;
    }
  }
  return false;
}

// Checks if bitr is in the middle cols
bool check_middle_cols(unsigned int board[8], Bitrimino& currBitrimino)
{
  for (int i=0; i < num_patterns(currBitrimino); i++) {
  unsigned int bitrCols = get_col_bits(currBitrimino.pattern[i]);
    if((bitrCols & 0x0018) != 0)                       // Checks if bitrimino has an entry in the top two rows of the board
    {
      return true;
    }
  }
  return false;
}

//************************************
//  Move Bitrimino Functions
//************************************

// Shift the bit pattern(s) of the given bitrimino so the piece moves one block right
Bitrimino move_bitr_right(unsigned int board[8], Bitrimino& currBitrimino) {

  if(!check_right_edge(board, currBitrimino)) {                              // If not on the edge of the board move 
  
    for (int i=0; i < num_patterns(currBitrimino); i++) {
      
      currBitrimino.pattern[i] = shift_cols_right(currBitrimino.pattern[i]); // Shift the column bits of all current bitrimino patterns right
    }
  }

  return currBitrimino;
}

// Shift the bit pattern(s) of the given bitrimino so the piece moves one block left
Bitrimino move_bitr_left(unsigned int board[8], Bitrimino& currBitrimino) {

  if(!check_left_edge(board, currBitrimino)) {                               // If not on the edge of the board move
  
    for (int i=0; i < num_patterns(currBitrimino); i++) {
      
      currBitrimino.pattern[i] = shift_cols_left(currBitrimino.pattern[i]); // Shift the column bits of all current bitrimino patterns left  
    }
  }

  return currBitrimino;
}

// Shift the bit pattern(s) of the given bitrimino so the piece moves one block down
Bitrimino move_bitr_down(unsigned int board[8], Bitrimino& currBitrimino) {
  
  remove_from_board(board, currBitrimino);                                  // Remove the bitrimino from the board

  for (int i=0; i < num_patterns(currBitrimino); i++) {
    
    currBitrimino.pattern[i] = shift_rows_down(currBitrimino.pattern[i]);   // Shift the row bits of all current bitrimino patterns left  
  }

  return currBitrimino;
}

Bitrimino hard_drop(unsigned int board[8], Bitrimino& currBitrimino) {

  while(!check_bottom_edge(currBitrimino) && !check_debris_below(board, currBitrimino)) { // Move Bitrimino down until it runs into something

    move_bitr_down(board, currBitrimino);
  }

  play_block_drop();                  // Play Sound Effect
  add_to_board(board, currBitrimino); // Place current bitrimino back on board

  return create_bitrimino(board);     // Skip over the slide delay by directly creating a new bitrimino
}
