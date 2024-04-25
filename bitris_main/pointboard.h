#pragma once

#include"data.h"

// Symbol Lookup Table
const int symbols = 10;
const unsigned int symbolTable[symbols] =
{
  0b0000000011111100,  //0
  0b0000000001100000,  //1
  0b0000000011011010,  //2
  0b0000000011110010,  //3
  0b0000000001100110,  //4
  0b0000000010110110,  //5
  0b0000000010111110,  //6
  0b0000000011100000,  //7
  0b0000000011111110,  //8
  0b0000000011100110,  //9
};

const int digits = 4;
const unsigned int digitTable[digits] =
{
  0b1111000100000000, // 1st digit
  0b1111001000000000, // 2nd digit
  0b1111010000000000, // 3rd digit
  0b1111100000000000 // 4th digit
};

// Make a symbol pattern of the form
// 0b00004321ABCDEFGd
// from a given digit and symbol
unsigned int make_symbol_pattern(int digit, int symbol) {
  unsigned int digit_pattern = digitTable[digit - 1];

  unsigned int symbol_pattern = symbolTable[symbol];

  return digit_pattern | symbol_pattern;
}

void update_points_patterns() {
  int dig1 = (points / 1000) % 10;
  int dig2 = (points / 100) % 10;
  int dig3 = (points / 10) % 10;
  int dig4 = points % 10;
  
  int pointArray[] = {dig1, dig2, dig3, dig4};

  for(int i = 1; i < 5; ++i) {
    unsigned int pattern = make_symbol_pattern(i, pointArray[i-1]);
    points_patterns[i-1] = pattern;
  }
}
