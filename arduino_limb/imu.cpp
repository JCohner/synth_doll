#include <HardwareSerial.h>
#include "imu.h"

void IMUj::init(){
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
  Serial.print("Gyroscope sample rate = ");
  Serial.print(IMU.gyroscopeSampleRate());
  Serial.println(" Hz");  
  Serial.println();
  Serial.println("Gyroscope in degrees/second");
}

void IMUj::poll(){
  if (IMU.accelerationAvailable()) {
    float x,y,z;
    IMU.readAcceleration(x, y, z);
    _pose.accel += Vec3(x,y,z);
    _num_reads++;
  }
}

Vec3 IMUj::read(){
  _pose.accel /= _num_reads;
  // zero averaging counter
  _num_reads = 0;
  auto ret = _pose.accel;
  // zero averages
  _pose.accel = Vec3();
  return ret; // TODO: return full pose
}