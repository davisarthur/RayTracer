#include <math.h>
#include "RayTracer.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

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
   u = Vector3::cross(up, w);
   u = u.normalized();
   v = Vector3::cross(w, u);
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

void OrthographicCamera::changeOrientation(Vector3 viewPoint, Vector3 up, Vector3 viewDir) {
   w = (viewDir * -1.0f).normalized();
   e = viewPoint;
   u = Vector3::cross(up, w).normalized();
   v = Vector3::cross(w, u);
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
   red = (unsigned char) std::min(redIn, 255);
   green = (unsigned char) std::min(greenIn, 255);
   blue = (unsigned char) std::min(blueIn, 255);
}

Color Color::operator+(const Color& c) const {
   int red = (int) this->red + c.red;
   int green = (int) this->green + c.green;
   int blue = (int) this->blue + c.blue;
   return Color(red, green, blue);
}

Color Color::operator*(const Color& c) const {
   int red = (int) this->red * c.red;
   int green = (int) this->green * c.green;
   int blue = (int) this->blue * c.blue;
   return Color(red, green, blue);
}

Color Color::operator*(const float c) const {
   Color result;
   int red = (int) this->red * c;
   int green = (int) this->green * c;
   int blue = (int) this->blue * c;
   return Color(red, green, blue);
}

Color Color::operator/(const float c) const {
   Color result;
   int red = (int) this->red / c;
   int green = (int) this->green / c;
   int blue = (int) this->blue / c;
   return Color(red, green, blue);
}

//////////////
// Material //
//////////////
Material::Material() {
   surfaceColor = Color(0, 0, 0);
   specularColor = Color(0, 0, 0);
   ambientColor = Color(0, 0, 0);
   ambientIntensity = 1.0;
   phongExp = 100.0;
   glazed = false;
}

Material::Material(Color surfaceColorIn, Color specularColorIn, Color ambientColorIn, 
   float surfaceIntensityIn, float specularIntensityIn, float ambientIntensityIn, float phongExpIn) {
   surfaceColor = surfaceColorIn;
   specularColor = specularColorIn;
   ambientColor = ambientColorIn;
   surfaceIntensity = surfaceIntensityIn;
   specularIntensity = specularIntensityIn;
   ambientIntensity = ambientIntensityIn;
   phongExp = phongExpIn;
   glazed = false;
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
      float t = (Vector3::dot(d * -1.0, (e - c)) - discriminant) / Vector3::dot(d, d);
      if (t > t0 && t < tf) {
         hit = true;
         rec = HitRecord(t);
      }
   }
   return hit;
}

Vector3 Sphere::normal(Vector3 pos) {
   Vector3 normal = (pos - center) * 2.0;
   return normal.normalized();
}

//////////////
// Triangle //
//////////////
Triangle::Triangle(Vector3 aIn, Vector3 bIn, Vector3 cIn, Material materialIn) {
   a = aIn;
   b = bIn;
   c = cIn;
   n = Vector3::cross(b - a, c - b).normalized();
   material = materialIn;
}

bool Triangle::hit(Ray r, float t0, float tf, HitRecord& rec) {
   // make sure the ray is not parallel to the triangle's plane
   if (std::abs(Vector3::dot(r.dir, n)) < 0.000001) {
      return false;
   }
   
   // determine intersection point
   float t = Vector3::dot((a - r.origin), n) / Vector3::dot(r.dir, n);
   Vector3 x = r.val(t);
   if (t < t0 || t > tf) {
      return false;
   }

   // see if intersection point is within the triangle
   if (Vector3::dot(Vector3::cross((b - a), (x - a)), n) < 0.0) {
      return false;
   }
   if (Vector3::dot(Vector3::cross((c - b), (x - b)), n) < 0.0) {
      return false;
   }
   if (Vector3::dot(Vector3::cross((a - c), (x - c)), n) < 0.0) {
      return false;
   }
   rec = HitRecord(t);
   return true;
}

Vector3 Triangle::normal(Vector3 pos) {
   return n;
}

///////////
// Plane //
///////////
Plane::Plane(Vector3 aIn, Vector3 b, Vector3 c, Material materialIn) {
   material = materialIn;
   a = aIn;
   n = Vector3::cross(b - a, c - b).normalized();
}

bool Plane::hit(Ray r, float t0, float tf, HitRecord& rec) {
   // make sure the ray is not parallel to the triangle's plane
   if (std::abs(Vector3::dot(r.dir, n)) < 0.000001) {
      return false;
   }
   
   // determine intersection point
   float t = Vector3::dot((a - r.origin), n) / Vector3::dot(r.dir, n);
   if (t < t0 || t > tf) {
      return false;
   }

   rec = HitRecord(t);
   return true;
}

