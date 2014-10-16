#include "RaceSceneFactory.h"
#include "RaceScene.h"
#include "RaceCart.h"
#include "DefaultEntity.h"
#include "track.h"
#include "trackblock.h"
#include "Ground.h"
#include "Material.h"

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

					for (int k = i + 1; k < j; ++k)
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
						RaceCart* racecart = new RaceCart();
						racecart->SetControllable(controllable);
						racecart->SetMass(mass);
						racecart->SetHorsePower(horsePower);
						racecart->AddAll(positionX, positionY, positionZ, translationX, translationY, translationZ, scalingX, scalingY, scalingZ);
						racecart->SetObject3D(resourceManager->LoadXFile(&objectPath));

 						scene->AddEntity(racecart);
						scene->AddCollidable(racecart);
						if (controllable == true)
						{
							scene->SetRaceCart(racecart);
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
		else if (!beginLine.compare("<Terrain>"))
		{

		}
		else if (!beginLine.compare("<Track>"))
		{

		}

	}

	pengine::EntityCamera* camera = new pengine::EntityCamera();
	camera->useInput = false;
	scene->SetCurrentCamera(camera);

	return scene;
}

pengine::Scene* racer::RaceSceneFactory::CreateScene()
{
	RaceCart* racecart = new RaceCart();
	racecart->SetControllable(true);
	racecart->SetMass(100.0f);
	racecart->SetHorsePower(30.0f);
	racecart->AddAll(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	racecart->SetObject3D(object3d);

	RaceCart* racecart1 = new RaceCart();
	racecart1->SetMass(100.0f);
	racecart1->AddAll(7.5f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	racecart1->SetObject3D(object3d);


	Track* track = new Track();
	track->AddTrackBlock(TrackBlock::TYPE::STRAIGHT, xModel2);
	track->AddTrackBlock(TrackBlock::TYPE::STRAIGHT, xModel2);
	track->AddTrackBlock(TrackBlock::TYPE::STRAIGHT, xModel2);
	track->AddTrackBlock(TrackBlock::TYPE::TURN_LEFT, xModel3);
	track->AddTrackBlock(TrackBlock::TYPE::TURN_RIGHT, xModel3);
	track->AddTrackBlock(TrackBlock::TYPE::TURN_RIGHT, xModel3);
	track->AddTrackBlock(TrackBlock::TYPE::STRAIGHT, xModel2);
	track->AddTrackBlock(TrackBlock::TYPE::STRAIGHT, xModel2);
	track->AddTrackBlock(TrackBlock::TYPE::TURN_RIGHT, xModel3);
	track->AddTrackBlock(TrackBlock::TYPE::STRAIGHT, xModel2);
	track->AddTrackBlock(TrackBlock::TYPE::STRAIGHT, xModel2);
	track->AddTrackBlock(TrackBlock::TYPE::STRAIGHT, xModel2);
	track->AddTrackBlock(TrackBlock::TYPE::STRAIGHT, xModel2);
	track->AddTrackBlock(TrackBlock::TYPE::TURN_RIGHT, xModel3);
	track->AddTrackBlock(TrackBlock::TYPE::STRAIGHT, xModel2);
	track->AddTrackBlock(TrackBlock::TYPE::TURN_RIGHT, xModel3);
	track->SetAll(-15, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 3.0f, 3.0f, 3.0f);

	pengine::Ground* ground = resourceManager->LoadGround(groundResource, groundTexture);
	ground->InitQuadTree(2);
	pengine::Skybox* skybox = new pengine::Skybox();
	pengine::Material* material = new pengine::Material();
	material->texture = resourceManager->LoadBinaryFile(skyboxTexture);

	skybox->SetMaterial(material);

	RaceScene* raceScene = new RaceScene();
	raceScene->AddEntity(racecart);
	raceScene->AddEntity(racecart1);
	raceScene->AddCollidable(racecart);
	raceScene->AddCollidable(racecart1);
	raceScene->AddEntity(track);
	raceScene->SetGround(ground);
	raceScene->SetSkybox(skybox);

	pengine::EntityCamera* camera = new pengine::EntityCamera();
	camera->useInput = false;
	raceScene->SetCurrentCamera(camera);
	raceScene->SetRaceCart(racecart);

	return raceScene;
}

pengine::Scene* racer::RaceSceneFactory::CreateScene(RaceScene* raceScene)
{
	/*
	RaceCart* racecart = new RaceCart();
	racecart->SetControllable(true);
	racecart->SetMass(100.0f);
	racecart->SetHorsePower(30.0f);
	racecart->AddAll(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	racecart->SetObject3D(object3d);
	*/

	RaceCart* racecart1 = new RaceCart();
	racecart1->SetMass(100.0f);
	RaceCart* racecart2 = new RaceCart();
	racecart2->SetMass(100.0f);

	racecart1->AddAll(7.5f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 3.0f, 3.0f, 3.0f);
	racecart2->AddAll(7.5f, 0.0f, -5.0f, 0.0f, 0.0f, 0.0f, 3.0f, 3.0f, 3.0f);
	racecart1->SetObject3D(object3d);
	racecart2->SetObject3D(object3d);


	Track* track = new Track();
	track->AddTrackBlock(TrackBlock::TYPE::STRAIGHT, xModel2);
	track->AddTrackBlock(TrackBlock::TYPE::STRAIGHT, xModel2);
	track->AddTrackBlock(TrackBlock::TYPE::STRAIGHT, xModel2);
	track->AddTrackBlock(TrackBlock::TYPE::TURN_LEFT, xModel3);
	track->AddTrackBlock(TrackBlock::TYPE::TURN_RIGHT, xModel3);
	track->AddTrackBlock(TrackBlock::TYPE::TURN_RIGHT, xModel3);
	track->AddTrackBlock(TrackBlock::TYPE::STRAIGHT, xModel2);
	track->AddTrackBlock(TrackBlock::TYPE::STRAIGHT, xModel2);
	track->AddTrackBlock(TrackBlock::TYPE::TURN_RIGHT, xModel3);
	track->AddTrackBlock(TrackBlock::TYPE::STRAIGHT, xModel2);
	track->AddTrackBlock(TrackBlock::TYPE::STRAIGHT, xModel2);
	track->AddTrackBlock(TrackBlock::TYPE::STRAIGHT, xModel2);
	track->AddTrackBlock(TrackBlock::TYPE::STRAIGHT, xModel2);
	track->AddTrackBlock(TrackBlock::TYPE::TURN_RIGHT, xModel3);
	track->AddTrackBlock(TrackBlock::TYPE::STRAIGHT, xModel2);
	track->AddTrackBlock(TrackBlock::TYPE::TURN_RIGHT, xModel3);
	track->SetAll(-15, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 3.0f, 3.0f, 3.0f);

	pengine::Ground* ground = resourceManager->LoadGround(groundResource, groundTexture);
	ground->InitQuadTree(1);
	pengine::Skybox* skybox = new pengine::Skybox();
	pengine::Material* material = new pengine::Material();
	material->texture = resourceManager->LoadBinaryFile(skyboxTexture);

	skybox->SetMaterial(material);

	//raceScene->AddEntity(racecart);
	raceScene->AddEntity(racecart1);
	raceScene->AddEntity(racecart2);
	//raceScene->AddCollidable(racecart);
	raceScene->AddCollidable(racecart1);
	raceScene->AddCollidable(racecart2);
	raceScene->AddEntity(track);
	raceScene->SetGround(ground);
	raceScene->SetSkybox(skybox);

	pengine::EntityCamera* camera = new pengine::EntityCamera();
	camera->useInput = false;
	raceScene->SetCurrentCamera(camera);
	//raceScene->SetRaceCart(racecart);

	return raceScene;
}

void racer::RaceSceneFactory::SetXModel2(pengine::Object3D* p_xModel)
{
	xModel2 = p_xModel;
}

void racer::RaceSceneFactory::SetXModel3(pengine::Object3D* p_xModel)
{
	xModel3 = p_xModel;
}

void racer::RaceSceneFactory::SetObject3D(pengine::Object3D* obj)
{
	object3d = obj;
}