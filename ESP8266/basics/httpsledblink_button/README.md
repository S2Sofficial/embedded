# HTTP LED Blink using Button on HTML page connected via WiFi in ESP8266
![image](https://github.com/user-attachments/assets/3b70f07b-baf3-4012-b341-5d14dcc2cba4)

## Code
```c
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Replace with your network credentials
const char* ssid = "antivirus.exe";
const char* password = "antivirus.exe";

// Create a web server object that listens on port 80
ESP8266WebServer server(80);

// HTML page with buttons
const char* htmlPage = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta charset="utf-8">
  <title>ESP8266 LED Control</title>
  <style>
    body { font-family: Arial, sans-serif; text-align: center; margin-top: 50px; }
    button { padding: 15px 30px; font-size: 18px; margin: 5px; }
    #status { margin-top: 20px; font-size: 20px; }
  </style>
</head>
<body>
  <h1>ESP8266 LED Control</h1>
  <button onclick="toggleLED(1)">Turn ON</button>
  <button onclick="toggleLED(0)">Turn OFF</button>
  <p id="status"></p>
<script>
  function toggleLED(state) {
    var url = state ? '/ledon' : '/ledoff';
    fetch(url)
      .then(response => response.text())
      .then(text => {
        document.getElementById('status').innerHTML = text;
      })
      .catch(err => console.error('Request failed', err));
  }
</script>
</body>
</html>
)rawliteral";

// Handler for root path
void handleRoot() {
  Serial.println("HTTP GET: /");
  server.send(200, "text/html", htmlPage);
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
    Serial.println("HTTP GET: /ledon -> LED is ON");
  });

  server.on("/ledoff", HTTP_GET, []() {
    digitalWrite(LED_BUILTIN, HIGH); // Turn the LED off (HIGH = off)
    server.send(200, "text/plain", "LED is OFF");
    Serial.println("HTTP GET: /ledoff -> LED is OFF");
  });

  // Start the server
  server.begin();
  Serial.println("HTTP server started");
}

// Main loop listens for client requests
void loop() {
  server.handleClient();
  // Optional: monitor WiFi status and reconnect
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi disconnected! Attempting reconnect...");
    WiFi.reconnect();
  }
}

```

## Result
![image](https://github.com/user-attachments/assets/3b70f07b-baf3-4012-b341-5d14dcc2cba4)

```
HTTP GET: /ledon -> LED is ON
HTTP GET: /ledoff -> LED is OFF
HTTP GET: /ledon -> LED is ON
HTTP GET: /ledoff -> LED is OFF
```

https://github.com/user-attachments/assets/eca017d4-3bb0-42c3-9ec5-7df2e4a43c77