Vector3 Plane::normal(Vector3 pos) {
   return n;
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
DirectionalLight::DirectionalLight() {
   intensity = 1.0;
   dir = Vector3(0.0, 1.0, 0.0).normalized();
}

DirectionalLight::DirectionalLight(float intensityIn, Vector3 dirIn) {
   intensity = intensityIn;
   dir = dirIn.normalized();
}

///////////
// Scene // 
///////////
Scene::Scene(Camera& camIn, DirectionalLight lightSourceIn) {
   cam = &camIn;
   lightSource = lightSourceIn;
   createSurfaces();
}

Scene::Scene(Camera& camIn, DirectionalLight lightSourceIn, std::vector<Surface*> surfacesIn) {
   cam = &camIn;
   lightSource = lightSourceIn;
   surfaces = surfacesIn;
}

void Scene::createSurfaces() {
   // create materials
   float surfaceIntensity = 0.4;
   float specularIntensity = 0.25;
   float ambientIntensity = 0.1;
   float phongExp = 100.0;
   Color red(255, 0, 0), green(0, 255, 0), blue(0, 0, 255), white(255, 255, 255), black(0, 0, 0);
   Material sphere1Mat(red, white, red, surfaceIntensity, specularIntensity, ambientIntensity, phongExp);
   Material sphere2Mat(green, white, green, surfaceIntensity, specularIntensity, ambientIntensity, phongExp); 
   Material tetraMat(blue, white, blue, surfaceIntensity, specularIntensity, ambientIntensity, phongExp);
   Material planeMat(white, white, white, surfaceIntensity, specularIntensity, ambientIntensity, phongExp);
   planeMat.glazed = true;

   // create spheres
   float radius1 = 3.0, radius2 = 1.0;
   Vector3 center1(0.0, radius1, -7.0), center2(2.0, radius2, 0.0);
   Sphere* sphere1 = new Sphere(radius1, center1, sphere1Mat);
   Sphere* sphere2 = new Sphere(radius2, center2, sphere2Mat);

   // make tetrahedron
   Vector3 t1(-9.0, 0.0, -3.0), t2(-6.0, 0.0, 0.0), t3(-4.0, 0.0, -4.0), t4(-7.0, 5.0, -2.0);
   Triangle* front = new Triangle(t1, t2, t4, tetraMat);
   Triangle* bottom = new Triangle(t1, t3, t2, tetraMat);
   Triangle* left = new Triangle(t4, t3, t1, tetraMat);
   Triangle* right = new Triangle(t3, t4, t2, tetraMat);

   // make plane
   Vector3 p1(0.0, 0.0, 10.0), p2(5.0, 0.0, 10.0), p3(2.5, 0.0, -5.0);
   Plane* plane = new Plane(p1, p2, p3, planeMat);

   // add each surface to surface list
   surfaces.push_back(sphere1);
   surfaces.push_back(sphere2);
   surfaces.push_back(front);
   surfaces.push_back(bottom);
   surfaces.push_back(left);
   surfaces.push_back(right);
   surfaces.push_back(plane);
}

void Scene::render(unsigned char* image, int width, int height, float tmin, float tmax) {
   for(int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
         int idx = (i * width + j) * 3;
         Ray viewRay = cam->viewRay(j, i);
         Color idxColor = rayColor(viewRay, tmin, tmax);
         image[idx] = idxColor.red;
         image[idx+1] = idxColor.green;
         image[idx+2] = idxColor.blue;
      }
   }
}

Color Scene::rayColor(Ray r, float t0, float tf) {
   Surface *hitSurface;
   HitRecord rec;
   float t = tf;
   for (int k = 0; k < surfaces.size(); k++) {
      if (surfaces.at(k)->hit(r, t0, t, rec)) {
         hitSurface = surfaces.at(k);
         t = rec.t;
      }
   }
   if (rec.hit) {
      Vector3 normal = hitSurface->normal(r.val(t));
      Vector3 h = (r.dir * -1.0 + lightSource.dir).normalized();
      float d = hitSurface->material.surfaceIntensity * lightSource.intensity 
         * std::max(0.0f, Vector3::dot(normal, lightSource.dir));
      float s = hitSurface->material.specularIntensity * lightSource.intensity 
         * pow(std::max(0.0f, Vector3::dot(normal, h)), hitSurface->material.phongExp);
      float a = hitSurface->material.ambientIntensity;
                
      float lR = (d * hitSurface->material.surfaceColor.red + s * hitSurface->material.specularColor.red
         + a * hitSurface->material.ambientColor.red);
      float lG = (d * hitSurface->material.surfaceColor.green + s * hitSurface->material.specularColor.green
         + a * hitSurface->material.ambientColor.green);
      float lB = (d * hitSurface->material.surfaceColor.blue + s * hitSurface->material.specularColor.blue
         + a * hitSurface->material.ambientColor.blue);
      if (hitSurface->material.glazed) {
         Ray mr(r.val(t), r.dir - normal * 2 * Vector3::dot(r.dir, normal));
         return Color(lR, lG, lB) + hitSurface->material.specularColor / 255.0f 
            * rayColor(mr, t0, tf) * hitSurface->material.specularIntensity;
      }
      return Color(lR, lG, lB);
   }
   return Color(0, 0, 0);
}
