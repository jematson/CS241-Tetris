#pragma once

#include "config.h"

void playRowClear()
{
    digitalWrite(row_sound_pin, HIGH);
    delay(1);
    digitalWrite(row_sound_pin, LOW);
}

void playBlockDrop() {
    digitalWrite(drop_sound_pin, HIGH);
    delay(1);
    digitalWrite(drop_sound_pin, LOW);
}
