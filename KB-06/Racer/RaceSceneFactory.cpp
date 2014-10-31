#include "RaceSceneFactory.h"
#include "RaceScene.h"
#include "RaceCart.h"
#include "track.h"
#include "trackblock.h"
#include "Ground.h"
#include "Material.h"

#include "TinyEntity.h"

racer::RaceSceneFactory::RaceSceneFactory()
{

}

racer::RaceSceneFactory::~RaceSceneFactory()
{
	pengine::SceneFactory::~SceneFactory();
}

pengine::Scene* racer::RaceSceneFactory::CreateScene(std::vector<std::string>* sceneFile, pengine::ResourceManager* resourceManager)
{
	RaceScene* scene = new RaceScene();
	std::vector<RaceCart*> raceCarts;
	std::vector<TrackBlock*> trackBlocks;
	float height = NULL;

	Track* track = NULL;

	std::string beginLine;

	int i;
	int j;
	int k;

	for (i = 0; i < sceneFile->size(); ++i)
	{
		beginLine = sceneFile->at(i);

		if (!beginLine.compare("<Entity>"))
		{
			std::string endLine;
			for (j = i; j < sceneFile->size(); ++j)
			{
				endLine = sceneFile->at(j);

				if (!endLine.compare("</Entity>"))
				{
					std::size_t startPosition;
					std::size_t endPosition;

					std::string type;
					std::string objectPath;
					bool controllable;
					float horsePower;
					float mass;
					float translationX;
					float translationY;
					float translationZ;
					float positionX;
					float positionY;
					float positionZ;
					float scalingX;
					float scalingY;
					float scalingZ;

					for (k = i + 1; k < j; ++k)
					{


						startPosition = sceneFile->at(k).find("<Type>");
						endPosition = sceneFile->at(k).find("</Type>");
						if (startPosition != std::string::npos || endPosition != std::string::npos)
						{
							startPosition = startPosition + 6;
							type = sceneFile->at(k).substr(startPosition, endPosition - startPosition);
						}
						startPosition = sceneFile->at(k).find("<Controllable>");
						endPosition = sceneFile->at(k).find("</Controllable>");
						if (startPosition != std::string::npos || endPosition != std::string::npos)
						{
							startPosition = startPosition + 14;
							if (sceneFile->at(k).substr(startPosition, endPosition - startPosition).compare("TRUE") == 0)
							{
								controllable = true;
							}
							else
							{
								controllable = false;
							}
						}
						startPosition = sceneFile->at(k).find("<ObjectPath>");
						endPosition = sceneFile->at(k).find("</ObjectPath>");
						if (startPosition != std::string::npos || endPosition != std::string::npos)
						{
							startPosition = startPosition + 12;
							objectPath = sceneFile->at(k).substr(startPosition, endPosition - startPosition);
						}
						startPosition = sceneFile->at(k).find("<Mass>");
						endPosition = sceneFile->at(k).find("</Mass>");
						if (startPosition != std::string::npos || endPosition != std::string::npos)
						{
							startPosition = startPosition + 6;
							mass = (float)atof(sceneFile->at(k).substr(startPosition, endPosition - startPosition).c_str());
						}
						startPosition = sceneFile->at(k).find("<HorsePower>");
						endPosition = sceneFile->at(k).find("</HorsePower>");
						if (startPosition != std::string::npos || endPosition != std::string::npos)
						{
							startPosition = startPosition + 12;
							horsePower = (float)atof(sceneFile->at(k).substr(startPosition, endPosition - startPosition).c_str());
						}
						startPosition = sceneFile->at(k).find("<TranslationX>");
						endPosition = sceneFile->at(k).find("</TranslationX>");
						if (startPosition != std::string::npos || endPosition != std::string::npos)
						{
							startPosition = startPosition + 14;
							translationX = (float)atof(sceneFile->at(k).substr(startPosition, endPosition - startPosition).c_str());
						}
						startPosition = sceneFile->at(k).find("<TranslationY>");
						endPosition = sceneFile->at(k).find("</TranslationY>");
						if (startPosition != std::string::npos || endPosition != std::string::npos)
						{
							startPosition = startPosition + 14;
							translationY = (float)atof(sceneFile->at(k).substr(startPosition, endPosition - startPosition).c_str());
						}
						startPosition = sceneFile->at(k).find("<TranslationZ>");
						endPosition = sceneFile->at(k).find("</TranslationZ>");
						if (startPosition != std::string::npos || endPosition != std::string::npos)
						{
							startPosition = startPosition + 14;
							translationZ = (float)atof(sceneFile->at(k).substr(startPosition, endPosition - startPosition).c_str());
						}
						startPosition = sceneFile->at(k).find("<PositionX>");
						endPosition = sceneFile->at(k).find("</PositionX>");
						if (startPosition != std::string::npos || endPosition != std::string::npos)
						{
							startPosition = startPosition + 11;
							positionX = (float)atof(sceneFile->at(k).substr(startPosition, endPosition - startPosition).c_str());
						}
						startPosition = sceneFile->at(k).find("<PositionY>");
						endPosition = sceneFile->at(k).find("</PositionY>");
						if (startPosition != std::string::npos || endPosition != std::string::npos)
						{
							startPosition = startPosition + 11;
							positionY = (float)atof(sceneFile->at(k).substr(startPosition, endPosition - startPosition).c_str());
						}
						startPosition = sceneFile->at(k).find("<PositionZ>");
						endPosition = sceneFile->at(k).find("</PositionZ>");
						if (startPosition != std::string::npos || endPosition != std::string::npos)
						{
							startPosition = startPosition + 11;
							positionZ = (float)atof(sceneFile->at(k).substr(startPosition, endPosition - startPosition).c_str());
						}
						startPosition = sceneFile->at(k).find("<ScalingX>");
						endPosition = sceneFile->at(k).find("</ScalingX>");
						if (startPosition != std::string::npos || endPosition != std::string::npos)
						{
							startPosition = startPosition + 10;
							scalingX = (float)atof(sceneFile->at(k).substr(startPosition, endPosition - startPosition).c_str());
						}
						startPosition = sceneFile->at(k).find("<ScalingY>");
						endPosition = sceneFile->at(k).find("</ScalingY>");
						if (startPosition != std::string::npos || endPosition != std::string::npos)
						{
							startPosition = startPosition + 10;
							scalingY = (float)atof(sceneFile->at(k).substr(startPosition, endPosition - startPosition).c_str());
						}
						startPosition = sceneFile->at(k).find("<ScalingZ>");
						endPosition = sceneFile->at(k).find("</ScalingZ>");
						if (startPosition != std::string::npos || endPosition != std::string::npos)
						{
							startPosition = startPosition + 10;
							scalingZ = (float)atof(sceneFile->at(k).substr(startPosition, endPosition - startPosition).c_str());
						}

					}

					if (type.compare("RaceKart") == 0)
					{
						RaceCart* raceCart = new RaceCart();
						raceCart->SetControllable(controllable);
						raceCart->SetMass(mass);
						raceCart->SetHorsePower(horsePower);
						raceCart->AddAll(positionX, positionY, positionZ, translationX, translationY, translationZ, scalingX, scalingY, scalingZ);
						raceCart->SetObject3D(resourceManager->LoadXFile(&objectPath));

						scene->AddEntity(raceCart);
						scene->AddCollidable(raceCart);
						if (controllable == true)
						{
							scene->SetRaceCart(raceCart);
						}
						raceCarts.push_back(raceCart);
					}
				}
			}
			i = k;
		}
		else if (!beginLine.compare("<Skybox>"))
		{
			std::string endLine;

			for (j = i; j < sceneFile->size(); ++j)
			{
				endLine = sceneFile->at(j);

				if (!endLine.compare("</Skybox>"))
				{
					std::string skyboxPath;

					for (k = i; k < j; ++k)
					{
						std::size_t startPosition;
						std::size_t endPosition;

						startPosition = sceneFile->at(k).find("<Material>");
						endPosition = sceneFile->at(k).find("</Material>");

						std::size_t npos = std::string::npos;

						if (startPosition != std::string::npos || endPosition != std::string::npos)
						{
							startPosition = startPosition + 10;
							skyboxPath = sceneFile->at(k).substr(startPosition, endPosition - startPosition);
						}

					}

					if (skyboxPath.compare(""))
					{
						pengine::Skybox* skybox = new pengine::Skybox();
						pengine::Material* material = new pengine::Material();
						material->texture = resourceManager->LoadBinaryFile(skyboxPath);

						skybox->SetMaterial(material);
						scene->SetSkybox(skybox);
					}
				}


			}
			i = k;
		}
		else if (!beginLine.compare("<Ground>"))
		{
			std::string endLine;

			for (j = i; j < sceneFile->size(); ++j)
			{
				endLine = sceneFile->at(j);

				if (!endLine.compare("</Ground>"))
				{
					std::string groundHeightmapPath;
					std::string groundMaterialPath;

					for (k = i + 1; k < j; ++k)
					{
						std::size_t startPosition;
						std::size_t endPosition;

						startPosition = sceneFile->at(k).find("<Heightmap>");
						endPosition = sceneFile->at(k).find("</Heightmap>");

						if (startPosition != std::string::npos || endPosition != std::string::npos)
						{
							startPosition = startPosition + 11;
							groundHeightmapPath = sceneFile->at(k).substr(startPosition, endPosition - startPosition);
						}

						startPosition = sceneFile->at(k).find("<Material>");
						endPosition = sceneFile->at(k).find("</Material>");
						if (startPosition != std::string::npos || endPosition != std::string::npos)
						{
							startPosition = startPosition + 10;
							groundMaterialPath = sceneFile->at(k).substr(startPosition, endPosition - startPosition);
						}
					}

					if (groundHeightmapPath.compare("") && groundMaterialPath.compare(""))
					{
						pengine::Ground* ground = resourceManager->LoadGround(groundHeightmapPath, groundMaterialPath, 3);
						ground->InitQuadTree(2);
						scene->SetGround(ground);
					}
				}


			}
			i = k;
		}
		else if (!beginLine.compare("<TrackBlock>"))
		{
			std::string endLine;
			for (j = i; j < sceneFile->size(); ++j)
			{
				endLine = sceneFile->at(j);
				if (!endLine.compare("</TrackBlock>"))
				{
					std::string trackBlockType;
					std::string trackBlockModel;
					for (k = i + 1; k < j; ++k)
					{
						std::size_t startPosition;
						std::size_t endPosition;
						startPosition = sceneFile->at(k).find("<Type>");
						endPosition = sceneFile->at(k).find("</Type>");
						if (startPosition != std::string::npos || endPosition != std::string::npos)
						{
							startPosition = startPosition + 6;
							trackBlockType = sceneFile->at(k).substr(startPosition, endPosition - startPosition);
						}
						startPosition = sceneFile->at(k).find("<Model>");
						endPosition = sceneFile->at(k).find("</Model>");
						if (startPosition != std::string::npos || endPosition != std::string::npos)
						{
							startPosition = startPosition + 7;
							trackBlockModel = sceneFile->at(k).substr(startPosition, endPosition - startPosition);
						}
					}
					if (trackBlockType.compare("") && trackBlockModel.compare(""))
					{
						if (track == NULL)
						{
							track = new Track();
						}
						

						if (!trackBlockType.compare("STRAIGHT"))
						{
							trackBlocks.push_back(track->AddTrackBlock(TrackBlock::TYPE::STRAIGHT, resourceManager->LoadXFile(&trackBlockModel)));
						}
						else if (!trackBlockType.compare("LEFT"))
						{
							trackBlocks.push_back(track->AddTrackBlock(TrackBlock::TYPE::LEFT, resourceManager->LoadXFile(&trackBlockModel)));
						}
						else if (!trackBlockType.compare("RIGHT"))
						{
							trackBlocks.push_back(track->AddTrackBlock(TrackBlock::TYPE::RIGHT, resourceManager->LoadXFile(&trackBlockModel)));
						}

						if (height == NULL)
						{
							height = resourceManager->LoadXFile(&trackBlockModel)->GetMaxY();
						}

					}
				}
			}
			i = k;
		}
		if (!track == NULL)
		{
			scene->AddEntity(track);
		}

	}

	for (int i = 0; i < trackBlocks.size(); ++i)
	{
		for (int j = 0; j < raceCarts.size(); ++j)
		{
			raceCarts[j]->AddCheckPoint(trackBlocks[i]);
		}
		scene->AddStaticCollidable(trackBlocks[i]);
	}

	for (int i = 0; i < raceCarts.size(); ++i)
	{
		raceCarts[i]->SetLastCheckPoint(trackBlocks[0]);
		raceCarts[i]->SetTrackHeight(height);
		raceCarts[i]->AddPosition(raceCarts[i]->GetPosition()->x, height, raceCarts[i]->GetPosition()->z);
	}
	std::string* shader = resourceManager->LoadShaderFile("resources/shaders/shader.fx");
	scene->shader = shader;
	

	pengine::EntityCamera* camera = new pengine::EntityCamera();
	camera->useInput = false;
	scene->SetCurrentCamera(camera);
	scene->SetAmountOfRenderTextures(1);
	return scene;
}
