#ifndef __SCENE_SCENE_H__
#define __SCENE_SCENE_H__

#include <list>
#include "Entity.h"


	class Scene {
	public:
		Scene();
		~Scene();
		virtual void Update() = 0;
		void AddEntity(Entity* entity);

	private:
		std::list<Entity*> entities;
	};


#endif
