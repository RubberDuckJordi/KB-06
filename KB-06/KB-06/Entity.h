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

		void SetMovementVector(Vector3*);
		void SetFriction(float);
		void AddFriction(float);
		void AddForce(Vector3*);
		void SetMass(float);

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

		RenderMatrix* myCachedMatrix;
		Vertex position;
		Vertex rotation;
		Vertex scale;

		Logger* logger;//Really? We keep track of a pointer to a logger in every entity? Isn't that what the singleton loggerpool is for?

		float mass = 1.0f;
		float friction = 1.0f;
		float force = 0.0f;
		Vector3 movementVector;

<<<<<<< HEAD
=======
		Logger* logger;
>>>>>>> origin/master
	};
}
#endif
