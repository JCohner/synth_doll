#include "mqtt.h"
#include "secrets.h"

#include <memory> 

void MQTT::init(){
  Serial.print("got here\n");
  Serial.flush();
  mqttClient_ = std::make_unique<MqttClient>(wifiClient_);
  Serial.print("did not get here\n");
  Serial.flush();

  char ssid[] = SECRET_SSID;
  char pass[] = SECRET_PASS;
  const char broker[] = "10.0.0.130";  //10.0.0.216
  const int port     = 1883;

  Serial.print("Attempting to connect to WPA SSID: ");
  Serial.println(ssid);
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("You're connected to the network\n");
  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);
  if (!mqttClient_->connect(broker, port)) {

    Serial.print("MQTT connection failed! Error code = ");

    Serial.println(mqttClient_->connectError());

    while (1);

  }


  Serial.println("You're connected to the MQTT broker!");

  Serial.println();
}