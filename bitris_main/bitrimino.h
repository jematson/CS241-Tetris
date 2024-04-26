// bitrimino.h
// Header to define bitriminos and associated functions

#pragma once
#include"data.h"
#include"sound_comm.h"

// Bitrimino struct
// Stores bit patterns in array
struct Bitrimino {
  unsigned int pattern[2];
};

// Define Bitrimino Type patterns
// Horizontal Bitrimino
Bitrimino bitrimino_h = { .pattern = {0b0000000100011000} };
// Vertical Bitrimino
Bitrimino bitrimino_v = { .pattern = {0b0000001000001000, 0b0000000100001000} };
// Forward Diagonal Bitrimino
Bitrimino bitrimino_f = { .pattern = {0b0000001000001000, 0b0000000100010000} };
// Back Diagonal Bitrimino
Bitrimino bitrimino_b = { .pattern = {0b0000001000010000, 0b0000000100001000} };

// Create a new random bitrimino
Bitrimino create_bitrimino() {
  switch(random(1, 5)) {
    case 1:
      return bitrimino_h;
    case 2:
      return bitrimino_v;
    case 3:
      return bitrimino_f;
    case 4:
      return bitrimino_b; 
  }
}

// Return high bits (rows) from a bit pattern
unsigned int get_row_bits(unsigned int pattern) {
  return pattern & 0xFF00;
}
// Return low bits (cols) from a bit pattern
unsigned int get_col_bits(unsigned int pattern) {
  return pattern & 0x00FF;
}

// Shift the col bits of a bit pattern to move right on the board
unsigned int shift_cols_right(unsigned int pattern) {
  // save the old rows
  unsigned int newPattern = get_row_bits(pattern);
  // copy the cols
  unsigned int newCols = get_col_bits(pattern);
  // left shift the cols by 1
  newCols = newCols << 1;

  // recombine the old rows with the new cols and return
  newPattern = newPattern | newCols;
  return newPattern;
}
// Shift the col bits of a bit pattern to move left on the board
unsigned int shift_cols_left(unsigned int pattern) {
  // save the old rows
  unsigned int newPattern = get_row_bits(pattern);
  // copy the cols
  unsigned int newCols = get_col_bits(pattern);
  // right shift the cols by 1
  newCols = newCols >> 1;

  // recombine the old rows with the new cols and return
  newPattern = newPattern | newCols;
  return newPattern;
}
// Shift the row bits of a bit pattern to move down on the board
unsigned int shift_rows_down(unsigned int pattern) {
  // save the old cols
  unsigned int newPattern = get_col_bits(pattern);
  // copy the rows
  unsigned int newRows = get_row_bits(pattern);
  // left shift the rows by 1
  newRows = newRows << 1;

  // recombine the new rows with the old cols and return
  newPattern = newRows | newPattern;
  return newPattern;
}

// Return the number of bit patterns a Bitrimino object has (1 or 2)
int num_patterns(Bitrimino bitrimino) {
  return sizeof(bitrimino.pattern) / sizeof(bitrimino.pattern[0]);
}

// Add the given Bitrimino object to the board
void add_to_board(unsigned int board[8], Bitrimino& bitrimino) {
  // iterate over the rows of the board
  for(int j = 0; j < 8; j++) {
    // iterate over the patterns of the bitrimino
    for (int i=0; i < num_patterns(bitrimino); i++) {
      unsigned int bitrRows = get_row_bits(bitrimino.pattern[i]);
        // If the bitrimino has a block in this row of the board, add it to the row.
        if((bitrRows & board[j]) != 0) {
          board[j] = board[j] | bitrimino.pattern[i];
        }
    }
  }
}

// Remove the given Bitrimino object from the board
void remove_from_board(unsigned int board[8], Bitrimino& bitrimino) {
  // loop through rows of board
  for(int i = 0; i < 8; i++) {
    for (int j=0; j < num_patterns(bitrimino); j++) {
      // Checking if the bitrimino has something in the ith row of the board
      if((get_row_bits(bitrimino.pattern[j]) & board[i]) != 0) {
        unsigned int boardRows = get_row_bits(board[i]);
        unsigned int boardCols = get_col_bits(board[i]);
        unsigned int bitrCols = get_col_bits(bitrimino.pattern[j]);
        board[i] = boardRows | ((~bitrCols) & boardCols);
      }
    }
  }
}

