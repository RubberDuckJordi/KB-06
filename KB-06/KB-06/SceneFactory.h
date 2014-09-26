#ifndef __SCENE_SCENE_FACTORY_H__
#define __SCENE_SCENE_FACTORY_H__

#include "Scene.h"
#include <map>

namespace pengine
{
	class SceneFactory 
	{
	public:
		SceneFactory();
		~SceneFactory();
		virtual Scene* CreateScene() = 0;
	};
}
#endif