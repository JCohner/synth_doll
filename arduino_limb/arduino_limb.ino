#include "imu.h"
#include "mqtt.h"
#include <sstream>

#include <fast_samd21_tc3.h>
#include <fast_samd21_tc4.h>

//set interval for sending messages (milliseconds)
const long interval = 166;
unsigned long previousMillis = 0;
int count = 0;

MQTT mqtt;
IMUj imu;

void TC3_Handler(void) {
  auto avg_accel = imu.read();
  
  Serial.print("Sending message to topic: ");
  std::ostringstream ss;
  ss << avg_accel;
  auto pose_string = ss.str().c_str();
  Serial.print(pose_string);
  Serial.print('\r');
  mqtt.transact_message(avg_accel.x, 'x');
  mqtt.transact_message(avg_accel.y, 'y');
  mqtt.transact_message(avg_accel.z, 'z');
  // mqqt.transact_message(pose_string, 'p'); // TODO: determine if this is more reliable
  TC3->COUNT16.INTFLAG.bit.MC0 = 1; // clears the interrupt
}

void TC4_Handler(void) {
  mqtt.poll();
  imu.poll();
  TC4->COUNT16.INTFLAG.bit.MC0 = 1; // clears the interrupt
}

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  // TODO: remove if not compiled for debug // TODO add flag that allows for that
  while (!Serial) {;}
  imu.init();
  mqtt.init();

  auto ret = fast_samd21_tc3_configure(100000); // starts the timer/trigger with 0.5 s
  auto ret1 = fast_samd21_tc4_configure(1000); // starts the timer/trigger with 50ms
  Serial.println(ret || ret1);
}

void loop() {
}
