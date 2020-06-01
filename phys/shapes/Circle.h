#pragma once

#include "Shape.h"

namespace phys { namespace shapes {

/**
 * [[ Declaration ]]
 */
class Circle : public Shape
{
public:
	float radius;

	Circle();
	Circle(float);

	virtual Type getType() const;

	virtual bool testPoint(const math::Vector2 &) const;
};

}};
