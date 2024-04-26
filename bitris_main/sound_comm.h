#pragma once

#include "data.h"

//Sound comms pins
const int rowSoundPin = 6;
const int dropSoundPin = 5;
const int endSoundPin = 4;
const int songSoundPin = 3;

void begin_sound_pins() {
  pinMode(rowSoundPin, OUTPUT);
  pinMode(dropSoundPin, OUTPUT);
  pinMode(endSoundPin, OUTPUT);
  pinMode(songSoundPin, OUTPUT);
  digitalWrite(rowSoundPin, HIGH);
  digitalWrite(dropSoundPin, HIGH);
  digitalWrite(endSoundPin, HIGH);
  digitalWrite(songSoundPin, HIGH);
}

void play_row_clear()
{
    digitalWrite(rowSoundPin, LOW);
    digitalWrite(rowSoundPin, HIGH);
}

void play_block_drop() {
    digitalWrite(dropSoundPin, LOW);
    digitalWrite(dropSoundPin, HIGH);
}

void play_game_over() {
  digitalWrite(endSoundPin, LOW);
  delay(10);
  digitalWrite(endSoundPin, HIGH);
}

void play_background_music() {
  digitalWrite(songSoundPin, LOW);
  digitalWrite(songSoundPin, HIGH);
}
