#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Innovex_Hardware";
const char* password = "Inn0vexug@2024!";

// The endpoint you created in Node.js
const char* serverName = "http://192.168.7.1:3000/update";

const int ledPin = 2; // Pin 2 is the built-in blue LED on most ESP32 dev boards
bool ledOn = false;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi network!");
}

void loop() {
  if(WiFi.status() == WL_CONNECTED){
    HTTPClient http;
    http.begin(serverName);
    http.addHeader("Content-Type", "application/json");

    // Toggle the LED state for demonstration
    ledOn = !ledOn;
    digitalWrite(ledPin, ledOn ? HIGH : LOW);
    String state = ledOn ? "ON" : "OFF";

    // Create and send the JSON payload
    String jsonPayload = "{\"state\":\"" + state + "\"}";
    int httpResponseCode = http.POST(jsonPayload);

    Serial.print("Sent: " + state + " | Server Response: ");
    Serial.println(httpResponseCode);
    
    http.end();
  }
  
  // Wait 2 seconds before sending the next update
  delay(2000); 
}