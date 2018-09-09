const int trigPin = 11;
const int echoPin = 10;
int buzzerPin = 6; //Define buzzerPin
int delayms=25;

void setup() {
  Serial.begin(115200);
  pinMode(buzzerPin, OUTPUT);
}

void loop()
{
  long duration,cm;
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  cm = microsecondsToCentimeters(duration);
  Serial.print("Distance: ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  delay(100);
  if(cm>=3 && cm<=20){
    noTone(buzzerPin);
    beep(cm+10);
  }
  else if(cm>20 && cm<=200){noTone(buzzerPin);}
  else{
    tone(buzzerPin,1000);
    Serial.print("Collision!!");
  }
}

long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}

void beep(unsigned char delayms) { //creating function
  tone(buzzerPin, 1000); //Setting pin to high
  delay(delayms); //Delaying
  noTone(buzzerPin); //Setting pin to LOW
  delay(delayms); //Delaying
}


