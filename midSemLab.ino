//#include <WiFi.h>
//#include <WiFiClient.h>
//#include <WebServer.h>
//#include <ESPmDNS.h>
//
//const int trigPin = 22;
//const int echoPin = 25 ;
//int wLed = 26;
//
////define sound speed in cm/uS
//#define SOUND_SPEED 0.034
//#define CM_TO_INCH 0.393701
//
//long duration;
//float distanceCm;
//float distanceInch;
//
//
//// include the library code:
//#include <LiquidCrystal.h>
// 
//// initialize the library with the numbers of the interface pins
//LiquidCrystal lcd(19, 23, 18, 17, 16, 15);
//
//
//
//
//
//const char* ssid = "Ben.Fra.Pri";
//const char* password = "M633SFTK";
//
//WebServer server(80);
//
//
//
//void handleRoot() {
//  //digitalWrite(led, 1);
//  server.send(200, "text/plain", "hello from esp32!");
//  //digitalWrite(led, 0);
//}
//
//void handleSensorData() {
////  //digitalWrite(led, 1);
////   hum = dht.readHumidity();
////   temp= dht.readTemperature();
////   String msg = "Temperature reading = ";
////   msg = msg + temp;
////   msg = msg + " & Humidity reading = ";
////   msg = msg + hum;
////  server.send(200, "text/plain",msg);
//// // digitalWrite(led, 0);
//}
//
//
//void handleMidsem() {
//
//   String msg = "Handle for midsem works";
// 
//  server.send(200, "text/plain",msg);
//
//}
//void operation(){
//    lcd.setCursor(0, 1);
//  // Clears the trigPin
//  digitalWrite(trigPin, LOW);
//  delayMicroseconds(2);
//  // Sets the trigPin on HIGH state for 10 micro seconds
//  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(10);
//  digitalWrite(trigPin, LOW);
//  
//  // Reads the echoPin, returns the sound wave travel time in microseconds
//  duration = pulseIn(echoPin, HIGH);
//  delay(200);
//  // Calculate the distance
//  distanceCm = duration * SOUND_SPEED/2;
//  if (distanceCm >= 15){
//    digitalWrite(wLed, HIGH);
//    }
//
//    else digitalWrite(wLed, LOW);  
//  // Convert to inches
//  distanceInch = distanceCm * CM_TO_INCH;
//  
//  // Prints the distance in the Serial Monitor
//  Serial.print("Distance (cm): ");
//  Serial.println(distanceCm);
//  lcd.print(distanceCm);
//  distanceCm = 0;
//  Serial.print("Distance (inch): ");
//  Serial.println(distanceInch);
//  
//  delay(2000);
//}
//
//void handleNotFound() {
//
// 
//  String message = "File Not Found\n\n";
//  message += "URI: ";
//  message += server.uri();
//  message += "\nMethod: ";
//  message += (server.method() == HTTP_GET) ? "GET" : "POST";
//  message += "\nArguments: ";
//  message += server.args();
//  message += "\n";
//  for (uint8_t i = 0; i < server.args(); i++) {
//    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
//  }
//  server.send(404, "text/plain", message);
//
//}
//
//void setup(void) {
//
//  
//
//  Serial.begin(115200);
//
//
//
//
//  
//  WiFi.mode(WIFI_STA);
//  WiFi.begin(ssid, password);
//  Serial.println("");
//
//  // Wait for connection
//  while (WiFi.status() != WL_CONNECTED) {
//    delay(500);
//    Serial.print(".");
//  }
//  Serial.println("");
//  Serial.print("Connected to ");
//  Serial.println(ssid);
//  Serial.print("IP address: ");
//  Serial.println(WiFi.localIP());
//
//  if (MDNS.begin("esp32")) {
//    Serial.println("MDNS responder started");
//  }
//
//  server.on("/", handleRoot);
//
//  server.on("/inline", []() {
//    server.send(200, "text/plain", "this works as well");
//  });
//
//// .......
//  server.on("/sensorData",handleSensorData);
//
//  server.on("/midSemData",handleMidsem);
//
//
//  server.onNotFound(handleNotFound);
//
//  server.begin();
//  Serial.println("HTTP server started");
//
//  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
//  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
//  pinMode(wLed, OUTPUT);
//
//
//  lcd.begin(16, 2);
//  // Print a message to the LCD.
//  lcd.print("Distance");
//}
//
//void loop(void) {
//  server.handleClient();
//  //operation();
//  delay(2);//allow the cpu to switch to other tasks
//}
//
//


