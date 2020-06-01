#include "collision.h"

namespace phys {

Contact *collideShapes(
    const shapes::Shape *sA, const math::Vector2 &pA, const double &aA,
    const shapes::Shape *sB, const math::Vector2 &pB, const double &aB)
{
    bool isCircleA = sA->getType() == shapes::Shape::CIRCLE,
         isCircleB = sB->getType() == shapes::Shape::CIRCLE;

    if (isCircleA && isCircleB)
    {
        return collideCircles(
            dynamic_cast<const shapes::Circle *>(sA), pA, aA,
            dynamic_cast<const shapes::Circle *>(sB), pB, aB);
    }

    bool isPolygonA = sA->getType() == shapes::Shape::POLYGON,
         isPolygonB = sB->getType() == shapes::Shape::POLYGON;

    if (isPolygonA && isPolygonB)
    {
        return collidePolygons(
            dynamic_cast<const shapes::Polygon *>(sA), pA, aA,
            dynamic_cast<const shapes::Polygon *>(sB), pB, aB);
    }

    if (isPolygonA && isCircleB)
    {
        return collidePolygonAndCircle(
            dynamic_cast<const shapes::Polygon *>(sA), pA, aA,
            dynamic_cast<const shapes::Circle *>(sB), pB, aB);
    }
    else if (isCircleA && isPolygonB)
    {
        return collideCircleAndPolygon(
            dynamic_cast<const shapes::Circle *>(sA), pA, aA,
            dynamic_cast<const shapes::Polygon *>(sB), pB, aB);
    }

    return 0;
}

Contact *collideCircles(
    const shapes::Circle *sA, const math::Vector2 &pA, const double &aA,
    const shapes::Circle *sB, const math::Vector2 &pB, const double &aB)
{
    math::Vector2 d = pB - pA;
    float r = sA->radius + sB->radius;

    if (d * d > r * r)
        return 0;

    Contact *contact = new Contact;

    contact->normal   = d.unit();
    contact->position = pA + contact->normal * sA->radius;

    return contact;
}

Contact *collidePolygons(
    const shapes::Polygon *sA, const math::Vector2 &pA, const double &aA,
    const shapes::Polygon *sB, const math::Vector2 &pB, const double &aB)
{
    return 0;
}

Contact *collidePolygonAndCircle(
    const shapes::Polygon *sA, const math::Vector2 &pA, const double &aA,
    const shapes::Circle *sB, const math::Vector2 &pB, const double &aB)
{
    math::Vector2 d = pB - pA;
    float sin = ::sin(aA), cos = ::cos(aA);
    float radius = sB->radius * sB->radius;
    d.set(d.x * cos - d.y * sin, d.y * cos + d.x * sin);

    math::Vector2 c = sA->vertices.back(), l, n;

	for (std::size_t i = 0; i < sA->vertices.size(); i++)
	{
		l = c, c = sA->vertices[i];
		n.set(c.y - l.y, l.x - c.x);

		float _a = d.distanceSquared(l);
		float _b = d.distanceSquared(c);
		float _c = l.distanceSquared(c);

		if (_a + _c <= _b)
        {
            if (_a > radius)
                continue;

            Contact *contact = new Contact;
            n = d - l;
            n.set(n.x * cos + n.y * sin, n.y * cos - n.x * sin);
            contact->normal = n.unit();
            contact->position = pB - contact->normal * sqrt(_a);
            return contact;
        }
        else if (_b + _c <= _a)
        {
            if (_b > radius)
                continue;

            Contact *contact = new Contact;
            n = d - c;
            n.set(n.x * cos + n.y * sin, n.y * cos - n.x * sin);
            contact->normal = n.unit();
            contact->position = pB - contact->normal * sqrt(_b);
            return contact;
        }
        else
        {
            float _d = (l.x - d.x) * (c.y - d.y) - (c.x - d.x) * (l.y - d.y);
            _d = _d * _d / _c;

            if (_d > radius)
                continue;

            Contact *contact = new Contact;
            n.set(n.x * cos + n.y * sin, n.y * cos - n.x * sin);
            contact->normal = n.unit();
            contact->position = pB - contact->normal * sqrt(_d);
            return contact;
        }
    }

    return 0;
}

Contact *collideCircleAndPolygon(
    const shapes::Circle *sA, const math::Vector2 &pA, const double &aA,
    const shapes::Polygon *sB, const math::Vector2 &pB, const double &aB)
{
    Contact *contact = collidePolygonAndCircle(sB, pB, aB, sA, pA, aA);

    if (contact != 0)
        contact->normal = -contact->normal;

    return contact;
}

};
