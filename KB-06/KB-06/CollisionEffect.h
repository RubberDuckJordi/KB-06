#ifndef _COLLISIONEFFECT_H_
#define _COLLISIONEFFECT_H_

#include "Collidable.h"
#include "Vector3.h"
#include <string>

namespace pengine
{
	class Collidable;
	// Struct to keep track of changes in force that must be done after collision detection has been executed
	struct COLLISIONEFFECT
	{
		Collidable* collidable1;
		Collidable* collidable2;

		// Properties of collidable1
		// They will change in collidable1 due to changes by the second collidables forces
		// so we keep them here to make sure we can reference the old valuess

		float forceVectorX;
		float forceVectorY;
		float forceVectorZ;

		float mass;

		// true if it does not move
		bool isStatic;

		std::string type;
	};
}

#endif