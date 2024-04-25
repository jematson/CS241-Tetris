#pragma once
#include"data.h"

//Sound comm pin declarations
const int rowSoundPin = 6;
const int dropSoundPin = 5;
const int endSoundPin = 4;
const int songSoundPin = 3;

// Set pinModes for sound comm pins
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

// Send signal to Nano to play row clear sound effect
void play_row_clear()
{
    digitalWrite(rowSoundPin, LOW);
    digitalWrite(rowSoundPin, HIGH);
}

// Send signal to Nano to play hard drop sound effect
void play_block_drop() {
    digitalWrite(dropSoundPin, LOW);
    digitalWrite(dropSoundPin, HIGH);
}

// Send signal to Nano to play game over sound effect
void play_game_over() {
  digitalWrite(endSoundPin, LOW);
  delay(10);
  digitalWrite(endSoundPin, HIGH);
}

// Send signal to Nano to play Tetris theme song
void play_background_music() {
  digitalWrite(songSoundPin, LOW);
  digitalWrite(songSoundPin, HIGH);
}
