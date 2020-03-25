#ifndef INCLUDE
#define INCLUDE

#include <cmath>

class Vector {
public:
    double x;
    double y;
    double z;

    Vector() : 
        x(0), y(0), z(0) {}
    Vector(const double &x, const double &y, const double &z) :
        x(x), y(y), z(z) {}
    Vector(const Vector &other) :
        x(other.x), y(other.y), z(other.z) {}
    ~Vector() {}

    double Magnitude() const {
        return std::sqrt(x*x + y*y + z*z);
    }
    Vector Normalized() const {
        double magnitude = Magnitude();
        if(magnitude == 0)
            return Vector(1, 0, 0);
        return Vector(x / magnitude, y / magnitude, z / magnitude);
    }
    long double Dot(const Vector &other) const {
        return x * other.x + y * other.y + z * other.z;
    }
    Vector Cross(const Vector &other) const {
        return Vector(y * other.z, -1 * z * other.x, x * other.y);
    }

    Vector operator+(const Vector &other) const {
        return Vector(x + other.x, y + other.y, z + other.z);
    }
    Vector& operator+=(const Vector &other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }
    Vector operator-(const Vector &other) const {
        return Vector(x - other.x, y - other.y, z - other.z);
    }
    Vector& operator-=(const Vector &other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }
    Vector operator*(const double &scalar) const {
        return Vector(scalar * x, scalar * y, scalar * z);
    }
    Vector& operator*=(const double &scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }
    bool operator==(const Vector &other) const {
        return x == other.x && y == other.y && z == other.z;
    }
};
Vector operator*(const double &scalar, const Vector &vector) {
    return Vector(scalar * vector.x, scalar * vector.y, scalar * vector.z);
}

class Disk {
public:
    double radius;
    Vector position;
    Vector velocity;

    Disk() :
        radius(1), position(Vector()), velocity(Vector()) {}
    Disk(const double &radius, const double &px, const double &py, const double &pz, const double &vx, const double &vy, const double &vz) :
        radius(radius), position(Vector(px, py, pz)), velocity(Vector(vx, vy, vz))  {}
    Disk(const double &radius, const Vector &position, const Vector &velocity) :
        radius(radius), position(Vector(position)), velocity(Vector(velocity)) {}
    Disk(const Disk &other) :
        radius(other.radius), position(Vector(position)), velocity(Vector(velocity)) {}
    ~Disk() {}

    bool Overlaps(const Disk &other) const {
        return (position - other.position).Magnitude < radius + other.radius;
    }

    bool operator==(const Disk &other) const {
        return radius == other.radius && position == other.position && velocity == other.position;
    }
};

#endif // INCLUDE