#pragma once

#include "Shape.h"
#include <vector>

namespace phys { namespace shapes {

/**
 * [[ Declaration ]]
 */
class Polygon : public Shape
{
public:
	std::vector<math::Vector2> vertices;

	Polygon();
	Polygon(const std::vector<math::Vector2> &);

	virtual Type getType() const;

	virtual bool testPoint(const math::Vector2 &) const;

	void setAsBox(float, float);
};

}};
