#include "World.h"

namespace phys {

/**
 * [[ Implementation ]]
 */
World::World()
    : bodyList()
{}

World::~World()
{
    while (!bodyList.empty())
        destroyBody(bodyList.front());
}

Body *World::createBody(const BodyDef &bodyDef)
{
    Body *body = new Body(bodyDef, this);
    bodyList.push_back(body);
    return body;
}

void World::destroyBody(Body *body)
{
    std::list<Body *>::iterator it;

    for (it = bodyList.begin(); it != bodyList.end(); it++)
    {
        if ((*it) == body)
        {
            bodyList.erase(it);
            delete body;
            break;
        }
    }
}

std::list<Body *> &World::getBodyList()
{
    return bodyList;
}

/* [ begin temporary ] */
static float combineFriction(float friction1, float friction2)
{
    return sqrt(friction1 * friction2);
}

static float combineRestitution(float restitution1, float restitution2)
{
    return restitution1 < restitution2 ? restitution2 : restitution1;
}
/* [ end temporary ] */

void World::step(float timeStep, unsigned iterations)
{
    float dt = timeStep / iterations;

    while (iterations-- > 0)
    {
        std::list<Body *>::iterator it, jt;

        // Broad phase
        for (it = bodyList.begin(); it != bodyList.end(); ++it)
        {
            for (++(jt = it); jt != bodyList.end(); ++jt)
            {
                Body *bodyA = (*it), *bodyB = (*jt);

                Contact *contact = collideShapes(
                    bodyA->shape, bodyA->position, bodyA->angle,
                    bodyB->shape, bodyB->position, bodyB->angle);

                if (contact != 0)
                {
                    math::Vector2 velocity = bodyB->linearVelocity - bodyA->linearVelocity;

                    float e = combineRestitution(bodyA->restitution, bodyB->restitution);
                    float ratioA = 0, ratioB = 0;

                    bool isDynA = bodyA->type == Body::DYNAMIC,
                         isDynB = bodyB->type == Body::DYNAMIC;

                    if (isDynA && isDynB)
                    {
                        ratioA = bodyB->mass / (bodyA->mass + bodyB->mass);
                        ratioB = bodyA->mass / (bodyA->mass + bodyB->mass);
                    }
                    else if (!isDynA && isDynB)
                        ratioB = 1;
                    else if (isDynA && !isDynB)
                        ratioA = 1;

                    float scalarImpulse = velocity * contact->normal * (1.0f + e);
                    math::Vector2 impulse = contact->normal * std::min(scalarImpulse, 0.0f);

                    bodyA->linearVelocity = bodyA->linearVelocity + impulse * ratioA;
                    bodyB->linearVelocity = bodyB->linearVelocity - impulse * ratioB;

                    delete contact;
                }
            }
        }

        // Integrate velocities and apply damping
        for (it = bodyList.begin(); it != bodyList.end(); ++it)
        {
            Body *body = (*it);

            math::Vector2 newLinearVelocity = body->linearVelocity - body->linearVelocity.unit() * body->linearDamping * dt;

            //body->linearVelocity = body->linearVelocity / (1.0f + body->linearDamping * dt);
            body->linearVelocity = (newLinearVelocity * body->linearVelocity > 0) ? newLinearVelocity : math::Vector2(0.0f, 0.0f);
            body->angularVelocity = body->angularVelocity / (1.0f + body->angularDamping * dt);
        }

        // Integrate positions
        for (it = bodyList.begin(); it != bodyList.end(); ++it)
        {
            Body *body = (*it);

            body->position = body->position + body->linearVelocity * dt;
            body->angle = body->angle + body->angularVelocity * dt;
        }
    }
}

};
