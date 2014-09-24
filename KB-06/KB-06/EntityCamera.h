#ifndef __SCENE_ENTITYCAMERA_H__
#define __SCENE_ENTITYCAMERA_H__

#include "Entity.h"
#include "Vertex.h"
#include "Mesh.h"
#include "XModel.h"

namespace Scene
{
	class EntityCamera : public Entity 
	{
	public:
		EntityCamera();
		~EntityCamera();
		void UpdateLogic(std::map<Input::Input, long>* actions);
		void Draw(Renderer::Renderer* renderer);
		Resource::Vertex* GetPosition();
		CameraData GetCameraData();
		void SetLookAtPosition(float x, float y, float z, float rollDegrees);

		Resource::Mesh* myMesh;//debug!
		Resource::Mesh* myMesh2;//debug!
		void SetXModel(Resource::XModel*); //debug
		bool useInput = false;
	protected:
		Resource::Vertex lookAtPosition;
	private:
		Resource::XModel* xModel; //debug
		CameraData cameraData;
		PEngineMatrix* rotationMatrix;
	};
}

#endif