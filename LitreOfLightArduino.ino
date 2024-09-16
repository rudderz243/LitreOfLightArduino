#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

// define the pins the components will use
#define LIGHT_PIN 5
#define DAYLIGHT_SENSOR_PIN A0

// set the AP details
#ifndef APSSID
#define APSSID "litre of light"
#define APPSK "rustyspoon"
#endif

// assign them to variables
const char *ssid = APSSID;
const char *password = APPSK;

// create a web server instance on port 80
ESP8266WebServer server(80);

// create enums for the light sensor sensitivity
enum LightSensitivity {
  L,
  M,
  H
};

// create enums for the mode
enum LightMode {
  AUTOMATIC,
  MANUAL
};

// initialise with default values
LightSensitivity CurrentSensitivity = M;
LightMode CurrentMode = AUTOMATIC;

void setup() {
  // prepare the pins 
  pinMode(LIGHT_PIN, OUTPUT);
  pinMode(DAYLIGHT_SENSOR_PIN, INPUT);
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  
  // initialise wifi and web server
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  // define the API routes
  server.on("/LightOn", HandleLightOn);
  server.on("/LightOff", HandleLightOff);
  server.on("/AutomaticMode", HandleAutomaticMode);
  server.on("/Low", HandleLowSensitivity);
  server.on("/Medium", HandleMediumSensitivity);
  server.on("/High", HandleHighSensitivity);
  server.on("/Status", HandleStatus);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  // get a reading of current ambient light
  int LightSensorReading = analogRead(DAYLIGHT_SENSOR_PIN);
  server.handleClient();

  // check whether the bottle is in manual mode 
  if (CurrentMode != MANUAL) {
    // LOW setting
    if (CurrentSensitivity == L) {
      if (LightSensorReading < 90) {
        digitalWrite(LIGHT_PIN, HIGH);
      } else {
        digitalWrite(LIGHT_PIN, LOW);
      }
      // MEDIUM setting
    } else if (CurrentSensitivity == M) {
      if (LightSensorReading < 60) {
        digitalWrite(LIGHT_PIN, HIGH);
      } else {
        digitalWrite(LIGHT_PIN, LOW);
      }
      // HIGH setting
    } else if (CurrentSensitivity == H) {
      if (LightSensorReading < 30) {
        digitalWrite(LIGHT_PIN, HIGH);
      } else {
        digitalWrite(LIGHT_PIN, LOW);
      }
    }
  }
  // delay to prevent flickering
  delay(1000);
}

// turn the light ON for testing, enables MANUAL mode
void HandleLightOn() {
  CurrentMode = MANUAL;
  digitalWrite(LIGHT_PIN, HIGH);
  server.send(200, "application/json", "{ \"message\" : \"light on\" }");
}

// turn the light OFF for testing, enables MANUAL mode
void HandleLightOff() {
  CurrentMode = MANUAL;
  digitalWrite(LIGHT_PIN, LOW);
  server.send(200, "application/json", "{ \"message\" : \"light off\" }");
}

// set it back to AUTOMATIC when done testing
void HandleAutomaticMode() {
  CurrentMode = AUTOMATIC;
  server.send(200, "application/json", "{ \"message\" : \"automatic mode enabled\" }");
}

// change the sens
void HandleLowSensitivity() {
  CurrentSensitivity = L;
  server.send(200, "application/json", "{ \"message\" : \"low threshold set\" }");
}

// change the sens
void HandleMediumSensitivity() {
  CurrentSensitivity = M;
  server.send(200, "application/json", "{ \"message\" : \"medium threshold set\" }");
}

// change the sens
void HandleHighSensitivity() {
  CurrentSensitivity = H;
  server.send(200, "application/json", "{ \"message\" : \"high threshold set\" }");
}

// return the information needed by the Android app
void HandleStatus() {
  server.send(200, "application/json", "{ \"Mode\" : \"" + (String)CurrentMode + "\", \"Sensitivity\" : \"" + (String)CurrentSensitivity + "\", \"light\" : \"" + (String)analogRead(DAYLIGHT_SENSOR_PIN) + "\" }");
}
