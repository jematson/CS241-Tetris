// display_pattern.h
// Header file for displaying pattern on 8x8 LED display
// with two 595 shift registers

#pragma once
#include"data.h"

// This gives names to each bit from the 16-bit pattern for the game board
// 0b7654321076543210
typedef enum {
 c0 = 0, c1, c2, c3, c4, c5, c6, c7, // columns are low 8 bits
 r0 = 8, r1, r2, r3, r4, r5, r6, r7  // rows are high 8 bits
} rc_t;

// This gives names to each bit from the 16-bit pattern for the pointboard
// 0b00004321ABCDEFGd
typedef enum {
  dot = 0, G, F, E, D, C, B, A, // segments of a digit
  d1 = 8, d2, d3, d4            // digits on board
} ds_t;

// Set up the shift register pins (call from setup)
void begin_shift_reg(const int dataPin, const int shiftPin, const int outputPin)
{
  pinMode(dataPin,OUTPUT);
  pinMode(shiftPin,OUTPUT);
  pinMode(outputPin,OUTPUT);  
}

/*
 Pattern is a 16 bit int = 8 rows, 8 columns
 The bits tell you what the rows and columns should be doing:
  high bits  low bits
   8 rows   8 cols
   7654321076543210
*/
bool pattern_has_bit(unsigned int raw_pattern, rc_t bit)
{
  return raw_pattern & (1<<bit); // pull out this bit of the pattern
}
bool pattern_has_bit(unsigned int raw_pattern, ds_t bit)
{
  return raw_pattern & (1<<bit); // pull out this bit of the pattern
}

// Send another bit to the shift register
void send_bit_to_shift_reg(int bit)
{
  digitalWrite(dataPin,bit);
  digitalWrite(shiftPin,0);
  digitalWrite(shiftPin,1);
}

// 595s expect 32 bits: 16 pins for 7-segment led display, 16 pins for 8x8 led display
void send_to_shift_reg(unsigned int board_pattern, unsigned int point_pattern)
{
  // Point Board Pins
  send_bit_to_shift_reg(pattern_has_bit(point_pattern, B));
  send_bit_to_shift_reg(pattern_has_bit(point_pattern, d3));
  send_bit_to_shift_reg(pattern_has_bit(point_pattern, d2));
  send_bit_to_shift_reg(pattern_has_bit(point_pattern, F));
  send_bit_to_shift_reg(pattern_has_bit(point_pattern, A));
  send_bit_to_shift_reg(pattern_has_bit(point_pattern, d1));
  send_bit_to_shift_reg(0); // unused
  send_bit_to_shift_reg(0); // unused
  send_bit_to_shift_reg(pattern_has_bit(point_pattern, E));
  send_bit_to_shift_reg(pattern_has_bit(point_pattern, D));
  send_bit_to_shift_reg(pattern_has_bit(point_pattern, dot));
  send_bit_to_shift_reg(pattern_has_bit(point_pattern, C));
  send_bit_to_shift_reg(pattern_has_bit(point_pattern, G));
  send_bit_to_shift_reg(pattern_has_bit(point_pattern, d4));
  send_bit_to_shift_reg(0); // unused
  send_bit_to_shift_reg(0); // unused

  // 8x8 Game Board Pins
  send_bit_to_shift_reg(pattern_has_bit(board_pattern, r0));
  send_bit_to_shift_reg(pattern_has_bit(board_pattern, c3));
  send_bit_to_shift_reg(pattern_has_bit(board_pattern, c5));
  send_bit_to_shift_reg(pattern_has_bit(board_pattern, r3));
  send_bit_to_shift_reg(pattern_has_bit(board_pattern, c0));
  send_bit_to_shift_reg(pattern_has_bit(board_pattern, r1));
  send_bit_to_shift_reg(pattern_has_bit(board_pattern, c6));
  send_bit_to_shift_reg(pattern_has_bit(board_pattern, c7));

  send_bit_to_shift_reg(pattern_has_bit(board_pattern, r4));
  send_bit_to_shift_reg(pattern_has_bit(board_pattern, r6));
  send_bit_to_shift_reg(pattern_has_bit(board_pattern, c1));
  send_bit_to_shift_reg(pattern_has_bit(board_pattern, c2));
  send_bit_to_shift_reg(pattern_has_bit(board_pattern, r7));
  send_bit_to_shift_reg(pattern_has_bit(board_pattern, c4));
  send_bit_to_shift_reg(pattern_has_bit(board_pattern, r5));
  send_bit_to_shift_reg(pattern_has_bit(board_pattern, r2));
 
  digitalWrite(outputPin,0);
  digitalWrite(outputPin,1);
}

/* Show this pattern on the 8x8 LED matrix.  
  "Nice" pattern bits should be 1
  for that row or column to be active,
  and 0 for inactive.
*/
void send_pattern(unsigned int board_pattern, unsigned int point_pattern, int delay)
{
  unsigned int raw_board_pattern = 0b1111111100000000 ^ board_pattern; // rows are 0 to be lit
  unsigned int raw_point_pattern = 0b0000000011111111 ^ point_pattern;
  send_to_shift_reg(raw_board_pattern, raw_point_pattern);
  delayMicroseconds(delay);
  unsigned int zero_pattern1 = 0b1111111100000000;
  unsigned int zero_pattern2 = 0b0000000000000000;
  send_to_shift_reg(zero_pattern1, zero_pattern2);
}