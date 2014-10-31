#ifndef _PENGINE_DEFAULT_SCENE_FACTORY_H_
#define _PENGINE_DEFAULT_SCENE_FACTORY_H_

#include "SceneFactory.h"

/*
Default scene factory for creating scenes without specific implementation
*/

namespace pengine
{
	class DefaultSceneFactory : public SceneFactory
	{
	public:
		DefaultSceneFactory(ResourceManager* resourceManager);
		~DefaultSceneFactory();
		Scene* CreateScene();
		Scene* CreateScene(std::vector<std::string>* sceneFile, pengine::ResourceManager* resourceManager);
	private:
	};
}
#endif