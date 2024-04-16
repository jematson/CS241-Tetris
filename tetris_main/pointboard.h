#pragma once

// Pins for digits 1-4
const int digitArray[] = {10, 11, 12, 13};
const int digitLength = 4;
/*
1 = 10
2 = 11
3 = 12
4 = 13
*/

// LED Segment Pins
const int pinArray[] = {8,7,5,3,4,9,6,2};
const int pinLength = 8;
/*
2 = Dot
3 = D
4 = E
5 = C
6 = G
7 = B
8 = A
9 = F
*/

// Symbol Lookup Table
const int symbols = 10;
const int symbol[symbols][8] =
{
  {1,1,1,1,1,1,0,0},  //0
  {0,1,1,0,0,0,0,0},  //1
  {1,1,0,1,1,0,1,0},  //2
  {1,1,1,1,0,0,1,0},  //3
  {0,1,1,0,0,1,1,0},  //4
  {1,0,1,1,0,1,1,0},  //5
  {1,0,1,1,1,1,1,0},  //6
  {1,1,1,0,0,0,0,0},  //7
  {1,1,1,1,1,1,1,0},  //8
  {1,1,1,0,0,1,1,0},  //9
};

const int delayMS = 1;
void showSymbol(int S)
{
  for(int i = 0; i < pinLength; i++)
  {
    digitalWrite(pinArray[i], symbol[S][i]);
  }
}

void showDigit(int digit, int symbol)
{
  showSymbol(symbol);
  digitalWrite(digitArray[digit], LOW);
  delay(delayMS);
  digitalWrite(digitArray[digit], HIGH);
}

