#ifndef __SCENE_SCENE_FACTORY_H__
#define __SCENE_SCENE_FACTORY_H__

#include "EntityFactory.h"
#include "Scene.h"
#include <map>
#include <string>

namespace Scene {
	class SceneFactory {
	public:
		SceneFactory();
		~SceneFactory();
		void AddEntityFactory(std::string name, EntityFactory* entityFactory);
		virtual Scene* CreateScene() = 0;
	protected:
		std::map<std::string, EntityFactory*> entityFactories;
	};
}

#endif