#include "vec3.h"
#include <iomanip>  

Vec3 operator/(const Vec3 &lhs, const float rhs ){
  Vec3 out;
  out.x = lhs.x / rhs;
  out.y = lhs.y / rhs;
  out.z = lhs.z / rhs;
  return out;
}

Vec3& operator/=(Vec3 &lhs, float rhs){
  lhs = lhs / rhs;
  return lhs;
}

Vec3 operator+(Vec3 lhs, const Vec3 &rhs){
  Vec3 out;
  out.x = lhs.x + rhs.x;
  out.y = lhs.y + rhs.y;
  out.z = lhs.z + rhs.z;
  return out;
}

Vec3& operator+=(Vec3& lhs, const Vec3& rhs){
  lhs = lhs + rhs;
  return lhs;
}

std::ostream & operator<<(std::ostream & os, const Vec3 & vec)
{
  // TODO reflect if we are ever bandwidth constrained how to send in one MQTT message
  os << "x: " << std::setprecision(3) << vec.x << "\t" << "y: " << vec.y << "\t" << "z: " << vec.z << '\n';
  // os << "x: " << vec.x << "\t" << "y: " << vec.y << "\t" << "z: " << vec.z << "\n";
  return os;
}