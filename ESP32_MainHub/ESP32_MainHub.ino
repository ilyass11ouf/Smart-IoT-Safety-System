#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

// WiFi
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
const char* mqtt_server = "YOUR_MQTT_BROKER_IP";

WiFiClient espClient;
PubSubClient client(espClient);

// Sensors and Buzzer
#define DHTPIN 4
#define DHTTYPE DHT11
#define WATERPIN 35
#define MQ2PIN 34
#define BUZZER 18
#define WATER_THRESHOLD 1800
#define GAS_THRESHOLD 3000

DHT dht(DHTPIN, DHTTYPE);

// MQTT topic
const char* kitchenTopic = "kitchen_node/data";

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, LOW);

  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(mqtt_callback);

  Serial.println("ESP32 Main Hub Ready!");
}

void setup_wifi() {
  Serial.print("Connecting to Wi-Fi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi connected");
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    if (client.connect("ESP32_MainHub")) {
      Serial.println("connected");
      client.subscribe(kitchenTopic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 2s");
      delay(2000);
    }
  }
}

void mqtt_callback(char* topic, byte* payload, unsigned int length) {
  String msg;
  for (unsigned int i = 0; i < length; i++) msg += (char)payload[i];
  Serial.print("📥 Kitchen Node Data: ");
  Serial.println(msg);

  if (msg.indexOf("GAS LEAK DETECTED") >= 0) {
    digitalWrite(BUZZER, HIGH);
  }
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  int water = analogRead(WATERPIN);
  int gas = analogRead(MQ2PIN);

  bool alarm = false;
  String status = "Main Hub Data | ";

  status += "Temp: " + String(temp) + "C, Hum: " + String(hum) + "%, Water: " + String(water) + ", Gas: " + String(gas);

  if (water > WATER_THRESHOLD) {
    status += " ⚠️ WATER LEAK!";
    alarm = true;
  }
  if (gas > GAS_THRESHOLD) {
    status += " ⚠️ GAS DETECTED!";
    alarm = true;
  }

  Serial.println(status);
  digitalWrite(BUZZER, alarm ? HIGH : LOW);
  delay(2000);
}
