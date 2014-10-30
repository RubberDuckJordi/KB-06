#include "RaceSceneFactory.h"
#include "RaceScene.h"
#include "RaceKart.h"
#include "DefaultEntity.h"
#include "track.h"
#include "trackblock.h"
#include "Ground.h"
#include "Material.h"
#include <vector>

racer::RaceSceneFactory::RaceSceneFactory(pengine::ResourceManager* resourceManager) : SceneFactory(resourceManager)
{

}

racer::RaceSceneFactory::~RaceSceneFactory()
{
	pengine::SceneFactory::~SceneFactory();
}

pengine::Scene* racer::RaceSceneFactory::CreateScene(std::vector<std::string>* sceneFile, pengine::ResourceManager* resourceManager)
{
	RaceScene* scene = new RaceScene();
	std::vector<RaceKart*> raceKarts;
	std::vector<TrackBlock*> trackBlocks;

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
						RaceKart* raceKart = new RaceKart();
						raceKart->SetControllable(controllable);
						raceKart->SetMass(mass);
						raceKart->SetHorsePower(horsePower);
						raceKart->AddAll(positionX, positionY, positionZ, translationX, translationY, translationZ, scalingX, scalingY, scalingZ);
						raceKart->SetObject3D(resourceManager->LoadXFile(&objectPath));

						scene->AddEntity(raceKart);
						scene->AddCollidable(raceKart);
						if (controllable == true)
						{
							scene->SetRaceKart(raceKart);
						}
						raceKarts.push_back(raceKart);
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
						
					}
				}
			}
			i = k;
		}
		if (!track == NULL)
		{
			track->SetAll(-15, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 3.0f, 3.0f, 3.0f);
			scene->AddEntity(track);
		}

	}

	for (int i = 0; i < trackBlocks.size(); ++i)
	{
		for (int j = 0; j < raceKarts.size(); ++j)
		{
			raceKarts[j]->AddCheckPoint(trackBlocks[i]);
		}
		scene->AddStaticCollidable(trackBlocks[i]);
	}

	pengine::EntityCamera* camera = new pengine::EntityCamera();
	camera->useInput = false;
	scene->SetCurrentCamera(camera);
	scene->SetAmountOfRenderTextures(1);
	return scene;
}

