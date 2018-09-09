#include <ESP8266WiFi.h>
#include <dht.h>
dht DHT;
#define DHT11_PIN 5

//############## VARIABLE DECLARATION ##############
const char* ssid = "SAM"; // SSID i.e. Service Set Identifier is the name of your WIFI
const char* password = "1234556789"; // Your Wifi password, in case you have open network comment the whole statement.
const int trigPin = 14; //D5
const int echoPin = 12;  //D6
int buzzer = 13; //D7
int delayms=25;
int switch1 = 4; // GPIO4 or for NodeMCU you can directly write D2
int switch2 = 0; // GPIO0 or for NodeMCU you can directly write D3
//##################################################

WiFiServer server(80); // Creates a server that listens for incoming connections on the specified port, here in this case port is 80.

void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(buzzer, OUTPUT);
  pinMode(switch1, OUTPUT);
  digitalWrite(switch1, HIGH);
  pinMode(switch2, OUTPUT);
  digitalWrite(switch2, HIGH);

  //############## Connect to WiFi network ##############
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  //#####################################################

  //############## Start the server #####################
  server.begin();
  Serial.println("Server started");
  //#####################################################

  //############# Print the IP address ##################
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP()); //Gets the WiFi shield's IP address and Print the IP address of serial monitor
  Serial.println("/");
  //#####################################################
}

void loop() {
  //############ ULTRASONIC SENSOR ######################
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
  delay(100);
  if(cm>=3 && cm<=10){
    noTone(buzzer);
    beep(cm+30);
  }
  else if(cm>10 && cm<=200){noTone(buzzer);}
  else{
    tone(buzzer,1000);
    Serial.println("Collision!!");
  }
  //#####################################################

  //########## Check if a client has connected ##########
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  //#####################################################

  //######## Wait until the client sends some data ######
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  //#####################################################

  //######### Read the first line of the request ########
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
  //#####################################################

  //#################### SWITCH 1 #######################
  int value1,value2,master;
  if (request.indexOf("/CH1=ON") != -1)  {
    digitalWrite(switch1, LOW);
    value1 = LOW;
  }
  if (request.indexOf("/CH1=OFF") != -1)  {
    digitalWrite(switch1, HIGH);
    value1 = HIGH;
  }
  //#####################################################

  //#################### SWITCH 2 #######################
  if (request.indexOf("/CH2=ON") != -1)  {
    digitalWrite(switch2, LOW);
    value2 = LOW;
  }
  if (request.indexOf("/CH2=OFF") != -1)  {
    digitalWrite(switch2, HIGH);
    value2 = HIGH;
  }
  //#####################################################

  //#################### MASTER #########################
  if (request.indexOf("/MASTER=ON") != -1)  {
    digitalWrite(switch1, LOW);
    digitalWrite(switch2, LOW);
    value1 = LOW;
    value2 = LOW;
    master = LOW;
  }
  if (request.indexOf("/MASTER=OFF") != -1)  {
    digitalWrite(switch1, HIGH);
    digitalWrite(switch2, HIGH);
    value1 = HIGH;
    value2 = HIGH;
    master = HIGH;
  }
  //#####################################################

  //############### SERIAL OUTPUT #######################
  int chk = DHT.read11(DHT11_PIN);
  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);
  Serial.print("Distance = ");
  Serial.println(cm);
  /*
  Serial.print("Distance: ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  */
  //#####################################################

  //################ HTML WEB PAGE ######################
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head>");
  client.println("<title>Home Automation</title>");
  //client.println("<meta http-equiv=\"refresh\"\" content=\"5\"/>");
  client.println("</head>");
  client.println("<br><br>");
  client.println("<b>Temperature = </b>");
  client.println(DHT.temperature);
  client.println("<br><br>");
  client.println("<b>Humidity = </b>");
  client.println(DHT.humidity);
  client.println("<br><br>");
  client.println("<b>Distance = </b>");
  client.println(cm);
  
  //################### SWITCH 1 ########################
  client.println("<br><br>");
  client.println("Switch 1: <a href=\"/CH1=ON\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/CH1=OFF\"\"><button>Turn Off </button></a>");
  if(value1 == LOW) {
    client.print("SWITCH 1 ON<br><br>");
  }
  else if(value1 == HIGH){
    client.print("SWITCH 1 OFF<br><br>");
  }
  //#####################################################

  //################### SWITCH 2 ########################
  client.println("<br><br>");
  client.println("Switch 2: <a href=\"/CH2=ON\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/CH2=OFF\"\"><button>Turn Off </button></a>");
  if(value2 == LOW) {
    client.print("SWITCH 2 ON<br><br>");
  }
  else if(value2 == HIGH){
    client.print("SWITCH 2 OFF<br><br>");
  }
  //#####################################################

  //##################### MASTER ########################
  client.println("<br><br>");
  client.println("Master: <a href=\"/MASTER=ON\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/MASTER=OFF\"\"><button>Turn Off </button></a>");
  if(master == LOW) {
    client.print("Master ON<br><br>");
  }
  else if(master == HIGH){
    client.print("Master OFF<br><br>");
  }
  //#####################################################
  client.println("</html>");
  //#####################################################

  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
}

//#################### FUNCTIONS ########################
long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}

void beep(unsigned char delayms) { //creating function
  tone(buzzer, 1000); //Setting pin to high
  delay(delayms); //Delaying
  noTone(buzzer); //Setting pin to LOW
  delay(delayms); //Delaying
}
//#######################################################

