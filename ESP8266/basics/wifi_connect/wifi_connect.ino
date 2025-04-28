#include <ESP8266WiFi.h>

// WiFi credentials
const char* ssid = "HNBGU_Guest";  
const char* password = "432154321"; 
void setup() {
  Serial.begin(115200);
  delay(10);

  Serial.println("\n\nStarting WiFi Connection...");

  // Initialize WiFi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to ");
  Serial.print(ssid);

  // Wait for connection (with timeout)
  unsigned long startTime = millis();
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");

    // Timeout after 30 seconds
    if (millis() - startTime > 30000) {
      Serial.println("\nFailed to connect!");
      Serial.println("Possible issues:");
      Serial.println("1. Wrong password");
      Serial.println("2. Weak signal");
      Serial.println("3. Network not available");
      Serial.println("4. Captive portal (guest networks)");
      return;
    }
  }

  // Connection successful
  Serial.println("\nWiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Signal Strength (RSSI): ");
  Serial.print(WiFi.RSSI());
  Serial.println(" dBm");
}

void loop() {
  // Monitor connection status
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Connection lost! Attempting to reconnect...");
    WiFi.reconnect();
    delay(5000); 
  }
}
