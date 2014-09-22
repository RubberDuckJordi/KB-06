#include "SceneLoader.h"


Resource::SceneLoader::SceneLoader()
{

}
Resource::SceneLoader::~SceneLoader()
{

}

std::vector<std::string>* Resource::SceneLoader::LoadFile(std::string filePath)
{
	std::ifstream file(filePath);
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

	/*
	CODE USED TO PROGRESS THE VECTOR FILLED WITH SCENES/LEVELS
	FOR THE CODE USED TO PROGRESS ONE SINGLE SCENE, SEE NEXT COMMENT

	IN IT IS BEING LOOKED FOR ALL LEVELS, INCLUDING THEIR TITLE, THEIR FILEPATHS, PICTURE PATHS (TO DISPLAY IN MENUS) AND THEIR DIFFICULTY (ALSO FOR IN MENUS)
	AT THE END A VECTOR IS BEING RETURNED WITH ALL THE LEVELS, WHICH CAN THEN BE USED FOR DISPLAY IN MENUS
	
	std::vector<Resource::SceneDefinition*>* sceneDefinitions;

	std::vector<std::string>* scenesFile = new std::vector<std::string>();

	std::string beginLine;
	
	for (int i = 0; i < scenesFile->size(); ++i)
	{
		beginLine = scenesFile->at(i);
		
		if (!beginLine.compare("<Level>"))
		{
			std::string endLine;
			int j;
			for (j = i; j < scenesFile->size(); ++j)
			{
				endLine = scenesFile->at(j);

				if (!endLine.compare("</Level>"))
				{
					Resource::SceneDefinition* scene = new SceneDefinition;
					std::string title;
					std::string filePath;
					std::string picturePath;
					int difficulty;
					
					for (int k = i+1; k < j-1; ++k)
					{
						std::size_t startPosition;
						std::size_t endPosition;

						startPosition = scenesFile->at(k).find("<Title>");
						endPosition = scenesFile->at(k).find("</Title>");
						if (startPosition != endPosition)
						{
							startPosition = startPosition + 7;
							title = scenesFile->at(k).substr(startPosition, endPosition - startPosition);
						}
						startPosition = scenesFile->at(k).find("<FilePath>");
						endPosition = scenesFile->at(k).find("</FilePath>");
						if (startPosition != endPosition)
						{
							startPosition = startPosition + 10;
							filePath = scenesFile->at(k).substr(startPosition, endPosition - startPosition);
						}
						startPosition = scenesFile->at(k).find("<PicturePath>");
						endPosition = scenesFile->at(k).find("</PicturePath>");
						if (startPosition != endPosition)
						{
							startPosition = startPosition + 12;
							picturePath = scenesFile->at(k).substr(startPosition, endPosition - startPosition);
						}
						startPosition = scenesFile->at(k).find("<Difficulty>");
						endPosition = scenesFile->at(k).find("</Difficulty>");
						if (startPosition != endPosition)
						{
							startPosition = startPosition + 12;
							difficulty = (int)atof(scenesFile->at(k).substr(startPosition, endPosition - startPosition).c_str());
						}
					}
					scene->title = title;
					scene->filePath = filePath;
					scene->picturePath = picturePath;
					scene->difficulty = difficulty;

					sceneDefinitions->push_back(scene);

				}
				
			}
			i = j;
		}

	}

	return sceneDefinitions;
	*/
	
	/*
	CODE USED TO PROGRESS THE VECTOR OF ONE SCENE/LEVEL
	FOR THE CODE USED TO PROGRESS THE SCENELIST, SEE PREVIOUST COMMENT
	
	*/

}