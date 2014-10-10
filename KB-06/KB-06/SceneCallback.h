#ifndef _PENGINE_SCENECALLBACK_H_
#define _PENGINE_SCENECALLBACK_H_

#include <string>

namespace pengine
{
	class SceneCallback {
		virtual void ChangeScene(char* identifier) = 0;
	};
}
#endif