//-------------










/** 
 *  No AJAX
 *  This extends Hello Server and adds an HTTPCLient to 
 *  make requests to a remote service.
 *  This nodes must connect to the network in STA mode.
 *  (not AP mode) 
 *  
 *  Connect as client by visiting local_ipaddress/client
 */

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>  //because of HTTPClient use
#include "htmltext.h"
#define USE_SERIAL Serial

WiFiMulti wifiMulti;
const char* ssid = "Ben.Fra.Pri";
const char* password = "M633SFTK";



int LEDR = LOW;
int LEDG = LOW;
int counter = 0;
const int trigPin = 22;
const int echoPin = 25 ;
int wLed = 26;
String manualState = "OFF";


//define sound speed in cm/uS
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

long duration;
float distanceCm;
float distanceInch;


// include the library code:
#include <LiquidCrystal.h>
 
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(19, 23, 18, 17, 16, 15);


WebServer server(80);

const int led = 2;

void handleRoot() {
  digitalWrite(led, 1);
  server.send(200, "text/plain", "hello from esp32!");
  digitalWrite(led, 0);
}


//this returns HTML
void handleYaw() {
  
  server.send(200, "text/html", page);
  
}

void handleCurrentLevel(){
  String theData = String(distanceCm);

  String mssg = "The Current Level is ";
  mssg += theData;
  server.send(200, "text/plain", mssg);
  
}

void handlePush(){
  doGETRequest();
}


void handleNotFound() {
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void setup(void) {
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(wLed, OUTPUT);


  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Distance");
  
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  wifiMulti.addAP("SSID", "PASSWORD");
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp32")) {    //multicast DNS service
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);
 
  server.on("/yaw", handleYaw);  

  server.on("/LEDGurl",LEDGfunct);
  server.on("/LEDRurl",LEDRfunct);
  server.on("/zeroUrl",zerofunct);
  server.on("/push",handlePush);
//  server.on("/countUrl",countFunct);

  

  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);
//  server.on("/midSemData", doGETRequest);
  server.on("/currentLevel", handleCurrentLevel);
 
  
  server.begin();
  Serial.println("HTTP server started");
}
//String url = String("http://192.168.130.13/sensordata/index.php?temperature=");
String url = String("http://192.168.2.13/sensorproject/toinsert.php?level=");

void perform(){
    delay(2000);


       url = url+ String(distanceCm);
    url = url + String("&cid=2");


    USE_SERIAL.println(" ");
    
    USE_SERIAL.println(" ");

     // wait for WiFi connection
    while((wifiMulti.run() == WL_CONNECTED)) {

        HTTPClient http;

        USE_SERIAL.print("[HTTP] begin...\n");
        // configure traged server and url
        //http.begin("https://www.howsmyssl.com/a/check", ca); //HTTPS
        // http.begin("http://example.com/index.html"); //HTTP
        http.begin(url); //HTTP


        USE_SERIAL.print("[HTTP] GET...\n");
        // start connection and send HTTP header
        int httpCode = http.GET();

        // httpCode will be negative on error
        if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

            // file found at server
            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                USE_SERIAL.println(payload);
            }
        } else {
            USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
    }
  url = String("http://192.168.2.13/sensorproject/toinsert.php?level=");
    delay(5000);
}

