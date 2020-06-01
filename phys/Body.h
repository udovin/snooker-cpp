#pragma once

#include "World.h"
#include "math/Vector2.h"
#include "shapes/Shape.h"

namespace phys {

/**
 * [[ Dependency ]]
 */
class World;

/**
 * [[ Declaration ]]
 */
struct BodyDef;

class Body
{
    friend class World;

public:
    enum Type
    {
        STATIC  = 0,
        DYNAMIC = 1
    };

private:
    Type type;

    World *world;

    math::Vector2 position;
    float angle;

    math::Vector2 linearVelocity;
    float angularVelocity;

    float mass;

    float restitution;

    float linearDamping;
    float angularDamping;

    shapes::Shape *shape;

    Body(const BodyDef &, World *);

    ~Body();

public:
    World *getWorld();

    const math::Vector2 &getPosition() const;
    void setPosition(const math::Vector2 &);

    const float &getAngle() const;
    void setAngle(const float &);

    const math::Vector2 &getLinearVelocity() const;
    void setLinearVelocity(const math::Vector2 &);

    const float &getAngularVelocity() const;
    void setAngularVelocity(const float &);

    const float &getMass() const;

    const float &getRestitution() const;

	const float &getLinearDamping() const;
	const float &getAngularDamping() const;

    const shapes::Shape *getShape() const;
};

struct BodyDef
{
    Body::Type type;

    math::Vector2 position;
    float angle;

    math::Vector2 linearVelocity;
    float angularVelocity;

    float mass;

    float restitution;

    float linearDamping;
    float angularDamping;

    shapes::Shape *shape;

    BodyDef();
};

};
