#include <GL/glut.h>
#include <cmath>
#include <vector>
#include <limits>

struct Vec3 
{
    float x, y, z;

    Vec3() : x(0), y(0), z(0) {}
    Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

    Vec3 operator+(const Vec3& v) const { return Vec3(x+v.x, y+v.y, z+v.z); }
    Vec3 operator-(const Vec3& v) const { return Vec3(x-v.x, y-v.y, z-v.z); }
    Vec3 operator*(float s) const { return Vec3(x*s, y*s, z*s); }
    float dot(const Vec3& v) const { return x*v.x + y*v.y + z*v.z; }
    Vec3 normalize() const 
    {
        float mag = std::sqrt(x*x + y*y + z*z);
        return Vec3(x/mag, y/mag, z/mag);
    }
};

struct Ray 
{
    Vec3 origin;
    Vec3 direction;

    Ray(const Vec3& o, const Vec3& d) : origin(o), direction(d.normalize()) {}
};

struct Sphere 
{
    Vec3 center;
    float radius;
    Vec3 color;

    Sphere(const Vec3& c, float r, const Vec3& col) : center(c), radius(r), color(col) {}
};

bool sphereIntersect(const Sphere& sphere, const Ray& ray, float& t) 
{
    Vec3 oc = ray.origin - sphere.center;
    float a = ray.direction.dot(ray.direction);
    float b = 2.0f * oc.dot(ray.direction);
    float c = oc.dot(oc) - sphere.radius*sphere.radius;
    float discriminant = b*b - 4*a*c;

    if (discriminant < 0) return false;
    
    float t0 = (-b - std::sqrt(discriminant)) / (2*a);
    float t1 = (-b + std::sqrt(discriminant)) / (2*a);
    t = (t0 < t1) ? t0 : t1;
    return true;
}

Vec3 trace(const Ray& ray, const std::vector<Sphere>& spheres) 
{
    float minDist = std::numeric_limits<float>::max();
    const Sphere* hitSphere = nullptr;
    
    for (const auto& sphere : spheres) 
    {
        float t;
        if (sphereIntersect(sphere, ray, t)) 
        {
            if (t < minDist) 
            {
                minDist = t;
                hitSphere = &sphere;
            }
        }
    }
    
    if (hitSphere) 
    {
        Vec3 hitPoint = ray.origin + ray.direction * minDist;
        Vec3 normal = (hitPoint - hitSphere->center).normalize();
        Vec3 lightDir = Vec3(1, 1, 1).normalize();
        float diffuse = std::max(0.0f, normal.dot(lightDir));
        return hitSphere->color * diffuse;
    }
    
    return Vec3(0.2f, 0.7f, 0.8f);
}

void render() 
{
    const int WIDTH = 800;
    const int HEIGHT = 600;
    float aspect = (float)WIDTH / HEIGHT;

    std::vector<Sphere> spheres = {
        Sphere(Vec3(0, -0.2, -3), 1, Vec3(1, 0.2, 0.2)),
        Sphere(Vec3(1, 0, -4), 0.5, Vec3(0.2, 1, 0.2)),
        Sphere(Vec3(-1, 0, -4), 0.5, Vec3(0.2, 0.2, 1))
    };

    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);

    for (int y = 0; y < HEIGHT; y++) 
    {
        for (int x = 0; x < WIDTH; x++) 
        {
            float dirX = (x / (float)WIDTH) * 2.0f - 1.0f;
            float dirY = ((HEIGHT - y) / (float)HEIGHT) * 2.0f - 1.0f;
            dirY /= aspect;
            
            Ray ray(Vec3(0, 0, 0), Vec3(dirX, dirY, -1));
            Vec3 color = trace(ray, spheres);
            
            glColor3f(
                std::min(color.x, 1.0f),
                std::min(color.y, 1.0f),
                std::min(color.z, 1.0f)
            );
            glVertex2i(x, y);
        }
    }

    glEnd();
    glFlush();
}

int main(int argc, char** argv) 
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("GLUT Ray Tracing");
    
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 800, 0, 600);
    
    glutDisplayFunc(render);
    glutMainLoop();
    return 0;
}