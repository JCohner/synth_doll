#include "imu.h"
#include "mqtt.h"
#include <sstream>

//set interval for sending messages (milliseconds)
const long interval = 166;
unsigned long previousMillis = 0;
int count = 0;

MQTT mqtt;
IMUj imu;

void setup() {

  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  // TODO: remove if not compiled for debug // TODO add flag that allows for that
  while (!Serial) {;}
  imu.init();
  mqtt.init();
}

void loop() {
  // call poll() regularly to allow the library to send MQTT keep alive which
  // avoids being disconnected by the broker
  imu.poll();
  mqtt.poll();

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    auto avg_accel = imu.read();
    
    // save the last time a message was sent
    previousMillis = currentMillis;


    Serial.print("Sending message to topic: ");
    std::ostringstream ss;
    ss << avg_accel;
    auto pose_string = ss.str().c_str();
    Serial.print(pose_string);
    Serial.print('\r');
    mqtt.transact_message(avg_accel.x, 'x');
    mqtt.transact_message(avg_accel.y, 'y');
    mqtt.transact_message(avg_accel.z, 'z');
  }

}
