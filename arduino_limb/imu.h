#ifndef __IMU_H__
#define __IMU_H__

// #include <Arduino.h>
// #include <wiring_private.h>
// #include <Wire.h>
#include <Arduino_LSM6DS3.h>
#include "vec3.h"

struct Pose {
  Vec3 accel; // in g
  Vec3 gyro; // in deg/s
};

class IMUj {
  public:
    IMUj() : _num_reads(0) {}
    void init();
    void poll();
    Vec3 read();
  private:
    // LSM6DS3Class _IMU_LSM6DS3(Wire, LSM6DS3_ADDRESS);
    Pose _pose;
    float _num_reads;
};

#endif /* __IMU_H__ */