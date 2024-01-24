#include <Arduino_LSM6DS3.h>
#include "mqtt.h"

//set interval for sending messages (milliseconds)
const long interval = 166;
unsigned long previousMillis = 0;
int count = 0;

// hold values for imu
float x, y, z;
int plusThreshold = 30, minusThreshold = -30;

int num_reads = 0;
float x_avg = 0; 
float y_avg = 0;
float z_avg = 0;

MQTT mqtt;

void setup() {

  //Initialize serial and wait for port to open:

  Serial.begin(9600);

  while (!Serial) {

    ; // wait for serial port to connect. Needed for native USB port only

  }

  if (!IMU.begin()) {

    Serial.println("Failed to initialize IMU!");

    while (1);

  }
  Serial.print("Gyroscope sample rate = ");
  Serial.print(IMU.gyroscopeSampleRate());
  Serial.println(" Hz");  
  Serial.println();
  Serial.println("Gyroscope in degrees/second");

  mqtt.init();
}


void loop() {
    if (IMU.accelerationAvailable()) {
      IMU.readAcceleration(x, y, z);
      x_avg += x;
      y_avg += y;
      z_avg += z;
      num_reads++;
    }
  
  // call poll() regularly to allow the library to send MQTT keep alive which

  // avoids being disconnected by the broker
  mqtt.poll();
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // average values rezero counter
    x_avg /= (float) num_reads;
    y_avg /=  (float) num_reads;
    z_avg /= (float) num_reads;
    num_reads = 0;
    // save the last time a message was sent

    previousMillis = currentMillis;


    Serial.print("Sending message to topic: ");
    Serial.print(x);
    Serial.print('\r');
    Serial.print("Sending message to topic: ");
    Serial.print(y);
    Serial.print('\r');
    Serial.print("Sending message to topic: ");
    Serial.print(z);
    Serial.print('\r');

    mqtt.transact_message(x, 'x');
    mqtt.transact_message(y, 'y');
    mqtt.transact_message(z, 'z');

    // reset avgs
    x_avg = 0;
    y_avg = 0;
    z_avg = 0;

  }

}
