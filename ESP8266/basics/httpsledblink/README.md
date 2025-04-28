# Led blink using HTTP request via WiFi

## Code
```c
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Replace with your network credentials
const char* ssid = "antivirus.exe";
const char* password = "antivirus.exe";

// Create a web server object that listens on port 80
ESP8266WebServer server(80);

// Handler for root path
void handleRoot() {
  server.send(200, "text/plain", "ESP8266 LED Control\nUse /ledon to turn ON the LED, /ledoff to turn OFF the LED.");
}

// Setup function runs once at startup
void setup() {
  // Initialize serial communication for debug output
  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.println("Booting...");

  // Initialize the onboard LED pin
  pinMode(LED_BUILTIN, OUTPUT);
  // Turn LED off at start (HIGH = off for most ESP8266 boards)
  digitalWrite(LED_BUILTIN, HIGH);

  // Connect to WiFi network
  Serial.printf("Connecting to %s", ssid);
  WiFi.begin(ssid, password);

  // Keep trying to connect until successful
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  // Connected to WiFi
  Serial.println("WiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Define routes
  server.on("/", HTTP_GET, handleRoot);

  server.on("/ledon", HTTP_GET, []() {
    digitalWrite(LED_BUILTIN, LOW);  // Turn the LED on (LOW = on)
    server.send(200, "text/plain", "LED is ON");
  });

  server.on("/ledoff", HTTP_GET, []() {
    digitalWrite(LED_BUILTIN, HIGH); // Turn the LED off (HIGH = off)
    server.send(200, "text/plain", "LED is OFF");
  });

  // Start the server
  server.begin();
  Serial.println("HTTP server started");
}

// Main loop listens for client requests
void loop() {
  server.handleClient();
}

```
## Output
![image](https://github.com/user-attachments/assets/0fc21aeb-2410-4fdb-a9f2-0e7cd0d101a4)
