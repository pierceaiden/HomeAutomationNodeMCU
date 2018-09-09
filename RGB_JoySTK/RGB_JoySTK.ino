int redPin= 10;
int greenPin = 11;
int bluePin = 12;
const int SW_pin = 2; // digital pin connected to switch output
const int X_pin = 0; // analog pin connected to X output
const int Y_pin = 1; // analog pin connected to Y output
void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  Serial.begin(115200);
}
void loop() {
    if(analogRead(X_pin)<25 && analogRead(Y_pin)==515)
    setColor(255, 0, 0); // Red Color
  if(analogRead(X_pin)>900 && analogRead(Y_pin)==515)
    setColor(0, 255, 0); // Green Color
  if(analogRead(X_pin)==510 && analogRead(Y_pin)<15)
    setColor(0, 0, 255); // Blue Color
  if(analogRead(X_pin)==510 && analogRead(Y_pin)>900)
    setColor(170, 0, 255); // Purple Color
  if(digitalRead(SW_pin)==LOW)
    setColor(255, 255, 255); // White Color
  
}
void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}
