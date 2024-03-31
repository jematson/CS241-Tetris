const int button1 = 2;



void setup() {
  pinMode(button1, INPUT_PULLUP);
  Serial.begin(57600);

}

  bool state1 = false;
  bool prevState1 = state1;

void loop() {
  state1 = !digitalRead(button1);

  delay(10);

  if(!digitalRead(button1) && state1 != prevState1)
  {
    Serial.println("Button1 is pushed");
    state1 = true;
  }

  prevState1 = state1;
}
