
int shockPin = 10; // Use Pin 10 as our Input
int shockVal = HIGH; // This is where we record our shock measurement
boolean bAlarm = false;
const int buzzer = 7; 

unsigned long lastShockTime; // Record the time that we measured a shock

int shockAlarmTime = 500; // Number of milli seconds to keep the shock alarm high


void setup ()
{
  Serial.begin(115200);  
  pinMode (shockPin, INPUT) ; // input from the KY-002
  pinMode(buzzer, OUTPUT);
}
void loop () 
{
  shockVal = digitalRead (shockPin) ; // read the value from our sensor
  
  if (shockVal == HIGH) // If we're in an alarm state
  {
    lastShockTime = millis(); // record the time of the shock
    // The following is so you don't scroll on the output screen
    if (!bAlarm){
      Serial.println("Shock Alarm");
      bAlarm = true;
      tone(buzzer, 1000); // Send 1KHz sound signal...
  delay(1000);        // ...for 1 sec
  noTone(buzzer);     // Stop sound...
  delay(1000);
    }
  }
  else
  {
    if( (millis()-lastShockTime) > shockAlarmTime  &&  bAlarm){
      Serial.println("no alarm");
      bAlarm = false;
    }
  }
}
