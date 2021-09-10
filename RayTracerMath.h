

class Vector3 {
   public:
      float x, y, z;

      Vector3();
      Vector3(float xIn, float yIn, float zIn);

      float magnitude();
      Vector3 normalized();

      Vector3 operator+(const Vector3&) const;
      Vector3 operator-(const Vector3&) const;
      Vector3 operator*(const float) const;
      Vector3 operator/(const float) const; 

      static Vector3 cross(Vector3 v1, Vector3 v2);   
      static float dot(Vector3 v1, Vector3 v2);  
};

class Ray {
   public:
      Vector3 origin, dir;

      Ray(Vector3 originIn, Vector3 dirIn);
      Vector3 val(float t);
};

class Camera {
   public:
      Vector3 w, e, u, v;
      float t, b, l, r;
      int nx, ny;
      
      virtual Ray viewRay(int nx, int ny) = 0;

   private:
      virtual Vector3 pixelToPos(int xi, int yi) = 0;
};

class OrthographicCamera : public Camera {
   public:
      Ray viewRay(int xi, int yi);
      OrthographicCamera(Vector3 viewPoint, Vector3 up, Vector3 viewDir, 
         float tIn, float bIn, float lIn, float rIn, int nxIn, int nyIn);

   private:
      Vector3 pixelToPos(int xi, int yi);
};

class Surface {
   public:
      virtual bool hit(Ray r, float t0, float tf) = 0;
};

class Sphere : public Surface {
   public:
      float radius;
      Vector3 center;

      // t0 - minimum value of t that will be registered as a hit
      // tf - maximum value of t that wil be registered as a hit
      bool hit(Ray r, float t0, float tf);
};