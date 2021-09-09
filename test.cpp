#include "RayTracerMath.h"
#include <iostream>

int main() {
   // Test Vector3
   Vector3 p1(1.0, 2.0, 3.0);
   std::cout << p1.magnitude() << std::endl;
   Vector3 p2 = p1 / 3.0;
   std::cout << p2.x << ", " << p2.y << ", " << p2.z << std::endl;
   Vector3 p3 = p1 + p2;
   std::cout << p3.x << ", " << p3.y << ", " << p3.z << std::endl << std::endl;
   
   // Test Ray
   Vector3 o(0.0, 0.0, 0.0);
   Vector3 dir(1.0, 0.0, 0.0);
   Ray r(o, dir);
   Vector3 paramVal = r.parametricVal(1);
   std::cout << paramVal.x << ", " << paramVal.y << ", " << paramVal.z << std::endl;
}