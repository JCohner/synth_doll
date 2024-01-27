#include "mqtt.h"
#include "secrets.h"

#include <memory> 

void MQTT::init(){
  mqttClient_ = std::make_unique<MqttClient>(wifiClient_);
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

void MQTT::transact_message(float val, char idx ){
  mqttClient_->beginMessage(topics[idx].c_str());
  mqttClient_->print(val);
  mqttClient_->endMessage();
}

void MQTT::transact_message(const char* mess, char idx ){
  mqttClient_->beginMessage(topics[idx].c_str());
  mqttClient_->print(mess);
  mqttClient_->endMessage();
}