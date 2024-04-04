#pragma once
#include"config.h"
// Header file for displaying pattern on 8x8 LED display
// with two 595 shift registers

// Set up the shift register pins (call from setup)
void begin_shift_reg(const int dataPin, const int shiftPin, const int outputPin)
{
  pinMode(dataPin,OUTPUT);
  pinMode(shiftPin,OUTPUT);
  pinMode(outputPin,OUTPUT);  
}

// This gives names to each bit from the 16-bit pattern
typedef enum {
 c0 = 0, c1, c2, c3, c4, c5, c6, c7, // columns are low 8 bits
 r0 = 8, r1, r2, r3, r4, r5, r6, r7  // rows are high 8 bits
} rc_t;

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

// Send another bit to the shift register
void send_bit_to_shift_reg(int bit)
{
  digitalWrite(dataPin,bit);
  digitalWrite(shiftPin,0);
  digitalWrite(shiftPin,1);
}

// 595 expects 8 bits: the 8 bottom pins of the 8x8 LED matrix
void send_to_shift_reg(unsigned int raw_pattern)
{
  send_bit_to_shift_reg(pattern_has_bit(raw_pattern, r0));
  send_bit_to_shift_reg(pattern_has_bit(raw_pattern, c3));
  send_bit_to_shift_reg(pattern_has_bit(raw_pattern, c5));
  send_bit_to_shift_reg(pattern_has_bit(raw_pattern, r3));
  send_bit_to_shift_reg(pattern_has_bit(raw_pattern, c0));
  send_bit_to_shift_reg(pattern_has_bit(raw_pattern, r1));
  send_bit_to_shift_reg(pattern_has_bit(raw_pattern, c6));
  send_bit_to_shift_reg(pattern_has_bit(raw_pattern, c7));

  send_bit_to_shift_reg(pattern_has_bit(raw_pattern, r4));
  send_bit_to_shift_reg(pattern_has_bit(raw_pattern, r6));
  send_bit_to_shift_reg(pattern_has_bit(raw_pattern, c1));
  send_bit_to_shift_reg(pattern_has_bit(raw_pattern, c2));
  send_bit_to_shift_reg(pattern_has_bit(raw_pattern, r7));
  send_bit_to_shift_reg(pattern_has_bit(raw_pattern, c4));
  send_bit_to_shift_reg(pattern_has_bit(raw_pattern, r5));
  send_bit_to_shift_reg(pattern_has_bit(raw_pattern, r2));
 
  digitalWrite(outputPin,0);
  digitalWrite(outputPin,1);
}

/* Show this pattern on the 8x8 LED matrix.  
  "Nice" pattern bits should be 1
  for that row or column to be active,
  and 0 for inactive.
*/
void send_pattern(unsigned int nice_pattern, int delay)
{
  unsigned int raw_pattern = 0b1111111100000000 ^ nice_pattern; // rows are 0 to be lit
  send_to_shift_reg(raw_pattern); // bottom pins
  delayMicroseconds(delay);
  unsigned int zero_pattern = 0b1111111100000000;
  send_to_shift_reg(zero_pattern);
}