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
      OrthographicCamera(Vector3 viewPoint, Vector3 up, Vector3 viewDir, 
         float tIn, float bIn, float lIn, float rIn, int nxIn, int nyIn);
      Ray viewRay(int xi, int yi);
      

   private:
      Vector3 pixelToPos(int xi, int yi);
};

class HitRecord {
   public:
      float t;
      bool hit;

      HitRecord();
      HitRecord(float tIn);
};

class Color {
   public:
      unsigned char red;
      unsigned char green;
      unsigned char blue;

      Color();
      Color(int redIn, int greenIn, int blueIn);
};

class Material {
   public:
      Color color;
      float kd; // diffuse coefficient
      float ks; // specular coefficient
      float ka; // ambient coefficient

      Material();
      Material(Color colorIn, float kdIn, float ksIn, float kaIn);
};

class Surface {
   public:
      Material material;
      virtual bool hit(Ray r, float t0, float tf, HitRecord& rec) = 0;
      virtual Vector3 normal(Vector3 pos) = 0;

      Surface();
      Surface(Material materialIn);
};

class Sphere : public Surface {
   public:
      float radius;
      Vector3 center;

      Sphere(float radiusIn, Vector3 centerIn, Material materialIn);
      bool hit(Ray r, float t0, float tf, HitRecord& rec);
      Vector3 normal(Vector3 pos);
};

class Triangle : public Surface {
   public:
      Vector3 a;
      Vector3 b;
      Vector3 c;
      Vector3 n;

      Triangle(Vector3 aIn, Vector3 bIn, Vector3 cIn, Material materialIn);
      bool hit(Ray r, float t0, float tf, HitRecord& rec);
      Vector3 normal(Vector3 pos);
};

class DirectionalLight {
   public:
      float intensity;
      Vector3 dir;

      DirectionalLight(float intensityIn, Vector3 dirIn);
};