#include <Wire.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <LiquidCrystal_I2C.h>
#include "env.h"


// Try changing the address to 0x3F if 0x27 doesn't work
LiquidCrystal_I2C lcd(0x27, 16, 2);


void setup() {
  Serial.begin(115200);
  // Initialize I2C explicitly on pins 21 (SDA) and 22 (SCL)
  Wire.begin(21, 22);
 
  lcd.init();
  lcd.backlight();


  // Set WiFi mode to station
  WiFi.mode(WIFI_STA);
  if (IS_WOKWI)
    WiFi.begin(SSID, PASS, CHANNEL);
  else
    WiFi.begin(SSID, PASS);


  Serial.print("Connecting to Wi-Fi");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Connecting WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nWiFi connected!");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WiFi connected!");
}


void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    // Create a secure client for HTTPS communication
    WiFiClientSecure client;
    client.setInsecure(); // Bypass SSL verification (for testing)


    // Initialize HTTPClient for sending requests
    HTTPClient https;


    // Build the full URL by appending "/message" to your endpoint
    String url = String(ENDPOINT) + "/message";
    https.begin(client, url);


    // Add the required API key header to the GET request
    https.addHeader("api-key", API_KEY);


    // Send the GET request
    int httpCode = https.GET();


    if (httpCode > 0) { // If request is successful
      Serial.print("HTTP Code: ");
      Serial.println(httpCode);


      if (httpCode == HTTP_CODE_OK) { // 200 OK
        String payload = https.getString();
        Serial.println("Payload: " + payload);


        // Parse the JSON payload
        StaticJsonDocument<200> doc;
        DeserializationError error = deserializeJson(doc, payload);
        if (!error) {
          // Extract the two lines from the JSON response
          const char* line1 = doc["line_1"];
          const char* line2 = doc["line_2"];


          // Update the LCD with the retrieved messages
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print(line1);
          lcd.setCursor(0, 1);
          lcd.print(line2);
        } else {
          Serial.print("JSON parsing error: ");
          Serial.println(error.c_str());
        }
      }
    } else {
      Serial.print("GET request failed: ");
      Serial.println(https.errorToString(httpCode));
    }


    // End the HTTP connection
    https.end();


    // Wait 10 seconds before making the next request
    delay(10000);
  } else {
    Serial.println("WiFi not connected");
  }
}



