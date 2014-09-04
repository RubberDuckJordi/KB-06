#ifndef __SCENE_SCENE_FACTORY_H__
#define __SCENE_SCENE_FACTORY_H__

#include "EntityFactory.h"
#include "Scene.h"
#include <map>
#include <string>

namespace Scene{
	class SceneFactory {
	public:
		void AddEntityFactory(EntityFactory* entityFactory);
		virtual Scene* CreateScene() = 0;
	private:
		std::map<std::string, EntityFactory*> entityFactories;
	};
}

#endif