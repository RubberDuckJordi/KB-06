#ifndef _COLLIDABLE_H_
#define _COLLIDABLE_H_

#include "Vector3.h"
#include "Beam.h"
#include "CollisionEffect.h"
#include "Renderer.h"

namespace pengine
{
	struct COLLISIONEFFECT;

	class Collidable
	{
	public:
		// Function called when the object collides with another collidable, must be implemented
		virtual void OnCollide(COLLISIONEFFECT*) = 0;
		// Function that initializes the collisionBox, must be implemented
		virtual void InitCollisionBox() = 0;
		// Function returns vector with current force. This can be used for a physical reaction to the impact.
		virtual Vector3* GetCollisionForceVector() = 0;
		// Function returns mass. This can be used for a physical reaction to the impact.
		virtual float GetCollisionMass() = 0;
		// Must return a collision box relative to the world matrix
		BEAM* GetCollisionBox();
		// Checks collision with another collidable, can be overridden to provide an own implementation
		virtual bool CheckCollision(Collidable*);
		// Draws the collision box for debugging
		virtual void DrawCollidable(Renderer*);

	protected:
		BEAM collisionBox;
	};
}

#endif