#include "Circle.h"

namespace phys { namespace shapes {

Circle::Circle()
	: radius(0.0f)
{}

Circle::Circle(float radius)
	: radius(radius)
{}

Shape::Type Circle::getType() const
{
	return CIRCLE;
}

bool Circle::testPoint(const math::Vector2 &point) const
{
	return point.lengthSquared() <= radius * radius;
}

}};
