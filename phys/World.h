#pragma once

#include "Body.h"
#include "collision.h"
#include <list>

namespace phys {

/**
 * [[ Dependency ]]
 */
class Body;
struct BodyDef;

/**
 * [[ Declaration ]]
 */
class World
{
private:
	std::list<Body *> bodyList;

public:
	World();

	~World();

	Body *createBody(const BodyDef &);

	void destroyBody(Body *);

	std::list<Body *> &getBodyList();

	void step(float, unsigned);
};

};
