<<<<<<< HEAD
#pragma once
class Scene
{
public:
	Scene();
	~Scene();
};

=======
#ifndef __SCENE_SCENE_H__
#define __SCENE_SCENE_H__

#include <list>
#include "Entity.h"

namespace Scene{
	class Scene {
	public:
		virtual void Update() = 0;
		void AddEntity(Entity* entity);

	private:
		std::list<Entity*> entities;
	};
}

#endif
>>>>>>> origin/master
