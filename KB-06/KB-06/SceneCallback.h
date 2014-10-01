#ifndef __SCENE_SCENECALLBACK_H__
#define __SCENE_SCENECALLBACK_H__
#include <string>

namespace pengine
{
	struct SceneCallback {
		virtual void ChangeScene(char* identifier) = 0;
	};
}
#endif