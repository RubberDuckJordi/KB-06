#ifndef _PENGINE_ENTITYCAMERA_H_
#define _PENGINE_ENTITYCAMERA_H_

#include "Entity.h"
#include "Vertex.h"
#include "Plane.h"
#include "RenderMatrix.h"

namespace pengine
{
	class EntityCamera : public Entity
	{
	public:
		EntityCamera();
		~EntityCamera();
		void UpdateLogic(float deltaTime, std::map<Input, long>* actions);
		void Draw(Renderer* renderer);
		Vertex* GetPosition();
		CameraData GetCameraData();

		/*!
		Sets the position to look at with the camera
		*/
		void SetLookAtPosition(float x, float y, float z, float rollDegrees);
		void SetLookAtEntity(Entity*);
		void SetThirdPersonEntity(Entity*, float distance, float height);
		void SetRotation(float yawDegrees, float pitchDegrees, float rollDegrees);

		bool useInput = false;

		bool SphereInFrustum(Vertex* position, float radius);
		void SetProjectionMatrix();
	protected:
		Vector3 lookAtPosition;

	private:
		void BuildViewFrustum();
		CameraData cameraData;
		PEngineMatrix* viewMatrix;
		Vector3* upVec;
		float rollDegrees = 0.0f;
		Plane frustrumPlane[6];
		PEngineMatrix projectionMatrix;
		Vector3* lastKnownRotation;
	};
}
#endif