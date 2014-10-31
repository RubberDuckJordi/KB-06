#ifndef _PENGINE_SCENEFACTORY_H_
#define _PENGINE_SCENEFACTORY_H_

#include "ResourceManager.h"
#include "Scene.h"
#include <map>

/*
Interface for SceneFactories. One must be implemented for every Scene implementation
*/

namespace pengine
{
	class SceneFactory 
	{
	public:
		SceneFactory();
		~SceneFactory();
		virtual Scene* CreateScene(std::vector<std::string>* sceneFile, pengine::ResourceManager* resourceManager) = 0;
	};
}
#endif