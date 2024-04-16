#pragma once

#include "config.h"

//Sound comms pins
const int row_sound_pin = 6;
const int drop_sound_pin = 5;

void begin_sound_pins() {
  pinMode(row_sound_pin, OUTPUT);
  pinMode(drop_sound_pin, OUTPUT);
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
