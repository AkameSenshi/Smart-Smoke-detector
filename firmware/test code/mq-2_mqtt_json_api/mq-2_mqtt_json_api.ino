#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>

// const char* ssid = "ADN Guest";
// const char* password = "@dnGuest@#$";

// Replace with your network credentials
const char* ssid = "ADN Common";
const char* password = "@dnCommon@#$";

const char* mqtt_server = "dev.mqtt1.irsfswt.com";
const char* mqtt_username = "sos_irs_user1";
const char* mqtt_password = "sosirs1230";

const char* mqtt_topic = "incidentPlace/IPX0000001/fireDetector_data";

WiFiClient espClient;
PubSubClient client(espClient);

int led_pin = 27;
int gas_sensor_pin = 36;
int gas_value = 0;

unsigned long lastPollTime = 0;
unsigned long lastMsgTime = 0;
const int pollInterval = 1000;  // polls sensor every 1 seconds
const int msgInterval = 5000;   // send message every 5 seconds

// API endpoint URL
const char* api_url = "http://18.142.88.192/api/v1.0/incident-places/incidents/60b64dc8-e700-4fbc-b162-52e82b7074db/";
int threshold = 250;
bool send_api_request = false;

void setup() {
  Serial.begin(9600);
  pinMode(led_pin, OUTPUT);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("WiFi connected");

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  while (!client.connected()) {
    Serial.println("Connecting to MQTT broker...");
    if (client.connect("ESP32Client", mqtt_username, mqtt_password)) {
      Serial.println("MQTT broker connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" retrying in 5 seconds");
      delay(5000);
    }
  }
}

void loop() {

  // Poll sensor data every second
  if (millis() - lastPollTime >= pollInterval) {
    gas_value = analogRead(gas_sensor_pin) - 2000;
    Serial.print("Gas sensor value: ");
    Serial.println(gas_value);
    // Update last message time
    lastPollTime = millis();


    if (gas_value > threshold && !send_api_request) {
      Serial.println("Sending API request...");
      send_api_request = true;

      digitalWrite(led_pin, HIGH); // led_pin on

      // Make HTTP request to API endpoint
      HTTPClient http;

      http.begin(espClient, api_url);
      int http_code = http.GET();
      http.end();

      // Check the HTTP response code
      if (http_code == HTTP_CODE_OK) {
        Serial.println("API request successful");
      } else {
        Serial.print("API request failed with error code ");
        Serial.println(http_code);
      }
    }
  }

  // Check if the gas value is below the threshold and reset the flag if necessary
  if (gas_value < (threshold - 60) && send_api_request) {
    send_api_request = false;

    digitalWrite(led_pin, LOW);// led_pin low

    Serial.println("flag reset !");
  }

  // Send message every 5 seconds
  if (millis() - lastMsgTime >= msgInterval) {

    // Create a JSON object and add the gas value to it
    StaticJsonDocument<200> jsonDoc;
    jsonDoc["gas_value"] = gas_value;

    // Serialize the JSON object to a string
    String jsonString;
    serializeJson(jsonDoc, jsonString);

    Serial.println("Sending msg !");
    Serial.println(jsonString);

    // Publish the JSON string to the MQTT topic
    client.publish(mqtt_topic, jsonString.c_str());
    lastMsgTime = millis();
  }

  // Reconnect to MQTT broker if connection lost
  if (!client.connected()) {
    while (!client.connected()) {
      Serial.println("Connecting to MQTT broker...");
      if (client.connect("ESP32Client", mqtt_username, mqtt_password)) {
        Serial.println("connected");
      } else {
        Serial.print("failed with state ");
        Serial.print(client.state());
        delay(2000);
      }
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}
