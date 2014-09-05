#ifndef __SCENE_DEFAULT_SCENE_FACTORY_H__
#define __SCENE_DEFAULT_SCENE_FACTORY_H__

#include "SceneFactory.h"

namespace Scene{
	class DefaultSceneFactory : public SceneFactory
	{
	public:
		DefaultSceneFactory();
		~DefaultSceneFactory();
		Scene* CreateScene();
	};
}

#endif