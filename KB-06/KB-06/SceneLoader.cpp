#include "SceneLoader.h"

namespace pengine
{
	SceneLoader::SceneLoader()
	{

	}

	SceneLoader::~SceneLoader()
	{

	}

	std::vector<std::string>* SceneLoader::LoadFile(std::string* filePath)
	{
		std::ifstream file(*filePath);
		std::string line;
		std::vector<std::string>* scenesFile = new std::vector<std::string>();
		if (file)
		{
			while (std::getline(file, line))
			{
				scenesFile->push_back(line);
			}
		}

		return scenesFile;
	}
}