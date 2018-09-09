//Example code KY012 active buzzer
int speakerPin = 6;
void setup () {
  pinMode (speakerPin, OUTPUT);
}
void loop () {
  tone (speakerPin, 1000);
  delay (1000);
  noTone (speakerPin);
  delay (1000);
}
