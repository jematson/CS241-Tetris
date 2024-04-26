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

void playRowClear()
{
    digitalWrite(rowSoundPin, LOW);
    digitalWrite(rowSoundPin, HIGH);
}

void playBlockDrop() {
    digitalWrite(dropSoundPin, LOW);
    digitalWrite(dropSoundPin, HIGH);
}

void playGameOver() {
  digitalWrite(endSoundPin, LOW);
  delay(10);
  digitalWrite(endSoundPin, HIGH);
}

void playBackgroundMusic() {
  digitalWrite(songSoundPin, LOW);
  digitalWrite(songSoundPin, HIGH);
}
