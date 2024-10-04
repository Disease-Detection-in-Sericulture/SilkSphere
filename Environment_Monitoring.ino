//Environment Sensing code using ESP32 with DHT11 and MQ135 sensor.

#include <DHT.h>        // Including library for DHT
#include "MQ135.h"
#include <WiFi.h>       // For ESP32 WiFi
#include "ThingSpeak.h" // Include ThingSpeak library

// WiFi credentials
const char *ssid = "Wifi_Name";  
const char *pass = "Wifi_Password";

// ThingSpeak details
unsigned long myChannelNumber = Channel_ID;   
const char * myWriteAPIKey = "API_Key";   

// Pin definitions for ESP32
#define DHTPIN 4        // DHT11 data connected to GPIO 4 (D2 on ESP32)
#define MQ135PIN 34     // MQ-135 connected to GPIO 34 (A0 on ESP32)

DHT dht(DHTPIN, DHT11); // Initialize DHT sensor
MQ135 gasSensor = MQ135(MQ135PIN);  // Initialize MQ-135 sensor

WiFiClient client;  // WiFi client to communicate with the server

void setup() {
  Serial.begin(115200);
  dht.begin();  // Initialize DHT sensor
  ThingSpeak.begin(client); // Initialize ThingSpeak

  // Connect to WiFi
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, pass);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
}

void loop() {
  // Read DHT11 sensor values
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  // Read MQ-135 sensor value
  int air_quality = gasSensor.getPPM();

  // Calculate air quality percentage
  float air_quality_percent = air_quality_ppm / 100000.0;

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Print sensor data to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print("°C, Humidity: ");
  Serial.print(h);
  Serial.print("%, Air Quality: ");
  Serial.print(air_quality_percent);
  Serial.println(" %");

  // Send data to ThingSpeak
  ThingSpeak.setField(1, t);
  ThingSpeak.setField(2, h);
  ThingSpeak.setField(3, air_quality_percent);
  
  int responseCode = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  
  if (responseCode == 200) {
    Serial.println("Data sent to ThingSpeak successfully.");
  } else {
    Serial.print("Error sending data to ThingSpeak. HTTP error code: ");
    Serial.println(responseCode);
  }

  delay(20000);  // Wait 20 seconds before repeating the loop
}
