#ifndef __VEC3_H__
#define __VEC3_H__
#include <ostream>

struct Vec3 {
  float x;
  float y;
  float z;
  Vec3() : x(0), y(0), z(0) {}
  Vec3(float x, float y, float z): x(x), y(y), z(z) {}
};

Vec3 operator/(const Vec3 &lhs, const float rhs );

Vec3& operator/=(Vec3 &lhs, float rhs);

Vec3 operator+(Vec3 lhs, const Vec3 &rhs);

Vec3& operator+=(Vec3& lhs, const Vec3& rhs);

//outstream op overload for transforms2ds
std::ostream & operator<<(std::ostream & os, const Vec3 & vec);

#endif /* __VEC3_H__ */