void LEDGfunct(){

  Serial.print("led Green pressed");
  Serial.print("\n");

  if (manualState == "ON"){
      LEDG = !LEDG;
  digitalWrite(wLed, LEDG);
 
  String str = "ON";    //modification below
  if(LEDG == LOW) str = "OFF";
  server.send(200, "text/plain", str);
  }
  
 
}

//modified to use AJAX
void LEDRfunct()
{
  
  Serial.print("led red pressed");
  Serial.print("\n");
  String str = "ON";    //very little returned
  if(LEDR == LOW){
     str = "OFF";
     LEDR = HIGH;
   };
   if(LEDR ==HIGH){
    str = "OFF";
    LEDR = LOW;
   }
  server.send(200, "text/plain", str);
  if (manualState == "OFF"){
    Serial.println("manual is ON");
    manualState = "ON";
  }
  else{
        Serial.println("manual is OFF");
    manualState = "OFF";
  }
  
}

void zerofunct() // function to zero counter
{
  String theData = String(distanceCm);

  String mssg = "The Current Level is ";
  mssg += theData;
  server.send(200, "text/plain", mssg);
}

//new optional funciton to always update the counter
void countFunct() {
  String str = String(counter);   //only this is sent
  server.send(200, "text/plain", str);

}

void operation(){
   // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  delay(200);
  // Calculate the distance
  distanceCm = duration * SOUND_SPEED/2;

  if(manualState == "OFF"){
     if (distanceCm >= 15){
    digitalWrite(wLed, HIGH);
    }

    else digitalWrite(wLed, LOW);  
   }
 
  // Convert to inches
  distanceInch = distanceCm * CM_TO_INCH;
  
  // Prints the distance in the Serial Monitor
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  lcd.print(distanceCm);
 
//  Serial.print("Distance (inch): ");
//  Serial.println(distanceInch);
  
  delay(2000);
}

void loop(void) {
  server.handleClient();

     // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  delay(200);
  // Calculate the distance
  distanceCm = duration * SOUND_SPEED/2;
  if (manualState == "OFF"){
    // meaning the auto is on
      if (distanceCm >= 15){
    digitalWrite(wLed, HIGH);
    }

    else digitalWrite(wLed, LOW);  
   }

  // Convert to inches
  distanceInch = distanceCm * CM_TO_INCH;
  
  // Prints the distance in the Serial Monitor
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  lcd.print(distanceCm);
 
//  Serial.print("Distance (inch): ");
//  Serial.println(distanceInch);
  
  delay(2000);


  
  
  delay(2);//allow the cpu to switch to other tasks
}
       
String serverName="http://192.168.2.13/sensorproject/toinsert.php?level=";  //need the http!
//String serverName="http://localhost/sensorproject//index2.html";  //need the http!
void doGETRequest(){
  //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;      
      String serverPath = serverName +String(distanceCm)+ "&cid=2";
      
      // Your Domain name with URL path or IP address with path
      http.begin(serverPath.c_str());  //alt use char host[] = "example.com";
      
      // Send HTTP GET request
      int httpResponseCode = http.GET();
      
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
        server.send(200, "text/html", payload);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
}
//=====
/*

//  //Check WiFi connection status
//    if(WiFi.status()== WL_CONNECTED){
//      HTTPClient http;      
//      String serverPath = serverName;
//      // Your Domain name with URL path or IP address with path
//      http.begin(serverPath);  //alt use char host[] = "example.com";
//      
//      // Send HTTP GET request
//      int httpResponseCode = http.GET();
//      
//      if (httpResponseCode>0) {
//        Serial.print("HTTP Response code: ");
//        Serial.println(httpResponseCode);
//        String payload = http.getString();
//        Serial.println(payload);
//        server.send(200, "text/html", payload);
//      }
//      else {
//        Serial.print("Error code: ");
//        Serial.println(httpResponseCode);
//      }
//      // Free resources
//      http.end();
//    }
//    else {
//      Serial.println("WiFi Disconnected");
//    }

  
 */
