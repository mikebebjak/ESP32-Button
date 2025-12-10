#include <WiFi.h>
#include <HTTPClient.h>
#include "codes.h"

#define PWR_EN 2  // GPIO2 to keep the ESP32 powered on when the button isn't held
#define LED_R 3
#define LED_G 5
#define LED_B 4

int connectToWiFi() {
  for (int i = 0; i < wifi_network_count; i++) 
  {
    WiFi.begin(wifi_ssids[i], wifi_passwords[i]);
    int retries = 0;

    while (WiFi.status() != WL_CONNECTED && retries++ < 10) {
      delay(500);
    }
    if (WiFi.status() == WL_CONNECTED) 
      return 1;
  }
  return 0;
}

int sendToSheet() {
  if (WiFi.status() == WL_CONNECTED)
  {
    HTTPClient http;
    http.begin(scriptURL); //scriptURL from your codes.h header
    http.addHeader("Content-Type", "application/json");
    int httpCode = http.POST("{}");  // Send (mostly) empty POST to run the Google Sheets script
    http.end();
    return httpCode;
  }
}

void setup() {
  pinMode(PWR_EN, OUTPUT);
  digitalWrite(PWR_EN, HIGH);
  delay(500);

  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);

  analogWrite(LED_R, 100);
  digitalWrite(LED_B, HIGH);
  digitalWrite(LED_G, HIGH);

  int code = 7;
  Serial0.begin(115200);
  Serial0.println("Connecting...");
  
  bool connected = connectToWiFi();

  if(connected)
  {
    digitalWrite(LED_B, LOW);
    delay(500);
    digitalWrite(LED_B, HIGH);

    Serial0.println("Connected. Sending POST...");
    code = sendToSheet();
    Serial0.println(code);

    if(code == 200)
      Serial0.println("Success!");
    else
      Serial0.println("POST failed");
  }
  else
  {
    Serial0.println("Failed to connect to Wifi");
  }

  WiFi.disconnect(true);
  
  digitalWrite(LED_G, LOW);
  delay(1000);
  digitalWrite(LED_G, HIGH);

  digitalWrite(PWR_EN, LOW);
}

void loop() {
  // unused
}