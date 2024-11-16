#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "JSS-STUDENT";
const char* password = "J55@2024&";
const char* serverUrl = "http://<server_ip>:3000/detect";  // Replace <server_ip> with your server's IP

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
}

void loop() {
    if (objectDetected()) { // Replace with your actual object detection logic
        sendDetection();
        delay(500);  // Avoid sending too frequently
    }
}

bool objectDetected() {
    // Your logic to detect the object within 7 cm
    return true; // Placeholder
}

void sendDetection() {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin(serverUrl);
        int httpResponseCode = http.GET();
        http.end();
    }
}
