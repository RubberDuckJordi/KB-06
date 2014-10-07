#include "Collidable.h"

namespace pengine
{
	Collidable::RECTANGLE* Collidable::GetCollisionBox()
	{
		return &collisionBox;
	}

	bool Collidable::CheckCollision(Collidable* collidable)
	{
		RECTANGLE* other = collidable->GetCollisionBox();

		if (collisionBox.x + collisionBox.width < other->x) return false;
		if (collisionBox.x > other->x + other->width) return false;
		if (collisionBox.y + collisionBox.height <  other->y) return false;
		if (collisionBox.y > other->y + other->height) return false;
		if (collisionBox.z + collisionBox.depth <  other->z) return false;
		if (collisionBox.z > other->z + other->depth) return false;

		return true;
	}
}