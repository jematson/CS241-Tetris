#pragma once

#include "config.h"

//Sound comms pins
const int row_sound_pin = 6;
const int drop_sound_pin = 5;
const int end_sound_pin = 4;
const int song_sound_pin = 3;

void begin_sound_pins() {
  pinMode(row_sound_pin, OUTPUT);
  pinMode(drop_sound_pin, OUTPUT);
  pinMode(end_sound_pin, OUTPUT);
  pinMode(song_sound_pin, OUTPUT);
  digitalWrite(row_sound_pin, HIGH);
  digitalWrite(drop_sound_pin, HIGH);
  digitalWrite(end_sound_pin, HIGH);
  digitalWrite(song_sound_pin, HIGH);
}

void playRowClear()
{
    digitalWrite(row_sound_pin, LOW);
    //delay(1);
    digitalWrite(row_sound_pin, HIGH);
}

void playBlockDrop() {
    digitalWrite(drop_sound_pin, LOW);
    //delay(1);
    digitalWrite(drop_sound_pin, HIGH);
}

void playGameOver() {
  digitalWrite(end_sound_pin, LOW);
  digitalWrite(end_sound_pin, HIGH);
}

void playBackgroundMusic() {
  digitalWrite(song_sound_pin, LOW);
  digitalWrite(song_sound_pin, HIGH);
}
