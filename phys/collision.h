#pragma once

#include "math/Vector2.h"
#include "shapes/all.h"
#include <vector>

namespace phys {

struct Contact
{
    math::Vector2 position;
    math::Vector2 normal;
};

Contact *collideShapes(
    const shapes::Shape *, const math::Vector2 &, const double &,
    const shapes::Shape *, const math::Vector2 &, const double &);

Contact *collideCircles(
    const shapes::Circle *, const math::Vector2 &, const double &,
    const shapes::Circle *, const math::Vector2 &, const double &);

Contact *collidePolygons(
    const shapes::Polygon *, const math::Vector2 &, const double &,
    const shapes::Polygon *, const math::Vector2 &, const double &);

Contact *collidePolygonAndCircle(
    const shapes::Polygon *, const math::Vector2 &, const double &,
    const shapes::Circle *, const math::Vector2 &, const double &);

Contact *collideCircleAndPolygon(
    const shapes::Circle *, const math::Vector2 &, const double &,
    const shapes::Polygon *, const math::Vector2 &, const double &);

};
