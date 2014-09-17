#ifndef __SCENE_ENTITYCAMERA_H__
#define __SCENE_ENTITYCAMERA_H__

#include "Entity.h"

namespace Scene{
	class EntityCamera : public Entity {
	public:
		EntityCamera();
		~EntityCamera();
		void Update(std::map<Input::Input, long>* actions);
		void Draw(Renderer::Renderer* renderer, Resource::Vertex* position, Resource::Vertex* rotation);
	private:
		void Move();
	};
}

#endif
