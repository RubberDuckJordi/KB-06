#ifndef _PENGINE_ENTITY_H_
#define _PENGINE_ENTITY_H_

#include "Renderer.h"
#include "logger.h"
#include "Input.h"
#include "Vector3.h"

namespace pengine
{
	class Entity
	{
	public:
		Entity();
		~Entity();

		virtual void SetPosition(float x, float y, float z);
		virtual void SetRotation(float yaw, float pitch, float roll);
		void SetScale(float scaleX, float scaleY, float scaleZ);
		void SetAll(float x, float y, float z, float yaw, float pitch, float roll, float scaleX, float scaleY, float scaleZ);

		Vector3* GetPosition();
		Vector3* GetRotation();
		Vector3* GetScale();

		void SetMovementVector(Vector3* vector);
		void SetFriction(float friction);
		void AddFriction(float friction);
		// Adds a force to the current movement force vector
		void AddForce(Vector3* vector);
		// Used for collisions, vector is multiplied by mass
		void AddForce(Vector3* vector, float mass);
		void SetMass(float mass);

		// Adds a force relative to the entity's rotation
		// for example: 0.0f, 0.0f, 1.0f is forward.
		void AddRelativeForce(Vector3*);
		Vector3* GetRelativeForce();

		float GetFriction();
		float GetMass();
		Vector3* GetMovementVector();

		void AddPosition(float x, float y, float z);//No need for a seperate substract for all these, as you can add negative values to substract
		void AddRotation(float yaw, float pitch, float roll);
		void AddScale(float scaleX, float scaleY, float scaleZ);
		void AddAll(float x, float y, float z, float yaw, float pitch, float roll, float scaleX, float scaleY, float scaleZ);

		virtual void CacheToRenderer(Renderer* renderer) = 0;
		virtual void Render(Renderer* renderer) = 0;
		virtual void UpdateLogic(float deltaTime, std::map<Input, long>* actions);
		

		virtual void SetRadius(float radius);
		virtual float GetRadius();

		// Used for reverting movement when two collision boxes hit eachother. They will get stuck otherwise.
		void RevertPreviousMovementStep();

	protected:
		void ApplyFriction(float friction);

		// Used in Entity::RevertPreviousMovementStep()
		Vector3 previousPosition;
		Vector3 previousRotation;

		// used to prevent collidables from moving into eachother, movement must be disabled for one tick
		boolean collides; 

		Matrix* myCachedMatrix;
		Vector3 position;
		Vector3 rotation;
		Vector3 scale;

		float mass;
		float friction;
		Vector3 movementVector;
		Logger* logger;
		float defaultRadius;
	};
}
#endif
