#pragma once

// Bitrimino struct
// Stores bit patterns in array
struct Bitrimino {
  unsigned int pattern[2];
};

// Define Bitrimino Types
// Horizontal Bitrimino
Bitrimino bitrimino_h = { .pattern = {0b0000000100011000} };
// Vertical Bitrimino
Bitrimino bitrimino_v = { .pattern = {0b0000001000001000, 0b0000000100001000} };
//
// Forward Diagonal Bitrimino
Bitrimino bitrimino_f = { .pattern = {0b0000001000001000, 0b0000000100010000} };
// Back Diagonal Bitrimino
Bitrimino bitrimino_b = { .pattern = {0b0000001000010000, 0b0000000100001000} };

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

// Shift the col bits of a bit pattern to move right on the screen
unsigned int shift_cols_right(unsigned int pattern) {
  // save the old rows
  unsigned int newPattern = get_row_bits(pattern);
  // copy the cols
  unsigned int newCols = get_col_bits(pattern);
  // left shift the cols by 1
  newCols = newCols << 1;
  //       | rows  | cols  |
  // ex. 0b7654321076543210
  //     0b0000000100001000
  // to  0b0000000100010000

  // recombine the old rows with the new cols
  newPattern = newPattern | newCols;
  // add new pattern to the bitrimino object
  return newPattern;
}
// Shift the col bits of a bit pattern to move left on the screen
unsigned int shift_cols_left(unsigned int pattern) {
  // save the old rows
  unsigned int newPattern = get_row_bits(pattern);
  // copy the cols
  unsigned int newCols = get_col_bits(pattern);
  // right shift the cols by 1
  newCols = newCols >> 1;
  //       | rows  | cols  |
  // ex. 0b7654321076543210
  //     0b0000000100001000
  // to  0b0000000100000100

  // recombine the old rows with the new cols
  newPattern = newPattern | newCols;
  return newPattern;
}

unsigned int shift_rows_down(unsigned int pattern) {
  // save the old cols
  unsigned int newPattern = get_col_bits(pattern);
  // copy the rows
  unsigned int newRows = get_row_bits(pattern);
  // left shift the rows by 1 to move down
  newRows = newRows << 1;
  //       | rows  | cols  |
  // ex. 0b7654321076543210
  //     0b0000100000001000
  // to  0b0001000000001000

  // recombine the new rows with the old cols
  newPattern = newRows | newPattern;
  // add new pattern to the bitrimino object
  return newPattern;
}

// Return the number of bit patterns a Bitrimino object has (1 or 2)
int num_patterns(Bitrimino bitrimino) {
  return sizeof(bitrimino.pattern) / sizeof(bitrimino.pattern[0]);
}

// Add the given Bitrimino obkect to the board
void add_to_board(unsigned int board[8], Bitrimino& bitrimino) {
  // iterate over the rows of the board
  for(int j = 0; j < 8; j++) {
    // iterate over the patterns of the bitrimino
    for (int i=0; i < num_patterns(bitrimino); i++) {
      unsigned int bitr_rows = get_row_bits(bitrimino.pattern[i]);
        // If the bitrimino has a block in this row of the board, add it to the row.
        if((bitr_rows & board[j]) != 0) {
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
        unsigned int board_rows = get_row_bits(board[i]);
        unsigned int board_cols = get_col_bits(board[i]);
        unsigned int bitr_cols = get_col_bits(bitrimino.pattern[j]);
        board[i] = board_rows | ((~bitr_cols) & board_cols);
      }
    }
  }
}

// Edge checking for current bitrimino
// false = no problem
// true = hitting edge
bool check_right_edge(unsigned int board[8], Bitrimino& curr_bitrimino) {
  // remove the bitrimino from the board
  remove_from_board(board, curr_bitrimino);
  for (int i=0; i < num_patterns(curr_bitrimino); i++) {
    unsigned int bitr_low_bits = get_col_bits(curr_bitrimino.pattern[i]);
    unsigned int bitr_high_bits = get_row_bits(curr_bitrimino.pattern[i]);
    // Check if current bitrimino is at the right edge of the board
    if((bitr_low_bits & 0x0080) != 0) 
    {
      return true;
    } 
    // Check if the bitrimino is running into debris on the right
    for (int j = 0; j<7; j++) {
      if((bitr_high_bits & get_row_bits(board[j])) != 0 && ((bitr_low_bits << 1) & get_col_bits(board[j])) != 0) {
        return true;
      }
    }
  }
  return false;
}

bool check_left_edge(unsigned int board[8], Bitrimino& curr_bitrimino) {
  // Remove the bitrimino from the board
  remove_from_board(board, curr_bitrimino);
  // Loop through patterns of bitrmino
  for (int i=0; i < num_patterns(curr_bitrimino); i++) {
    unsigned int bitr_low_bits = get_col_bits(curr_bitrimino.pattern[i]);
    unsigned int bitr_high_bits = get_row_bits(curr_bitrimino.pattern[i]);
    //Checks if the current bitrimino is on the left edge of the board
    if((bitr_low_bits & 0x0001) != 0) 
    {
      return true;
    }
    // Check if the bitrimino is running into debris on the left
    for (int j = 0; j<7; j++) {
      if((bitr_high_bits & get_row_bits(board[j])) != 0 && ((bitr_low_bits >> 1) & get_col_bits(board[j])) != 0) {
        return true;
      }
    }
  }
  return false;
}
bool check_bottom_edge(Bitrimino& curr_bitrimino) {
  for (int i=0; i < num_patterns(curr_bitrimino); i++) {
    unsigned int bitr_high_bits = get_row_bits(curr_bitrimino.pattern[i]);
    if((bitr_high_bits & 0x8000) != 0) // Checks if current bitrimino has an entry on the bottom row of the table
    {
      return true;
    }
  }
  return false;
}

// Shift the bit pattern(s) of the given bitrimino so the piece moves one block right
Bitrimino move_bitr_right(unsigned int board[8], Bitrimino& curr_bitrimino) {
  if(!check_right_edge(board, curr_bitrimino)) // If not on the edge of the board move 
  {
    
    for (int i=0; i < num_patterns(curr_bitrimino); i++) {
      // reform the column bits
      curr_bitrimino.pattern[i] = shift_cols_right(curr_bitrimino.pattern[i]);
    }
  }
  return curr_bitrimino;
}

// Shift the bit pattern(s) of the given bitrimino so the piece moves one block left
Bitrimino move_bitr_left(unsigned int board[8], Bitrimino& curr_bitrimino) {
  if(!check_left_edge(board, curr_bitrimino)) // If not on the edge of the board move
  {
    
    for (int i=0; i < num_patterns(curr_bitrimino); i++) {
      // reform the column bits
      curr_bitrimino.pattern[i] = shift_cols_left(curr_bitrimino.pattern[i]);
    }
  }
  return curr_bitrimino;
}

// Shift the bit pattern(s) of the given bitrimino so the piece moves one block down
Bitrimino move_bitr_down(unsigned int board[8], Bitrimino& curr_bitrimino) {
  // remove the bitrimino from the board
  remove_from_board(board, curr_bitrimino);
  for (int i=0; i < num_patterns(curr_bitrimino); i++) {
    // reform row bits
    curr_bitrimino.pattern[i] = shift_rows_down(curr_bitrimino.pattern[i]);
  }
  return curr_bitrimino;
}
