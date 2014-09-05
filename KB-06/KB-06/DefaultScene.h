#ifndef __SCENE_DEFAULT_SCENE_H__
#define __SCENE_DEFAULT_SCENE_H__

#include "Scene.h"

namespace Scene{
	class DefaultScene : public Scene {
	public:
		DefaultScene();
		~DefaultScene();
		void Update();
	};
}

#endif