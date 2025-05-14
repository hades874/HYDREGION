#include <Arduino.h>
#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>

AsyncWebServer server(80);

const char* ssid = "Fire Robot";
const char* password = "12121212";

const char* PARAM_MESSAGE = "message";

String message;
int msg;

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

void setup() {

  Serial.begin(115200);

  //Initialise the Motor outpu pins
  pinMode (D2, OUTPUT);
  pinMode (D3, OUTPUT);
  pinMode (D4, OUTPUT);
  pinMode (D5, OUTPUT);

  pinMode (D0, OUTPUT);
  pinMode (D1, OUTPUT);
  //By default turn off both the motors

  pinMode (D6, OUTPUT);
  digitalWrite(D6, HIGH);

  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);
  digitalWrite(D5, LOW);



  //Start soft AP
  WiFi.softAP(ssid, password);

  Serial.println("Soft AP started.");
  Serial.print("SSID: ");
  Serial.println(ssid);
  Serial.print("Password: ");
  Serial.println(password);
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());


  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(200, "text/plain", "Hello, world");
  });

  // Send a GET request to <IP>/get?message=<message>
  server.on("/get031", HTTP_GET, [] (AsyncWebServerRequest * request) {
    if (request->hasParam(PARAM_MESSAGE)) {
      message = request->getParam(PARAM_MESSAGE)->value();
      Serial.println(message);
      msg = message.toInt();
      switch (msg) {
        case 1:
          digitalWrite(D2, LOW);
          digitalWrite(D3, HIGH);
          digitalWrite(D4, LOW);
          digitalWrite(D5, HIGH);
          break;
        case 2:
          digitalWrite(D2, HIGH);
          digitalWrite(D3, LOW);
          digitalWrite(D4, HIGH);
          digitalWrite(D5, LOW);
          break;
        case 3:
          digitalWrite(D2, HIGH);
          digitalWrite(D3, LOW);
          digitalWrite(D4, LOW);
          digitalWrite(D5, HIGH);
          break;
        case 4:
          digitalWrite(D2, LOW);
          digitalWrite(D3, HIGH);
          digitalWrite(D4, HIGH);
          digitalWrite(D5, LOW);
          break;


        case 5:
          digitalWrite(D2, LOW);
          digitalWrite(D3, LOW);
          digitalWrite(D4, LOW);
          digitalWrite(D5, LOW);
          break;

        case 7:
          analogWrite(D0, 140);
          analogWrite(D1, 130);
          break;
        case 8:
          analogWrite(D0, 170);
          analogWrite(D1, 170);
          break;
        case 9:
          analogWrite(D0, 210);
          analogWrite(D1, 210);
          break;
        case 10:
          digitalWrite(D6, LOW);
          break;
        case 11:
          digitalWrite(D6, HIGH);
          break;
      }
    } else {
      message = "No message sent";
      Serial.println("no msg");
    }
    request->send(200, "text/plain", message);
  });

  // Send a POST request to <IP>/post with a form field message set to <message>
  server.on("/post", HTTP_POST, [](AsyncWebServerRequest * request) {
    if (request->hasParam(PARAM_MESSAGE, true)) {
      message = request->getParam(PARAM_MESSAGE, true)->value();
    } else {
      message = "No message sent";
    }
    request->send(200, "text/plain", message);
  });

  server.onNotFound(notFound);

  server.begin();
}

void loop() {
}
