#ifndef __MQTT_H__
#define __MQTT_H__

#include <ArduinoMqttClient.h>
#include <WiFiNINA.h>

#include <memory> 
#include <map>
#include <string>

class MQTT{
  public:
    MQTT(){
    }
    std::map<char, std::string> topics = {
      {'x', "x_topic"}, 
      {'y', "y_topic"}, 
      {'z', "z_topic"}
    };

    void init();
    void poll() {mqttClient_->poll();}
    void transact_message(float val, char idx );
    void transact_message(const char* mess, char idx );

  private:
    std::unique_ptr<MqttClient> mqttClient_;
    
    WiFiClient wifiClient_;
};


#endif /* __MQTT_H__ */