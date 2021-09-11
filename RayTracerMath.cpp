#include <math.h>
#include "RayTracerMath.h"
#include <iostream>

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

Vector3 Vector3::normalized() {
   float mag = magnitude();
   return Vector3(x / mag, y / mag, z / mag);
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

Vector3 Vector3::cross(Vector3 v1, Vector3 v2) {
   float resX = v1.y * v2.z - v1.z * v2.y;
   float resY = v1.z * v2.x - v1.x * v2.z;
   float resZ = v1.x * v2.y - v1.y * v2.x;
   return Vector3(resX, resY, resZ);
}

float Vector3::dot(Vector3 v1, Vector3 v2) {
   return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z; 
}

/////////
// Ray //
/////////
Ray::Ray(Vector3 originIn, Vector3 dirIn) {
   origin = originIn;
   dir = dirIn;
}

Vector3 Ray::val(float t) {
   float x = origin.x + dir.x * t;
   float y = origin.y + dir.y * t;
   float z = origin.z + dir.z * t;
   return Vector3(x, y, z);
}

/////////////////////////
// Orthographic Camera //
/////////////////////////
OrthographicCamera::OrthographicCamera(Vector3 viewPoint, Vector3 up, Vector3 viewDir, 
   float tIn, float bIn, float lIn, float rIn, int nxIn, int nyIn) {
   w = viewDir * -1.0f;
   w = w.normalized();
   e = viewPoint;
   v = up;
   v = v.normalized();
   u = Vector3::cross(w, v);
   u = u.normalized();
   t = tIn;
   b = bIn;
   l = lIn;
   r = rIn;
   nx = nxIn;
   ny = nyIn;
}

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

///////////
// Color //
///////////
Color::Color() {
   red = (unsigned char) 0;
   green = (unsigned char) 0;
   blue = (unsigned char) 0;
}

Color::Color(int redIn, int greenIn, int blueIn) {
   red = (unsigned char) redIn;
   green = (unsigned char) greenIn;
   blue = (unsigned char) blueIn;
}

//////////////
// Material //
//////////////
Material::Material() {
   color = Color(0, 0, 0);
   kd = 0.0;
   ks = 0.0;
   ka = 0.0;
}

Material::Material(Color colorIn, float kdIn, float ksIn, float kaIn) {
   color = colorIn;
   kd = kdIn;
   ks = ksIn;
   ka = kaIn;
}

/////////////
// Surface //
/////////////
Surface::Surface() {
   material = Material();
}

Surface::Surface(Material materialIn) {
   material = materialIn;
}

////////////
// Sphere //
////////////
Sphere::Sphere(float radiusIn, Vector3 centerIn, Material materialIn) {
   radius = radiusIn;
   center = centerIn;
   material = materialIn;
}

bool Sphere::hit(Ray r, float t0, float tf, HitRecord& rec) {
   // using the mathematical notation from pg. 77 of Marschner and Shirley
   Vector3 d = r.dir, e = r.origin, c = center;
   float R = radius;
   float discriminant = pow(Vector3::dot(d, (e - c)), 2.0) 
      - Vector3::dot(d, d) * (Vector3::dot((e - c), (e - c)) - pow(R, 2.0));
   bool hit = false;
   if (discriminant > 0.0) {
      hit = true;
      float t = (Vector3::dot(d * -1.0, (e - c)) - discriminant) / Vector3::dot(d, d);
      rec = HitRecord(t);
   }
   return hit;
}

Vector3 Sphere::normal(Vector3 pos) {
   Vector3 normal = (pos - center) * 2.0;
   return normal.normalized();
}

////////////////
// Hit Record //
////////////////
HitRecord::HitRecord() {
   t = -1.0;
   hit = false;
}

HitRecord::HitRecord(float tIn) {
   t = tIn;
   hit = true;
}

///////////////////////
// Directional Light //
///////////////////////
DirectionalLight::DirectionalLight(float intensityIn, Vector3 dirIn) {
   intensity = intensityIn;
   dir = dirIn.normalized();
}
