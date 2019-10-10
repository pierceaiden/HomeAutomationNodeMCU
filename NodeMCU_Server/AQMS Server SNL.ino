
/*
Make the following connections
1.MQ-4 Sensor
  DOUT - D2
2.Temperature and Humidity Sensor
  Data - D1
3.MQ-7 Sensor
  Analog Pin A0 - A0
  
*/

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <dht.h>
//dht DHT;
//#define DHT11_PIN 5 //D1

//############## VARIABLE DECLARATION ##############
const char* ssid = "SAM"; // SSID i.e. Service Set Identifier is the name of your WIFI
const char* password = "1234556789"; // Your Wifi password, in case you have open network comment the whole statement.
//int delayms=25;
//const int mq4 = 4; //D2
//int limit;
//##################################################

ESP8266WebServer server(80);                //Webserver Object

const char * indexMsg = "<!DOCTYPE html>"
"<html>"
"<head>"
"<title>Switch Controller</title>"
"<style>"
"* {box-sizing: border-box;}"
".left {width: 50%;float: left;}"
".right {width: 50%;float: right;}"
"header, footer {"
"padding: 0.5em;"
"color: white;"
"background-color: black;"
"clear: right;"
"text-align: center;"
"}"
".onbutton {"
"background-color: #4CAF50;"
"border: none;"
"color: white;"
"padding: 15px 32px;"
"text-align: center;"
"text-decoration: none;"
"display: inline-block;"
"font-size: 20px;"
"margin: 4px 2px;"
"cursor: pointer;"
"}"
".offbutton {"
"background-color: red;"
"border: none;"
"color: white;"
"padding: 15px 32px;"
"text-align: center;"
"text-decoration: none;"
"display: inline-block;"
"font-size: 20px;"
"margin: 4px 2px;"
"cursor: pointer;"
"}"
"</style>"
"</head>"
"<header>"
"<h1>SWITCH CONTROLLER</h1>"
"</header>"
"<br>"
"<body>"
"<font size=""6""><b>"
"<div class=""left"">"
"<form method=""post"">"
"&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Switch 1<br>"
"<button class=onbutton name=""ON1"">ON</button>&nbsp;"
"<button class=offbutton name=""OFF1"">OFF</button><br>"
"&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Switch 2<br>"
"<button class=onbutton name=""ON2"">ON</button>&nbsp;"
"<button class=offbutton name=""OFF2"">OFF</button><br>"
"&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Switch 3<br>"
"<button class=onbutton name=""ON3"">ON</button>&nbsp;"
"<button class=offbutton name=""OFF3"">OFF</button><br>"
"&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Switch 4<br>"
"<button class=onbutton name=""ON4"">ON</button>&nbsp;"
"<button class=offbutton name=""OFF4"">OFF</button><br>"
"&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Switch 5<br>"
"<button class=onbutton name=""ON5"">ON</button>&nbsp;"
"<button class=offbutton name=""OFF5"">OFF</button><br>"
"</form>"
"</div>"
"<div class=""right"">"
"<form method=""post"">"
"&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Switch 6<br>"
"<button class=onbutton name=""ON6"">ON</button>&nbsp;"
"<button class=offbutton name=""OFF6"">OFF</button><br>"
"&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Switch 7<br>"
"<button class=onbutton name=""ON7"">ON</button>&nbsp;"
"<button class=offbutton name=""OFF7"">OFF</button><br>"
"&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Switch 8<br>"
"<button class=onbutton name=""ON8"">ON</button>&nbsp;"
"<button class=offbutton name=""OFF8"">OFF</button><br>"
"&nbsp;&nbsp;&nbsp;Switch ALL<br>"
"<button class=onbutton name=""allon"">ON</button>&nbsp;"
"<button class=offbutton name=""alloff"">OFF</button><br>"
"&nbsp;CHECK<br>"
"<button class=onbutton name=""check"">CHECK</button>&nbsp;"
"</form>"
"</div>"
"</font>"
"<footer>Samdharsi Kumar</footer>"
"<font size=""6"">"
"Status:"
"</font></<b>"
"</body>"
"</html>";


void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  //delay(10);
  // pinMode(mq4,INPUT);

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
//=====================================================

//############# Print the IP address ##################
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP()); //Gets the WiFi shield's IP address and Print the IP address of serial monitor
  Serial.println("/");
//=====================================================


//############## Start the server #####################
  server.on("/", handleindex);    //Associate the handler function to the path
  server.begin();
  Serial.println("Server Listening");
//=====================================================

}

void loop() {
  server.handleClient();                    //Handling of incoming requests


//#################### MQ7 SENSOR #####################
  // int sensorValue = analogRead(A0);

  //Serial.print("MQ7 value: ");
  //Serial.println(sensorValue);
//=====================================================
//#####################  MQ4  #########################
  // limit = digitalRead(mq4);
//=====================================================

//############### SERIAL OUTPUT #######################
  // int chk = DHT.read11(DHT11_PIN);
  // Serial.print("Temperature = ");
  // Serial.println(DHT.temperature);
  // Serial.print("Humidity = ");
  // Serial.println(DHT.humidity);
  // Serial.print("CO = ");
  // Serial.println(sensorValue);
  // Serial.print("MQ-4 Limit: ");
  // Serial.println(limit);
//=====================================================

//################ HTML WEB PAGE ######################
  // client.println("HTTP/1.1 200 OK");
  // client.println("Content-Type: text/html");
  // client.println(""); //  do not forget this one
  // client.println("<!DOCTYPE HTML>");
  // client.println("<html>");
  // client.println("<head>");
  // client.println("<title>AQMS</title>");
  // //client.println("<meta http-equiv=\"refresh\"\" content=\"5\"/>");
  // client.println("</head>");
  // client.println("<h1 align=center>Air Quality Monitoring System</h1>");
  // client.println("<br><br>");
  // client.println("<b>Temperature = </b>");
  // client.println(DHT.temperature);
  // client.println("<br><br>");
  // client.println("<b>Humidity = </b>");
  // client.println(DHT.humidity);
  // client.println("<br><br>");
  // client.println("<b>CO = </b>");
  // client.println(sensorValue);
  // client.println("<br><br>");
  // client.println("<b>Gas Limit: </b>");
  // client.println(limit);
  // client.println("</html>");
//################ WEB PAGE ENDS ######################
}

void handleindex() {            //Handler for the root path
  server.send(200, "text/html", indexMsg);
} 

