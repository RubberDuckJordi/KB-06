#ifndef _PENGINE_ENTITYCAMERA_H_
#define _PENGINE_ENTITYCAMERA_H_

#include "Entity.h"
#include "Vertex.h"
#include "XModel.h"

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
		void SetLookAtPosition(float x, float y, float z, float rollDegrees);
		void SetLookAtEntity(Entity*);
		void SetThirdPersonEntity(Entity*, float distance, float height);

		//Mesh* myMesh;//debug!
		//Mesh* myMesh2;//debug!
		void SetXModel(XModel*); //debug
		bool useInput = false;

	protected:
		Vertex lookAtPosition;

	private:
		XModel* xModel; //debug
		CameraData cameraData;
		PEngineMatrix* rotationMatrix;
	};
}
#endif