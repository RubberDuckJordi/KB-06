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
		void AddForce(Vector3* vector);
		// Used for collisions, vector is multiplied by mass
		void AddForce(Vector3* vector, float mass);
		void SetMass(float mass);

		void AddRelativeForce(Vector3*);

		float GetFriction();
		float GetMass();
		Vector3* GetMovementVector();

		void AddPosition(float x, float y, float z);//No need for a seperate substract for all these, as you can add negative values to substract
		void AddRotation(float yaw, float pitch, float roll);
		void AddScale(float scaleX, float scaleY, float scaleZ);
		void AddAll(float x, float y, float z, float yaw, float pitch, float roll, float scaleX, float scaleY, float scaleZ);

		virtual void Draw(Renderer* renderer) = 0;
		virtual void UpdateLogic(float deltaTime, std::map<Input, long>* actions);
		
		virtual float GetRadius();
	protected:
		void ApplyFriction(float friction);

		Matrix* myCachedMatrix;
		Vector3 position;
		Vector3 rotation;
		Vector3 scale;

		float mass;
		float friction;
		Vector3 movementVector;
		float radius;
		Logger* logger;
		float defaultRadius = 1.0f;
	};
}
#endif
