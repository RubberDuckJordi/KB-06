#ifndef _PENGINE_ENTITYCAMERA_H_
#define _PENGINE_ENTITYCAMERA_H_

#include "Entity.h"
#include "Vertex.h"

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

		bool useInput = false;

	protected:
		Vertex lookAtPosition;

	private:
		CameraData cameraData;
		PEngineMatrix* rotationMatrix;
		Vector3* upVec;
		float rollDegrees = 0.0f;
	};
}
#endif