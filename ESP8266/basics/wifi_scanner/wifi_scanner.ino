#include <ESP8266WiFi.h>

void setup() {
  Serial.begin(115200);
  delay(1000);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.println("\nScanning for WiFi networks...");
}

void loop() {
  int numNetworks = WiFi.scanNetworks();

  if (numNetworks == 0) {
    Serial.println("No networks found!");
  } else {
    Serial.print(numNetworks);
    Serial.println(" networks found:");
    Serial.println("----------------------------");
    Serial.println("ID | SSID             | RSSI | Encryption");
    Serial.println("----------------------------");

    for (int i = 0; i < numNetworks; i++) {
      Serial.printf("%2d | %-16s | %4d | %s\n",
                   i + 1,
                   WiFi.SSID(i).c_str(),
                   WiFi.RSSI(i),
                   getEncryptionType(WiFi.encryptionType(i)));
      delay(10);
    }
  }

  Serial.println("\nScan completed. Rescanning in 10s...");
  delay(10000);
}

// Fixed: Use 'WiFiEncryptionType' (or int) instead of 'wifi_auth_mode_t'
String getEncryptionType(int encryptionType) {
  switch (encryptionType) {
    case ENC_TYPE_NONE:
      return "OPEN";
    case ENC_TYPE_WEP:
      return "WEP";
    case ENC_TYPE_TKIP:
      return "WPA (TKIP)";
    case ENC_TYPE_CCMP:
      return "WPA2 (AES)";
    case ENC_TYPE_AUTO:
      return "WPA/WPA2 AUTO";
    default:
      return "UNKNOWN";
  }
}
