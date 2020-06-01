#include "Vector2.h"

namespace phys { namespace math {

Vector2::Vector2()
    : x(0.0f), y(0.0f)
{}

Vector2::Vector2(float x, float y)
    : x(0.0f), y(0.0f)
{
    set(x, y);
}

void Vector2::set(float x, float y)
{
    this->x = x;
    this->y = y;
}

Vector2 Vector2::unit() const
{
    float len = length();

    if (len <= 0.0f)
        return Vector2(0.0f, 0.0f);

    return Vector2(x / len, y / len);
}

float Vector2::lengthSquared() const
{
    return x * x + y * y;
}

float Vector2::length() const
{
    return sqrt(lengthSquared());
}

float Vector2::distanceSquared(const Vector2 &other) const
{
    return (x - other.x) * (x - other.x) + (y - other.y) * (y - other.y);
}

float Vector2::distance(const Vector2 &other) const
{
    return sqrt(distanceSquared(other));
}

Vector2 Vector2::operator+() const
{
    return Vector2(+x, +y);
}

Vector2 Vector2::operator-() const
{
    return Vector2(-x, -y);
}

Vector2 Vector2::operator+(const Vector2 &other) const
{
    return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator-(const Vector2 &other) const
{
    return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::operator*(float other) const
{
    return Vector2(x * other, y * other);
}

Vector2 Vector2::operator/(float other) const
{
    return Vector2(x / other, y / other);
}

float Vector2::operator*(const Vector2 &other) const
{
    return x * other.x + y * other.y;
}

float Vector2::operator%(const Vector2 &other) const
{
    return x * other.y - y * other.x;
}

}};
