#include <math.h>
#include "RayTracerMath.h"

/////////////
// Vector3 //
/////////////
Vector3::Vector3() {
   x = 0.0;
   y = 0.0;
   z = 0.0;
}

Vector3::Vector3(float xIn, float yIn, float zIn) {
   x = xIn;
   y = yIn;
   z = zIn;
}

float Vector3::magnitude() {
   return pow(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0), 0.5);
}

Vector3 Vector3::operator+(const Vector3& v) const {
   Vector3 result;
   result.x = this->x + v.x;
   result.y = this->y + v.y;
   result.z = this->z + v.z;
   return result;
}

Vector3 Vector3::operator-(const Vector3& v) const {
   Vector3 result;
   result.x = this->x - v.x;
   result.y = this->y - v.y;
   result.z = this->z - v.z;
   return result;
}

Vector3 Vector3::operator*(const float c) const {
   Vector3 result;
   result.x = c * this->x;
   result.y = c * this->y;
   result.z = c * this->z;
   return result;
}

Vector3 Vector3::operator/(const float c) const {
   Vector3 result;
   result.x = this->x / c;
   result.y = this->y / c;
   result.z = this->z / c;
   return result;
}

/////////
// Ray //
/////////
Ray::Ray(Vector3 originIn, Vector3 dirIn) {
   origin = originIn;
   dir = dirIn;
}

Vector3 Ray::parametricVal(float t) {
   float x = origin.x + dir.x * t;
   float y = origin.y + dir.y * t;
   float z = origin.z + dir.z * t;
   return Vector3(x, y, z);
}

////////////
// Camera //
////////////
Camera::Camera(Vector3 viewPoint, Vector3 up, Vector3 viewDir, 
   float tIn, float bIn, float lIn, float rIn, int nxIn, int nyIn) {
   w = viewDir * -1.0f;
   e = viewPoint;
   v = up;
   t = tIn;
   b = bIn;
   l = lIn;
   r = rIn;
   nx = nxIn;
   ny = nyIn;
}

/////////////////////////
// Orthographic Camera //
/////////////////////////
Ray OrthographicCamera::viewRay(int xi, int yi) {
   Vector3 origin = e + pixelToPos(xi, yi);
   Vector3 dir = w * -1.0;
   return Ray(origin, dir);
}

Vector3 OrthographicCamera::pixelToPos(int xi, int yi) {
   float ucoord = l + (r - l) * (xi + 0.5) / nx;
   float vcoord = b + (t - b) * (yi + 0.5) / ny;
   return u * ucoord + v * vcoord;
}