pengine::Scene* racer::RaceSceneFactory::CreateScene()
{
	pengine::Logger* logger = pengine::LoggerPool::GetInstance().GetLogger();
	RaceKart* raceKart = new RaceKart();
	raceKart->SetControllable(true);
	raceKart->SetMass(100.0f);
	raceKart->SetHorsePower(100000.0f);
	raceKart->AddAll(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);

	pengine::Object3D* tiger = resourceManager->LoadXFile(&std::string("resources/cart/cart.x"));
	raceKart->SetObject3D(tiger);

	RaceKart* raceKart1 = new RaceKart();
	raceKart1->SetMass(100.0f);
	raceKart1->AddAll(-150.0f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	raceKart1->SetObject3D(tiger);

	pengine::Object3D* trackStraight = resourceManager->LoadXFile(&std::string("resources/track/trackstraight.X"));
	pengine::Object3D* trackCurved = resourceManager->LoadXFile(&std::string("resources/track/trackcurved.X"));
	Track* track = new Track();


	TrackBlock* block00 = track->AddTrackBlock(TrackBlock::TYPE::STRAIGHT, trackStraight);
	TrackBlock* block01 = track->AddTrackBlock(TrackBlock::TYPE::STRAIGHT, trackStraight);
	TrackBlock* block02 = track->AddTrackBlock(TrackBlock::TYPE::STRAIGHT, trackStraight);
	TrackBlock* block03 = track->AddTrackBlock(TrackBlock::TYPE::LEFT, trackCurved);
	TrackBlock* block04 = track->AddTrackBlock(TrackBlock::TYPE::RIGHT, trackCurved);
	TrackBlock* block05 = track->AddTrackBlock(TrackBlock::TYPE::RIGHT, trackCurved);
	TrackBlock* block06 = track->AddTrackBlock(TrackBlock::TYPE::STRAIGHT, trackStraight);
	TrackBlock* block07 = track->AddTrackBlock(TrackBlock::TYPE::STRAIGHT, trackStraight);
	TrackBlock* block08 = track->AddTrackBlock(TrackBlock::TYPE::LEFT, trackCurved);
	TrackBlock* block09 = track->AddTrackBlock(TrackBlock::TYPE::RIGHT, trackCurved);
	TrackBlock* block10 = track->AddTrackBlock(TrackBlock::TYPE::RIGHT, trackCurved);

	TrackBlock* block11 = track->AddTrackBlock(TrackBlock::TYPE::STRAIGHT, trackStraight);
	TrackBlock* block12 = track->AddTrackBlock(TrackBlock::TYPE::STRAIGHT, trackStraight);
	TrackBlock* block13 = track->AddTrackBlock(TrackBlock::TYPE::STRAIGHT, trackStraight);
	TrackBlock* block14 = track->AddTrackBlock(TrackBlock::TYPE::LEFT, trackCurved);
	TrackBlock* block15 = track->AddTrackBlock(TrackBlock::TYPE::RIGHT, trackCurved);
	TrackBlock* block16 = track->AddTrackBlock(TrackBlock::TYPE::RIGHT, trackCurved);
	TrackBlock* block17 = track->AddTrackBlock(TrackBlock::TYPE::STRAIGHT, trackStraight);
	TrackBlock* block18 = track->AddTrackBlock(TrackBlock::TYPE::STRAIGHT, trackStraight);
	TrackBlock* block19 = track->AddTrackBlock(TrackBlock::TYPE::LEFT, trackCurved);
	TrackBlock* block20 = track->AddTrackBlock(TrackBlock::TYPE::RIGHT, trackCurved);
	TrackBlock* block21 = track->AddTrackBlock(TrackBlock::TYPE::RIGHT, trackCurved);

	pengine::Ground* ground = resourceManager->LoadGround(groundResource, groundTexture, 3);
	ground->InitQuadTree(1);
	pengine::Skybox* skybox = new pengine::Skybox();
	pengine::Material* material = new pengine::Material();
	material->texture = resourceManager->LoadBinaryFile(skyboxTexture);

	skybox->SetMaterial(material);

	RaceScene* raceScene = new RaceScene();
	raceScene->AddEntity(raceKart);
	raceScene->AddEntity(raceKart1);
	raceScene->AddCollidable(raceKart);
	raceScene->AddCollidable(raceKart1);
	raceScene->AddEntity(track);
	raceScene->SetGround(ground);
	raceScene->SetSkybox(skybox);

	raceKart->AddCheckPoint(block00);
	raceKart->AddCheckPoint(block01);
	raceKart->AddCheckPoint(block02);
	raceKart->AddCheckPoint(block03);
	raceKart->AddCheckPoint(block04);
	raceKart->AddCheckPoint(block05);
	raceKart->AddCheckPoint(block06);
	raceKart->AddCheckPoint(block07);
	raceKart->AddCheckPoint(block08);
	raceKart->AddCheckPoint(block09);
	raceKart->AddCheckPoint(block10);
	raceKart->AddCheckPoint(block11);
	raceKart->AddCheckPoint(block12);
	raceKart->AddCheckPoint(block13);
	raceKart->AddCheckPoint(block14);
	raceKart->AddCheckPoint(block15);
	raceKart->AddCheckPoint(block16);
	raceKart->AddCheckPoint(block17);
	raceKart->AddCheckPoint(block18);
	raceKart->AddCheckPoint(block19);
	raceKart->AddCheckPoint(block20);
	raceKart->AddCheckPoint(block21);
	raceKart->AddCheckPoint(block00); // Finish block

	raceKart->SetLastCheckPoint(block00);
	raceKart1->SetLastCheckPoint(block00);
	raceKart->SetTrackHeight(trackStraight->GetMaxY());
	raceKart1->SetTrackHeight(trackStraight->GetMaxY());
	raceKart->AddPosition(0.0f, trackStraight->GetMaxY(), 0.0f);
	raceKart1->AddPosition(0.0f, trackStraight->GetMaxY(), 0.0f);

	raceScene->AddStaticCollidable(block00);
	raceScene->AddStaticCollidable(block01);
	raceScene->AddStaticCollidable(block02);
	raceScene->AddStaticCollidable(block03);
	raceScene->AddStaticCollidable(block04);
	raceScene->AddStaticCollidable(block05);
	raceScene->AddStaticCollidable(block06);
	raceScene->AddStaticCollidable(block07);
	raceScene->AddStaticCollidable(block08);
	raceScene->AddStaticCollidable(block09);
	raceScene->AddStaticCollidable(block10);
	raceScene->AddStaticCollidable(block11);
	raceScene->AddStaticCollidable(block12);
	raceScene->AddStaticCollidable(block13);
	raceScene->AddStaticCollidable(block14);
	raceScene->AddStaticCollidable(block15);
	raceScene->AddStaticCollidable(block16);
	raceScene->AddStaticCollidable(block17);
	raceScene->AddStaticCollidable(block18);
	raceScene->AddStaticCollidable(block19);
	raceScene->AddStaticCollidable(block20);
	raceScene->AddStaticCollidable(block21);

	pengine::EntityCamera* camera = new pengine::EntityCamera();
	camera->useInput = false;
	raceScene->SetCurrentCamera(camera);
	raceScene->SetRaceKart(raceKart);

	raceScene->SetAmountOfRenderTextures(1);

	return raceScene;
}