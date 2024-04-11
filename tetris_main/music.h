#pragma once
// Bitris background music, "Korobeiniki"
#include"config.h"

//music pin
const int soundPin = 6;

const int num_notes = 41;

// Arrays of notes and durations taken from blog "Musings of a Fondue"
// https://www.jk-quantized.com/blog/2013/11/22/tetris-theme-song-using-processing
int noteDuration[num_notes] = {
    406, 203, 203, 406, 203, 203, 406, 203, 203, 406, 
    203, 203, 609, 203, 406, 406, 406, 406, 203, 203, 
    203, 203, 609, 203, 406, 203, 203, 609, 203, 406, 
    203, 203, 406, 203, 203, 406, 406, 406, 406, 406, 406
};
int rawSequence[num_notes] = {
    659, 494, 523, 587, 523, 494, 440, 440, 523, 
    659, 587, 523, 494, 523, 587, 659, 523, 
    440, 440, 440, 494, 523, 587, 698, 880, 784, 
    698, 659, 523, 659, 587, 523, 494, 494, 
    523, 587, 659, 523, 440, 440, 0
};

// playNote function from Dr. Lawlor
// Time in microseconds for a digitalWrite,
//  delayMicroseconds, and loop.
int digitalWriteUS=4;

// Play this note, in Hz, for this many milliseconds
void playNote(int frequencyHz,int durationMs)
{
  int cycleTimeUS=long(1000000)/frequencyHz;
  int delayTimeUS=cycleTimeUS/2-digitalWriteUS;
  digitalWrite(soundPin, 0);
  bool bounce=true;
  int cycles=2*(durationMs*long(1000))/cycleTimeUS;
  for (int i=0;i<cycles;i++) {
    digitalWrite(soundPin,bounce); bounce=!bounce;
    delayMicroseconds(delayTimeUS);
  }
  digitalWrite(soundPin, 0);
}

void playRowClear() {
  playNote(493, 100);
  delay(1);
  playNote(493, 100);
  delay(5);
  playNote(1396, 100);
}

void playBlockDrop() {
  playNote(500, 30);
  playNote(2000, 30);
  playNote(500, 50);
}

void playKorobeiniki() {
  for(int i = 0; i < num_notes ; i++) {
    playNote(rawSequence[i], noteDuration[i]);
  }
  delay(20);
}