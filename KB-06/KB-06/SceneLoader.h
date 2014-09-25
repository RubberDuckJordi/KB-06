#ifndef _SCENELOADER_H_
#define _SCENELOADER_H_

#include "Scene.h"
#include "SceneDefinition.h"

namespace Resource
{
	class SceneLoader
	{
	public:
		SceneLoader();
		~SceneLoader();

		std::vector<std::string>* LoadFile(std::string filePath);
	};
}
#endif