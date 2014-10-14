#ifndef _PENGINE_SCENELOADER_H_
#define _PENGINE_SCENELOADER_H_

#include "Scene.h"
#include "SceneDefinition.h"

#include <vector>

namespace pengine
{
	class SceneLoader
	{
	public:
		SceneLoader();
		~SceneLoader();

		std::vector<std::string>* LoadFile(std::string* filePath);
	};
}
#endif