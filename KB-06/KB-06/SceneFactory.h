#ifndef _PENGINE_SCENEFACTORY_H_
#define _PENGINE_SCENEFACTORY_H_

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