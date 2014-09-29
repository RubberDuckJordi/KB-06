#ifndef __SCENE_DEFAULT_SCENE_H__
#define __SCENE_DEFAULT_SCENE_H__

#include "Scene.h"
#include "Logger.h"

namespace pengine
{
	class DefaultScene : public Scene
	{
	public:
		DefaultScene();
		~DefaultScene();
		void Update(float deltaTime, std::map<Input, long>* actions);
	};
}
#endif