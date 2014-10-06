#ifndef _PENGINE_SCENEFACTORY_H_
#define _PENGINE_SCENEFACTORY_H_

#include "ResourceManager.h"
#include "Scene.h"
#include <map>

namespace pengine
{
	class SceneFactory 
	{
	public:
		SceneFactory(ResourceManager* resourceManager);
		~SceneFactory();
		virtual Scene* CreateScene() = 0;

	protected:
		ResourceManager* resourceManager;
	};
}
#endif