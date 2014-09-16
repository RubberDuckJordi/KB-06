#ifndef __SCENE_ENTITYCAMERA_H__
#define __SCENE_ENTITYCAMERA_H__

#include "Entity.h"

namespace Scene{
	class EntityCamera : public Entity {
	public:
		EntityCamera();
		~EntityCamera();
		void Update();
	private:
		void Move();
	};
}

#endif