// Edge checking for current bitrimino
// Returns true if the bitrimino is hitting and edge or debris
bool check_right_edge(unsigned int board[8], Bitrimino& currBitrimino) {
  // remove the bitrimino from the board so it doesn't count itself as debris
  remove_from_board(board, currBitrimino);
  // Loop through patterns of Bitrimino
  for (int i=0; i < num_patterns(currBitrimino); i++) {
    unsigned int bitrCols = get_col_bits(currBitrimino.pattern[i]);
    unsigned int bitrRows = get_row_bits(currBitrimino.pattern[i]);
    // Check if current bitrimino is at the right edge of the board
    if((bitrCols & 0x0080) != 0) 
    {
      return true;
    } 
    // Check if the bitrimino is running into debris on the right
    for (int j = 0; j<8; j++) {
      if((bitrRows & get_row_bits(board[j])) != 0 && ((bitrCols << 1) & get_col_bits(board[j])) != 0) {
        return true;
      }
    }
  }
  return false;
}
bool check_left_edge(unsigned int board[8], Bitrimino& currBitrimino) {
  // Remove the bitrimino from the board so it doesn't count itself as debris
  remove_from_board(board, currBitrimino);
  // Loop through patterns of bitrimino
  for (int i=0; i < num_patterns(currBitrimino); i++) {
    unsigned int bitrCols = get_col_bits(currBitrimino.pattern[i]);
    unsigned int bitrRows = get_row_bits(currBitrimino.pattern[i]);
    //Checks if the current bitrimino is on the left edge of the board
    if((bitrCols & 0x0001) != 0) 
    {
      return true;
    }
    // Check if the bitrimino is running into debris on the left
    for (int j = 0; j<8; j++) {
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
    // Check if the bitrimino is at the bottom of the board
    if((bitrRows & 0x8000) != 0)
    {
      return true;
    }
  }
  return false;
}

// Checks if the current bitrimino will run into existing debris on the board
bool check_debris_below(unsigned int board[8], Bitrimino& currBitrimino) {
  // remove the bitrimino from the board so it doesn't count itself as debris
  remove_from_board(board, currBitrimino);
  for (int i=0; i < num_patterns(currBitrimino); i++) {
    unsigned int lowBlock = currBitrimino.pattern[i];

    unsigned int bitrRows = get_row_bits(lowBlock);
    unsigned int bitrCols = get_col_bits(lowBlock);
    bitrRows = bitrRows << 1;
    // loop through rows of board
    for(int j = 0; j < 8; j++) {
      if((bitrRows & board[j]) != 0) {
        if((bitrCols & get_col_bits(board[j])) != 0) {
          add_to_board(board, currBitrimino);
          return true;
        }
      }
    }
  }
  add_to_board(board, currBitrimino);
  return false;
}

// Checks if the bitr is in upper row
bool check_upper_rows(unsigned int board[8], Bitrimino& currBitrimino)
{
  for (int i=0; i < num_patterns(currBitrimino); i++) {
  unsigned int bitrRows = get_row_bits(currBitrimino.pattern[i]);
    if((bitrRows & 0x0300) != 0) // Checks if bitrimino has an entry in the top two rows of the board
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
    if((bitrCols & 0x0018) != 0) // Checks if bitrimino has an entry in the top two rows of the board
    {
      return true;
    }
  }
  return false;
}

// Shift the bit pattern(s) of the given bitrimino so the piece moves one block right
Bitrimino move_bitr_right(unsigned int board[8], Bitrimino& currBitrimino) {
  if(!check_right_edge(board, currBitrimino)) // If not on the edge of the board move 
  {
    for (int i=0; i < num_patterns(currBitrimino); i++) {
      // reform the column bits
      currBitrimino.pattern[i] = shift_cols_right(currBitrimino.pattern[i]);
    }
  }
  return currBitrimino;
}

// Shift the bit pattern(s) of the given bitrimino so the piece moves one block left
Bitrimino move_bitr_left(unsigned int board[8], Bitrimino& currBitrimino) {
  if(!check_left_edge(board, currBitrimino)) // If not on the edge of the board move
  {
    for (int i=0; i < num_patterns(currBitrimino); i++) {
      // reform the column bits
      currBitrimino.pattern[i] = shift_cols_left(currBitrimino.pattern[i]);
    }
  }
  return currBitrimino;
}

// Shift the bit pattern(s) of the given bitrimino so the piece moves one block down
Bitrimino move_bitr_down(unsigned int board[8], Bitrimino& currBitrimino) {
  // remove the bitrimino from the board
  remove_from_board(board, currBitrimino);
  for (int i=0; i < num_patterns(currBitrimino); i++) {
    // reform the row bits
    currBitrimino.pattern[i] = shift_rows_down(currBitrimino.pattern[i]);
  }
  return currBitrimino;
}

// Hard drop: immediately move the bitrimino as far down as it can go
Bitrimino hard_drop(unsigned int board[8], Bitrimino& currBitrimino) {
  while(!check_bottom_edge(currBitrimino) && !check_debris_below(board, currBitrimino)) {
    move_bitr_down(board, currBitrimino);
  }
  play_block_drop();
  add_to_board(board, currBitrimino);

  return create_bitrimino();
}
