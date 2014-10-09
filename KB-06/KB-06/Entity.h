#ifndef _PENGINE_ENTITY_H_
#define _PENGINE_ENTITY_H_

#include "Renderer.h"
#include "Vertex.h"
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

		void SetPosition(float x, float y, float z);
		void SetRotation(float yaw, float pitch, float roll);
		void SetScale(float scaleX, float scaleY, float scaleZ);
		void SetAll(float x, float y, float z, float yaw, float pitch, float roll, float scaleX, float scaleY, float scaleZ);

		Vertex* GetPosition();
		Vertex* GetRotation();
		Vertex* GetScale();

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

	protected:
		void ApplyFriction(float friction);

		RenderMatrix* myCachedMatrix;
		Vertex position;
		Vertex rotation;
		Vertex scale;

		float mass;
		float friction;
		Vector3 movementVector;

		Logger* logger;
	};
}
#endif
