#include "RayTracerMath.h"
#include <iostream>

int main() {
   /*
   // Test Vector3
   Vector3 p1(1.0, 2.0, 3.0);
   std::cout << p1.magnitude() << std::endl;
   Vector3 p2 = p1 / 3.0;
   std::cout << p2.x << ", " << p2.y << ", " << p2.z << std::endl;
   Vector3 p3 = p1 + p2;
   std::cout << p3.x << ", " << p3.y << ", " << p3.z << std::endl;
   Vector3 p4(3.0, 2.0, 1.0);
   Vector3 p5 = Vector3::cross(p1, p4);
   std::cout << p5.x << ", " << p5.y << ", " << p5.z << std::endl;
   Vector3 p6 = p4.normalized();
   std::cout << p6.x << ", " << p6.y << ", " << p6.z << std::endl;

   // Test Ray
   std::cout << std::endl << "Ray" << std::endl;
   Vector3 o(0.0, 0.0, 0.0);
   Vector3 dir(1.0, 0.0, 0.0);
   Ray ray(o, dir);
   Vector3 paramVal = ray.val(1);
   std::cout << paramVal.x << ", " << paramVal.y << ", " << paramVal.z << std::endl;

   // Test Camera
   std::cout << std::endl << "Camera" << std::endl;
   Vector3 viewDir(0.0, 0.0, 5.0), up(0.0, 4.0, 0.0), viewPoint = o;
   float t = 10.0, b = -10.0, l = -10.0, r = 10.0;
   int nx = 3, ny = 3;
   OrthographicCamera cam(o, up, viewDir, t, b, l, r, nx, ny);
   for (int i = 0; i < nx; i++) {
      for (int j = 0; j < ny; j++) {
         Ray ijR = cam.viewRay(i, j);
         Vector3 ijDir = ijR.dir;
         Vector3 ijOrigin = ijR.origin;
         std::cout << "Direction: (" << ijDir.x << ", " << ijDir.y << ", " << ijDir.z << ")" << std::endl;
         std::cout << "Origin: (" << ijOrigin.x << ", " << ijOrigin.y << ", " << ijOrigin.z << ")" << std::endl << std::endl;
      }
   }
   */
   Color color1(0, 255, 0);
   Material material1(color1, 1.0, 3.0, 1.0);
   Vector3 ta(10.0, 0.0, 0.0), tb(0.0, 10.0, 0.0), tc(-10.0, 0.0, 0.0);
   Triangle triangle1(ta, tb, tc, material1);
   Vector3 origin(0.0, 5.0, 5.0);
   Vector3 dir(0.0, 0.0, -1.0);
   Ray r(origin, dir);
   HitRecord rec;
   std::cout << triangle1.hit(r, 0.0001, 1000000.0, rec) << std::endl;
}