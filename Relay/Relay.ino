
int pin1 = 7 ;
int pin2 = 8 ;

void setup() {
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, HIGH);
  Serial.println("\n ON/OFF ? ");
  Serial.begin(115200);
}

int status = 0;

void loop() {


  if (Serial.available() > 0) {    // is a character available?
    Serial.println("\n ON/OFF ? ");
    status = Serial.read();


    if (status == 50) {
      digitalWrite(pin1, HIGH);
      Serial.println("TURNING OFF CH 1!");
    }
    else if (status == 49) {
      digitalWrite(pin1, LOW);
      Serial.println("TURNING ON CH 1!");
    }
    else if (status == 52) {
      digitalWrite(pin2, HIGH);
      Serial.println("TURNING OFF CH 2!");
    }
    else if (status == 51) {
      digitalWrite(pin2, LOW);
      Serial.println("TURNING ON CH 2!");
    }
    status = 0;
  }

}


