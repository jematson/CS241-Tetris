#pragma once

#include "config.h"

void playRowClear()
{
    digitalWrite(row_sound_pin, LOW);
    delay(1);
    digitalWrite(row_sound_pin, HIGH);
}

void playBlockDrop() {
    digitalWrite(drop_sound_pin, LOW);
    delay(1);
    digitalWrite(drop_sound_pin, HIGH);
}
