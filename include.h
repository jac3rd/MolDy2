#ifndef INCLUDE
#define INCLUDE

#include <cmath>

class Vector2D {
public:
    double x;
    double y;

    Vector2D() : 
        x(0), y(0) {}
    Vector2D(const double &x, const double &y) :
        x(x), y(y) {}
    Vector2D(const Vector2D &other) :
        x(other.x), y(other.y) {}
    ~Vector2D() {}

    double Magnitude() const {
        return std::sqrt(x*x + y*y);
    }
    Vector2D Normalized() const {
        double magnitude = Magnitude();
        if(magnitude == 0)
            return Vector2D(1, 0);
        return Vector2D(x / magnitude, y / magnitude);
    }
    long double Dot(const Vector2D &other) const {
        return x * other.x + y * other.y;
    }

    Vector2D operator+(const Vector2D &other) const {
        return Vector2D(x + other.x, y + other.y);
    }
    Vector2D& operator+=(const Vector2D &other) {
        x += other.x;
        y += other.y;
        return *this;
    }
    Vector2D operator-(const Vector2D &other) const {
        return Vector2D(x - other.x, y - other.y);
    }
    Vector2D& operator-=(const Vector2D &other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }
    Vector2D operator*(const double &scalar) const {
        return Vector2D(scalar * x, scalar * y);
    }
    Vector2D& operator*=(const double &scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }
    bool operator==(const Vector2D &other) const {
        return x == other.x && y == other.y;
    }
};
Vector2D operator*(const double &scalar, const Vector2D &vector) {
    return Vector2D(scalar * vector.x, scalar * vector.y);
}

class Disk {
public:
    double radius;
    Vector2D position;

    Disk() :
        radius(1), position(Vector2D()) {}
    Disk(const double &radius, const double &px, const double &py, const double &pz) :
        radius(radius), position(Vector2D(px, py)) {}
    Disk(const double &radius, const Vector2D &position) :
        radius(radius), position(Vector2D(position)) {}
    Disk(const Disk &other) :
        radius(other.radius), position(Vector2D(other.position)) {}
    ~Disk() {}

    bool Overlaps(const Disk &other) const {
      return (position - other.position).Magnitude() < radius + other.radius;
    }

    bool operator==(const Disk &other) const {
      return radius == other.radius && position == other.position;
    }
};

#endif // INCLUDE
