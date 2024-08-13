#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "ADN Guest";
const char* password = "@dnGuest@#$";

const char* mqtt_server = "dev.mqtt1.irsfswt.com";
const char* mqtt_username = "sos_irs_user1";
const char* mqtt_password = "sosirs1230";

const char* mqtt_topic = "gas_sensor_data";

WiFiClient espClient;
PubSubClient client(espClient);

int gas_sensor_pin = 36;

void setup() {
  Serial.begin(9600);

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
  int gas_value = analogRead(gas_sensor_pin);
  Serial.print("Gas sensor value: ");
  Serial.println(gas_value);

  String payload = String(gas_value);
  client.publish(mqtt_topic, payload.c_str());

  delay(5000);
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
