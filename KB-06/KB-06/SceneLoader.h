#ifndef _PENGINE_SCENELOADER_H_
#define _PENGINE_SCENELOADER_H_

#include "Scene.h"
#include "SceneDefinition.h"

#include <vector>

/*
Loader class for loading a scene file into a string vector.
Every line is one string entry in the vector.
*/

namespace pengine
{
	class SceneLoader
	{
	public:
		SceneLoader();
		~SceneLoader();

		// Returns a vector of strings. Every string represents one line in the file.
		std::vector<std::string>* LoadFile(std::string* filePath);
	};
}
#endif