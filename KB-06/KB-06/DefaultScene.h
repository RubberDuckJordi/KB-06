#ifndef _PENGINE_DEFAULT_SCENE_H_
#define _PENGINE_DEFAULT_SCENE_H_

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