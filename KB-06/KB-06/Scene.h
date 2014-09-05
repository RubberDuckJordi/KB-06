#ifndef __SCENE_SCENE_H__
#define __SCENE_SCENE_H__

#include <list>
#include "Entity.h"

namespace Scene {
	class Scene {
	public:
		Scene();
		~Scene();
		virtual void Update();
		void AddEntity(Entity* entity);

	protected:
		std::list<Entity*> entities;
	};
}

#endif
