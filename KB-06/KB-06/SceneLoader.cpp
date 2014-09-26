#include "SceneLoader.h"

pengine::SceneLoader::SceneLoader()
{

}

pengine::SceneLoader::~SceneLoader()
{

}

std::vector<std::string>* pengine::SceneLoader::LoadFile(std::string filePath)
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
					
					std::size_t startPosition;
					std::size_t endPosition;
					
					std::string title;
					std::string filePath;
					std::string picturePath;
					int difficulty;
					
					for (int k = i+1; k < j-1; ++k)
					{
						

						startPosition = scenesFile->at(k).find("<Title>");
						endPosition = scenesFile->at(k).find("</Title>");
						if (startPosition != std::string::npos || endPosition != std::string::npos)
						{
							startPosition = startPosition + 7;
							title = scenesFile->at(k).substr(startPosition, endPosition - startPosition);
						}
						startPosition = scenesFile->at(k).find("<FilePath>");
						endPosition = scenesFile->at(k).find("</FilePath>");
						if (startPosition != std::string::npos || endPosition != std::string::npos)
						{
							startPosition = startPosition + 10;
							filePath = scenesFile->at(k).substr(startPosition, endPosition - startPosition);
						}
						startPosition = scenesFile->at(k).find("<PicturePath>");
						endPosition = scenesFile->at(k).find("</PicturePath>");
						if (startPosition != std::string::npos || endPosition != std::string::npos)
						{
							startPosition = startPosition + 12;
							picturePath = scenesFile->at(k).substr(startPosition, endPosition - startPosition);
						}
						startPosition = scenesFile->at(k).find("<Difficulty>");
						endPosition = scenesFile->at(k).find("</Difficulty>");
						if (startPosition != std::string::npos || endPosition != std::string::npos)
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
	FOR THE CODE USED TO PROGRESS THE SCENELIST, SEE PREVIOUS COMMENT
	

	Scene::Scene* scene = new Scene::Scene();

	std::vector<std::string>* sceneFile = new std::vector<std::string>();

	std::string beginLine;

	for (int i = 0; i < sceneFile->size(); ++i)
	{
		beginLine = sceneFile->at(i);

		if (!beginLine.compare("<Entity>"))
		{
			std::string endLine;
			int j;
			for (j = i; j < sceneFile->size(); ++j)
			{
				endLine = sceneFile->at(j);

				if (!endLine.compare("</Entity>"))
				{
					std::size_t startPosition;
					std::size_t endPosition;

					std::string type;
					std::string objectPath;
					std::string texturePath;
					int translationX;
					int translationY;
					int translationZ;
					int positionX;
					int positionY;
					int positionZ;
					int scalingX;
					int scalingY;
					int scalingZ;

					for (int k = i + 1; k < j - 1; ++k)
					{
						

						startPosition = sceneFile->at(k).find("<Type>");
						endPosition = sceneFile->at(k).find("</Type>");
						if (startPosition != std::string::npos || endPosition != std::string::npos)
						{
							startPosition = startPosition + 6;
							type = sceneFile->at(k).substr(startPosition, endPosition - startPosition);
						}
						startPosition = sceneFile->at(k).find("<ObjectPath>");
						endPosition = sceneFile->at(k).find("</ObjectPath>");
						if (startPosition != std::string::npos || endPosition != std::string::npos)
						{
							startPosition = startPosition + 12;
							objectPath = sceneFile->at(k).substr(startPosition, endPosition - startPosition);
						}
						startPosition = sceneFile->at(k).find("<TexturePath>");
						endPosition = sceneFile->at(k).find("</TexturePath>");
						if (startPosition != std::string::npos || endPosition != std::string::npos)
						{
							startPosition = startPosition + 13;
							texturePath = sceneFile->at(k).substr(startPosition, endPosition - startPosition);
						}
						startPosition = sceneFile->at(k).find("<TranslationX>");
						endPosition = sceneFile->at(k).find("</TranslationX>");
						if (startPosition != std::string::npos || endPosition != std::string::npos)
						{
							startPosition = startPosition + 14;
							translationX = (int)atof(sceneFile->at(k).substr(startPosition, endPosition - startPosition).c_str());
						}
						startPosition = sceneFile->at(k).find("<TranslationY>");
						endPosition = sceneFile->at(k).find("</TranslationY>");
						if (startPosition != std::string::npos || endPosition != std::string::npos)
						{
							startPosition = startPosition + 14;
							translationY = (int)atof(sceneFile->at(k).substr(startPosition, endPosition - startPosition).c_str());
						}
						startPosition = sceneFile->at(k).find("<TranslationZ>");
						endPosition = sceneFile->at(k).find("</TranslationZ>");
						if (startPosition != std::string::npos || endPosition != std::string::npos)
						{
							startPosition = startPosition + 14;
							translationZ = (int)atof(sceneFile->at(k).substr(startPosition, endPosition - startPosition).c_str());
						}
						startPosition = sceneFile->at(k).find("<PositionX>");
						endPosition = sceneFile->at(k).find("</PositionX>");
						if (startPosition != std::string::npos || endPosition != std::string::npos)
						{
							startPosition = startPosition + 11;
							positionX = (int)atof(sceneFile->at(k).substr(startPosition, endPosition - startPosition).c_str());
						}
						startPosition = sceneFile->at(k).find("<PositionY>");
						endPosition = sceneFile->at(k).find("</PositionY>");
						if (startPosition != std::string::npos || endPosition != std::string::npos)
						{
							startPosition = startPosition + 11;
							positionY = (int)atof(sceneFile->at(k).substr(startPosition, endPosition - startPosition).c_str());
						}
						startPosition = sceneFile->at(k).find("<PositionZ>");
						endPosition = sceneFile->at(k).find("</PositionZ>");
						if (startPosition != std::string::npos || endPosition != std::string::npos)
						{
							startPosition = startPosition + 11;
							positionZ = (int)atof(sceneFile->at(k).substr(startPosition, endPosition - startPosition).c_str());
						}
						startPosition = sceneFile->at(k).find("<ScalingX>");
						endPosition = sceneFile->at(k).find("</ScalingX>");
						if (startPosition != std::string::npos || endPosition != std::string::npos)
						{
							startPosition = startPosition + 10;
							scalingX = (int)atof(sceneFile->at(k).substr(startPosition, endPosition - startPosition).c_str());
						}
						startPosition = sceneFile->at(k).find("<ScalingY>");
						endPosition = sceneFile->at(k).find("</ScalingY>");
						if (startPosition != std::string::npos || endPosition != std::string::npos)
						{
							startPosition = startPosition + 10;
							scalingY = (int)atof(sceneFile->at(k).substr(startPosition, endPosition - startPosition).c_str());
						}
						startPosition = sceneFile->at(k).find("<ScalingZ>");
						endPosition = sceneFile->at(k).find("</ScalingZ>");
						if (startPosition != std::string::npos || endPosition != std::string::npos)
						{
							startPosition = startPosition + 10;
							scalingZ = (int)atof(sceneFile->at(k).substr(startPosition, endPosition - startPosition).c_str());
						}

					}


				}
				
			}
			i = j;
		}
		else if (!beginLine.compare("<Skybox>"))
		{
			std::string endLine;
			int j;
			for (j = i; j < sceneFile->size(); ++j)
			{
				endLine = sceneFile->at(j);

				if (!endLine.compare("</Skybox>"))
				{
					std::string skyboxPath;

					for (int k = i + 1; k < j - 1; ++k)
					{
						std::size_t startPosition;
						std::size_t endPosition;

						startPosition = sceneFile->at(k).find("<Texture>");
						endPosition = sceneFile->at(k).find("</Texture>");
						if (startPosition != std::string::npos || endPosition != std::string::npos)
						{
							startPosition = startPosition + 9;
							skyboxPath = sceneFile->at(k).substr(startPosition, endPosition - startPosition);
						}
					}
				}


			}
			i = j;
		}

	}
	*/
}