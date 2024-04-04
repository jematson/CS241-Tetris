#pragma once

// Bitrimino struct
// Stores bit patterns in array
struct Bitrimino {
  unsigned int pattern[2];
};

// Return high bits (rows) from a bit pattern
unsigned int get_high_bits(unsigned int pattern) {
  return pattern & 0xFF00;
}
// Return low bits (cols) from a bit pattern
unsigned int get_low_bits(unsigned int pattern) {
  return pattern & 0x00FF;
}

// Add the given bitrimino to the board
void add_to_board(unsigned int board[8], unsigned int bitrimino) {
  unsigned int bitr_high_bits = get_high_bits(bitrimino);
  // loop through rows of board
  for(int i = 0; i < 8; i++) {
    if((bitr_high_bits & board[i]) != 0) {
      board[i] = board[i] | bitrimino;
    }
  }
}

// Remove the given bitrimino from the board
void remove_from_board(unsigned int board[8], unsigned int bitrimino) {
  unsigned int bitr_high_bits = get_high_bits(bitrimino);
  // loop through rows of board
  for(int i = 0; i < 8; i++) {
    // Checking if the bitrimino has something in the ith row of the board
    if((bitr_high_bits & board[i]) != 0) {
      unsigned int board_high_bits = get_high_bits(board[i]);
      unsigned int board_low_bits = get_low_bits(board[i]);
      unsigned int bitr_low_bits = get_low_bits(bitrimino);
      board[i] = board_high_bits | ((~bitr_low_bits) & board_low_bits);
    }
  }
}

// Edge checking for current bitrimino
// false = no problem
// true = hitting edge
bool check_right_edge(Bitrimino& curr_bitrimino) {
  int num_patterns = sizeof(curr_bitrimino.pattern) / sizeof(curr_bitrimino.pattern[0]);
  for (int i=0; i<num_patterns; i++) {
    unsigned int bitr_low_bits = get_low_bits(curr_bitrimino.pattern[i]);
    if((bitr_low_bits & 0x0080) != 0) //Checks if the current bitrimino has an entry on the right edge of the board
    {
      return true;
    }
  }
  return false;
}

bool check_left_edge(Bitrimino& curr_bitrimino) {
  int num_patterns = sizeof(curr_bitrimino.pattern) / sizeof(curr_bitrimino.pattern[0]);
  for (int i=0; i<num_patterns; i++) {
    unsigned int bitr_low_bits = get_low_bits(curr_bitrimino.pattern[i]);
    if((bitr_low_bits & 0x0001) != 0) //Checks if the current bitrimino has an entry on the left edge of the board
    {
      return true;
    }
  }
  return false;
}
bool check_bottom_edge(Bitrimino& curr_bitrimino) {
  int num_patterns = sizeof(curr_bitrimino.pattern) / sizeof(curr_bitrimino.pattern[0]);
  for (int i=0; i<num_patterns; i++) {
    unsigned int bitr_high_bits = get_high_bits(curr_bitrimino.pattern[i]);
    if((bitr_high_bits & 0x8000) != 0) // Checks if current bitrimino has an entry on the bottom row of the table
    {
      return true;
    }
    
  }
  return false;
}

// Shift the bit pattern(s) of the given bitrimino so the piece moves one block right
Bitrimino move_bitr_right(unsigned int board[8], Bitrimino& curr_bitrimino) {
  if(!check_right_edge(curr_bitrimino)) // If not on the edge of the board move 
  {
    int num_patterns = sizeof(curr_bitrimino.pattern) / sizeof(curr_bitrimino.pattern[0]);
    for (int i=0; i<num_patterns; i++) {
      // remove the bitrimino from the board
      remove_from_board(board, curr_bitrimino.pattern[i]);
      // save the high bits, the rows
      unsigned int newPattern = get_high_bits(curr_bitrimino.pattern[i]);
      // copy the low bits, the cols
      unsigned int oldCols = get_low_bits(curr_bitrimino.pattern[i]);
      // left shift the cols by 1
      oldCols = oldCols << 1;
      //       | rows  | cols  |
      // ex. 0b7654321076543210
      //     0b0000000100001000
      // to  0b0000000100010000

      // recombine the old rows with the old cols
      newPattern = newPattern | oldCols;
      // add new pattern to the bitrimino object
      curr_bitrimino.pattern[i] = newPattern;
      // add bitrimino to board in new position
      add_to_board(board, newPattern);
    }
  }
  return curr_bitrimino;
}

// Shift the bit pattern(s) of the given bitrimino so the piece moves one block left
Bitrimino move_bitr_left(unsigned int board[8], Bitrimino& curr_bitrimino) {
  if(!check_left_edge(curr_bitrimino)) // If not on the edge of the board move
  {
    int num_patterns = sizeof(curr_bitrimino.pattern) / sizeof(curr_bitrimino.pattern[0]);
    for (int i=0; i<num_patterns; i++) {
      // remove the bitrimino from the board
      remove_from_board(board, curr_bitrimino.pattern[i]);
      // save the high bits, the rows
      unsigned int newPattern = get_high_bits(curr_bitrimino.pattern[i]);
      // copy the low bits, the cols
      unsigned int oldCols = get_low_bits(curr_bitrimino.pattern[i]);
      // right shift the cols by 1
      oldCols = oldCols >> 1;
      //       | rows  | cols  |
      // ex. 0b7654321076543210
      //     0b0000000100001000
      // to  0b0000000100000100

      // recombine the old rows with the new cols
      newPattern = newPattern | oldCols;
      // add new pattern to the bitrimino object
      curr_bitrimino.pattern[i] = newPattern;
      // add bitrimino to board in new position
      add_to_board(board, newPattern);
    }
  }
  return curr_bitrimino;
}

// Shift the bit pattern(s) of the given bitrimino so the piece moves one block down
Bitrimino move_bitr_down(unsigned int board[8], Bitrimino& curr_bitrimino) {
  if(!check_bottom_edge(curr_bitrimino)) // If not on the edge of the board move
  {
    int num_patterns = sizeof(curr_bitrimino.pattern) / sizeof(curr_bitrimino.pattern[0]);
    for (int i=0; i<num_patterns; i++) {
      // remove the bitrimino from the board
      remove_from_board(board, curr_bitrimino.pattern[i]);
      // save the low bits, the cols
      unsigned int newPattern = get_low_bits(curr_bitrimino.pattern[i]);
      // copy the high bits, the rows
      unsigned int oldRows = get_high_bits(curr_bitrimino.pattern[i]);
      // left shift the rows by 1 to move down
      oldRows = oldRows << 1;
      //       | rows  | cols  |
      // ex. 0b7654321076543210
      //     0b0000100000001000
      // to  0b0001000000001000

      // recombine the new rows with the old cols
      newPattern = oldRows | newPattern;
      // add new pattern to the bitrimino object
      curr_bitrimino.pattern[i] = newPattern;
      // add bitrimino to board in new position
      add_to_board(board, newPattern);
    }
  }
  return curr_bitrimino;
}


