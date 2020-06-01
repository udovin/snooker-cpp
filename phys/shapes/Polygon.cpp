#include "Polygon.h"

namespace phys { namespace shapes {

Polygon::Polygon()
	: vertices()
{}

Polygon::Polygon(const std::vector<math::Vector2> &vertices)
	: vertices(vertices)
{}

Shape::Type Polygon::getType() const
{
	return POLYGON;
}

bool Polygon::testPoint(const math::Vector2 &point) const
{
	math::Vector2 curr = vertices.back(), last, normal;

	for (std::size_t i = 0; i < vertices.size(); i++)
	{
		last = curr, curr = vertices[i];
		normal.set(curr.y - last.y, last.x - curr.x);

		if (normal * (point - last) > 0.0f)
			return false;
    }

	return true;
}

void Polygon::setAsBox(float halfWidth, float halfHeight)
{
	vertices.resize(4);
	vertices[0].set(-halfWidth, -halfHeight);
	vertices[1].set(+halfWidth, -halfHeight);
	vertices[2].set(+halfWidth, +halfHeight);
	vertices[3].set(-halfWidth, +halfHeight);
}

}};
