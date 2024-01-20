#include <WiFiNINA.h>
#include <ArduinoMqttClient.h> 
#include <Arduino_LSM6DS3.h>
#include "secrets.h"

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

const char broker[] = "10.0.0.130";  //10.0.0.216
int port     = 1883;
const char xtopic[]  = "x_topic";
const char ytopic[]  = "y_topic";
const char ztopic[]  = "z_topic";

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

  // attempt to connect to Wifi network:

  Serial.print("Attempting to connect to WPA SSID: ");

  Serial.println(ssid);

  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {

    // failed, retry

    Serial.print(".");

    delay(5000);

  }


  Serial.println("You're connected to the network");

  Serial.println();


  Serial.print("Attempting to connect to the MQTT broker: ");

  Serial.println(broker);


  if (!mqttClient.connect(broker, port)) {

    Serial.print("MQTT connection failed! Error code = ");

    Serial.println(mqttClient.connectError());


    while (1);

  }


  Serial.println("You're connected to the MQTT broker!");

  Serial.println();

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

  mqttClient.poll();


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

    Serial.println(xtopic);

    Serial.println(x);


    Serial.print("Sending message to topic: ");

    Serial.println(ytopic);

    Serial.println(y);


    Serial.print("Sending message to topic: ");

    Serial.println(ztopic);

    Serial.println(z);


    // send message, the Print interface can be used to set the message contents

    mqttClient.beginMessage(xtopic);

    mqttClient.print(x);

    mqttClient.endMessage();


    mqttClient.beginMessage(ytopic);

    mqttClient.print(y);

    mqttClient.endMessage();


    mqttClient.beginMessage(ztopic);

    mqttClient.print(z);

    mqttClient.endMessage();


    Serial.println();

    // reset avgs
    x_avg = 0;
    y_avg = 0;
    z_avg = 0;

  }

}
