#pragma once

#include <cmath>

namespace phys { namespace math {

/**
 * [[ Declaration ]]
 */
class Vector2
{
public:
	float x, y;

	Vector2();
	Vector2(float, float);

	void set(float, float);

	Vector2 unit() const;

	float lengthSquared() const;
	float length() const;

	float distanceSquared(const Vector2 &) const;
	float distance(const Vector2 &) const;

	Vector2 operator+() const;
	Vector2 operator-() const;

	Vector2 operator+(const Vector2 &) const;
	Vector2 operator-(const Vector2 &) const;

	Vector2 operator*(float) const;
	Vector2 operator/(float) const;

	// Dot product
	float operator*(const Vector2 &) const;

	// Cross product
	float operator%(const Vector2 &) const;
};

}};
