// CS 241 Final Project: Bitris
// Jenae Matson and Elliott Lewandowski
// bitris_sounds.ino
// Code for running Bitris sound effects on an Arduino Nano


// Pin declarations
const int soundPin =13;
const int rowSoundPin = 2;
const int dropSoundPin = 3;
const int endSoundPin = 4;
const int songSoundPin = 5;

const int numNotes = 41;

// Arrays of notes and durations taken from blog "Musings of a Fondue"
// https://www.jk-quantized.com/blog/2013/11/22/tetris-theme-song-using-processing
int noteDuration[numNotes] = {
    406, 203, 203, 406, 203, 203, 406, 203, 203, 406, 
    203, 203, 609, 203, 406, 406, 406, 406, 203, 203, 
    203, 203, 609, 203, 406, 203, 203, 609, 203, 406, 
    203, 203, 406, 203, 203, 406, 406, 406, 406, 406, 406
};
int rawSequence[numNotes] = {
    659, 494, 523, 587, 523, 494, 440, 440, 523, 
    659, 587, 523, 494, 523, 587, 659, 523, 
    440, 440, 440, 494, 523, 587, 698, 880, 784, 
    698, 659, 523, 659, 587, 523, 494, 494, 
    523, 587, 659, 523, 440, 440, 0
};

int digitalWriteUS=4;

// Play this note, in Hz, for this many milliseconds
void play_note(int frequencyHz,int durationMs)
{
  int cycleTimeUS=long(1000000)/frequencyHz;
  int delayTimeUS=cycleTimeUS/2-digitalWriteUS;
  digitalWrite(soundPin,LOW);
  bool bounce=true;
  int cycles=2*(durationMs*long(1000))/cycleTimeUS;
  for (int i=0;i<cycles;i++) {
    digitalWrite(soundPin,bounce); bounce=!bounce;
    delayMicroseconds(delayTimeUS);
  }
  digitalWrite(soundPin,LOW);
}

// Play the Tetris theme song
void play_korobeiniki() {
  for(int i = 0; i < numNotes ; i++) {
    play_note(rawSequence[i], noteDuration[i]);
  }
  delay(20);
}

// Play the row clear sound effect
void play_row_clear() {
  play_note(493, 100);
  delay(1);
  play_note(493, 100);
  delay(5);
  play_note(1396, 100);
}

// Play the hard drop sound effect
void play_block_drop() {
  play_note(500, 30);
  play_note(2000, 30);
  play_note(500, 50);
}

// Play the game over sound effect
void play_game_over() {
  play_note(800, 200);
  play_note(200, 200);
  play_note(70, 400);
  delay(1000);
}

void setup() {
  Serial.begin(57600);
  Serial.println("***********\n    Startup   \n***********");
  pinMode(soundPin, OUTPUT);
  pinMode(rowSoundPin, INPUT_PULLUP);
  pinMode(dropSoundPin, INPUT_PULLUP);
  pinMode(endSoundPin, INPUT_PULLUP);
  pinMode(songSoundPin, INPUT_PULLUP);
  // The main Bitris code sends a LOW signal when a sound effect is to be played
  attachInterrupt(digitalPinToInterrupt(rowSoundPin), play_row_clear, FALLING);
  attachInterrupt(digitalPinToInterrupt(dropSoundPin), play_block_drop, FALLING);
}

void loop() {
  // The main Bitris code sends a LOW signal when a sound effect is to be played
 if(digitalRead(endSoundPin) == LOW) {
  play_game_over();
 }
 if(digitalRead(songSoundPin) == LOW) {
  play_korobeiniki();
 }
}
