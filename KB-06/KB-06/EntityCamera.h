#ifndef __SCENE_ENTITYCAMERA_H__
#define __SCENE_ENTITYCAMERA_H__

#include "Entity.h"
#include "Vertex.h"

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
	private:
		CameraData cameraData;
	};
}

#endif