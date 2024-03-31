// CS 241 Final Project: Tetris Game
// Jenae Matson and Elliott Lewandowski

const int left_button = 8;
const int right_button = 9;

// This gives names to each bit from the 16-bit pattern
typedef enum {
 c0 = 0, c1, c2, c3, c4, c5, c6, c7, // columns are low 8 bits
 r0 = 8, r1, r2, r3, r4, r5, r6, r7  // rows are high 8 bits
} rc_t;

/* Show this pattern on the 8x8 LED matrix.  
  "Nice" pattern bits should be 1
  for that row or column to be active,
  and 0 for inactive.
*/
void send_pattern(unsigned int nice_pattern, int delay)
{
  unsigned int raw_pattern = 0b1111111100000000 ^ nice_pattern; // rows are 0 to be lit
  send_to_arduino_pins(raw_pattern); // top pins
  send_to_shift_reg(raw_pattern); // bottom pins
  delayMicroseconds(delay);
  unsigned int zero_pattern = 0b1111111100000000;
  send_to_arduino_pins(zero_pattern);
  send_to_shift_reg(zero_pattern);
}

/*
 Pattern is a 16 bit int = 8 rows, 8 columns
 The bits tell you what the rows and columns should be doing:
  high bits  low bits
   8 rows   8 cols
   7654321076543210
*/
bool pattern_has_bit(unsigned int raw_pattern, rc_t bit)
{
  return raw_pattern & (1<<bit); // pull out this bit of the pattern
}

// Send this raw pattern to the Arduino's pins 0 through 7
void send_to_arduino_pins(unsigned int raw_pattern)
{
  digitalWrite(0, pattern_has_bit(raw_pattern, c7));
  digitalWrite(1, pattern_has_bit(raw_pattern, c6));
  digitalWrite(2, pattern_has_bit(raw_pattern, r1));
  digitalWrite(3, pattern_has_bit(raw_pattern, c0));
  digitalWrite(4, pattern_has_bit(raw_pattern, r3));
  digitalWrite(5, pattern_has_bit(raw_pattern, c5));
  digitalWrite(6, pattern_has_bit(raw_pattern, c3));
  digitalWrite(7, pattern_has_bit(raw_pattern, r0));
  // or one big PORTD call?
}

// Set up the Arduino's pins (call from setup once)
void begin_arduino_pins()
{
  for (int pin=0;pin<=7;pin++) pinMode(pin,OUTPUT);
}

int dataPin = 11;
int shiftPin = 12;
int outputPin = 13;

// 595 expects 8 bits: the 8 bottom pins of the 8x8 LED matrix
void send_to_shift_reg(unsigned int raw_pattern)
{
  send_bit_to_shift_reg(pattern_has_bit(raw_pattern, r4));
  send_bit_to_shift_reg(pattern_has_bit(raw_pattern, r6));
  send_bit_to_shift_reg(pattern_has_bit(raw_pattern, c1));
  send_bit_to_shift_reg(pattern_has_bit(raw_pattern, c2));
  send_bit_to_shift_reg(pattern_has_bit(raw_pattern, r7));
  send_bit_to_shift_reg(pattern_has_bit(raw_pattern, c4));
  send_bit_to_shift_reg(pattern_has_bit(raw_pattern, r5));
  send_bit_to_shift_reg(pattern_has_bit(raw_pattern, r2));
 
  digitalWrite(outputPin,0);
  digitalWrite(outputPin,1);
}

// Send another bit to the shift register
void send_bit_to_shift_reg(int bit)
{
  digitalWrite(dataPin,bit);
  digitalWrite(shiftPin,0);
  digitalWrite(shiftPin,1);
}

// Set up the shift register pins (call from setup)
void begin_shift_reg()
{
  pinMode(dataPin,OUTPUT);
  pinMode(shiftPin,OUTPUT);
  pinMode(outputPin,OUTPUT);  
}

unsigned int bitrimino = 0b0000000100001000;

void setup() {
  begin_shift_reg();
  begin_arduino_pins();
}

void loop() {
  // Send first block at top of screen
  send_pattern(bitrimino, 100);
  
}
