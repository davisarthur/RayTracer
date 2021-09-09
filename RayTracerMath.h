class Vector3 {
   public:
      float x, y, z;

      Vector3();
      Vector3(float xIn, float yIn, float zIn);

      float magnitude();

      Vector3 operator+(const Vector3&) const;
      Vector3 operator-(const Vector3&) const;
      Vector3 operator*(const float) const;
      Vector3 operator/(const float) const;
};

class Ray {
   public:
      Vector3 origin, dir;

      Ray(Vector3 originIn, Vector3 dirIn);
      Vector3 parametricVal(float t);
};

class Camera {
   public:
      Vector3 w, e, u, v;
      float t, b, l, r;
      int nx, ny;

      Camera(Vector3 viewPoint, Vector3 up, Vector3 viewDir, 
         float tIn, float bIn, float lIn, float rIn, int nxIn, int nyIn);
      virtual Ray viewRay(int nx, int ny);

   private:
      virtual Vector3 pixelToPos(int xi, int yi);
};

class OrthographicCamera : public Camera {
   public:
      Ray viewRay(int xi, int yi);

   private:
      Vector3 pixelToPos(int xi, int yi);
};