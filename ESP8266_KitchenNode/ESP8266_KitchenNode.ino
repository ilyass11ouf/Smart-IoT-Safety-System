#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

// Wi-Fi & MQTT
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
const char* mqtt_server = "YOUR_MQTT_BROKER_IP";

WiFiClient espClient;
PubSubClient client(espClient);

// Sensors
#define DHTPIN D2
#define DHTTYPE DHT11
#define MQ2PIN A0
#define GAS_THRESHOLD 3000

DHT dht(DHTPIN, DHTTYPE);
const char* kitchenTopic = "kitchen_node/data";

void setup() {
  Serial.begin(9600);
  dht.begin();
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  Serial.println("Kitchen Node Ready!");
}

void setup_wifi() {
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi connected");
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    if (client.connect("ESP8266_Kitchen")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 2s");
      delay(2000);
    }
  }
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  int gas = analogRead(MQ2PIN);

  String msg = "Temp: " + String(temp) + "C, Hum: " + String(hum) + "%, Gas: " + String(gas);
  if (gas > GAS_THRESHOLD) msg += " ⚠️ GAS LEAK DETECTED!";

  client.publish(kitchenTopic, msg.c_str());
  Serial.println(msg);
  delay(2000);
}
