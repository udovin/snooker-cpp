#pragma once

#include "../math/Vector2.h"

namespace phys { namespace shapes {

/**
 * [[ Declaration ]]
 */
class Shape
{
public:
	enum Type
	{
		CIRCLE  = 0,
		POLYGON = 1
	};

	virtual ~Shape();

	virtual Type getType() const = 0;

	virtual bool testPoint(const math::Vector2 &) const = 0;
};

}};
