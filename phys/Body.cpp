#include "World.h"

namespace phys {

/**
 * [[ Implementation ]]
 */
Body::Body(const BodyDef &def, World *world)
    : type(def.type), world(world), position(def.position)
    , angle(def.angle), linearVelocity(def.linearVelocity)
    , angularVelocity(def.angularVelocity), mass(def.mass)
    , restitution(def.restitution), linearDamping(def.linearDamping)
    , angularDamping(def.angularDamping), shape(def.shape)
{}

Body::~Body()
{
    delete shape;
}

World *Body::getWorld()
{
    return world;
}

const math::Vector2 &Body::getPosition() const
{
    return position;
}

void Body::setPosition(const math::Vector2 &position)
{
    this->position = position;
}

const float &Body::getAngle() const
{
    return angle;
}

void Body::setAngle(const float &angle)
{
    this->angle = angle;
}

const math::Vector2 &Body::getLinearVelocity() const
{
    return linearVelocity;
}

void Body::setLinearVelocity(const math::Vector2 &velocity)
{
    linearVelocity = velocity;
}

const float &Body::getAngularVelocity() const
{
    return angularVelocity;
}

void Body::setAngularVelocity(const float &velocity)
{
    angularVelocity = velocity;
}

const float &Body::getMass() const
{
    return mass;
}

const float &Body::getRestitution() const
{
    return restitution;
}

const float &Body::getLinearDamping() const
{
    return linearDamping;
}

const float &Body::getAngularDamping() const
{
    return angularDamping;
}

const shapes::Shape *Body::getShape() const
{
    return shape;
}

BodyDef::BodyDef()
    : type(Body::STATIC), position(), angle(0.0f), linearVelocity()
    , angularVelocity(0.0f), mass(0.0f), restitution(0.0f)
    , linearDamping(0.0f), angularDamping(0.0f), shape(0)
{}

};
