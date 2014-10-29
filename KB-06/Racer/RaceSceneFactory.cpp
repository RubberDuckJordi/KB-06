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
	pengine::Scene* scene = new pengine::Scene();
	std::string beginLine;

	for (unsigned int i = 0; i < sceneFile->size(); ++i)
	{
		beginLine = sceneFile->at(i);

		if (!beginLine.compare("<Entity>"))
		{
			std::string endLine;
			unsigned int j;
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

					for (unsigned int k = i + 1; k < j - 1; ++k)
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
					if (!type.empty())
					{
					}
				}
			}
			i = j;
		}
		else if (!beginLine.compare("<Skybox>"))
		{
			std::string endLine;
			unsigned int j;
			for (j = i; j < sceneFile->size(); ++j)
			{
				endLine = sceneFile->at(j);

				if (!endLine.compare("</Skybox>"))
				{
					std::string skyboxPath;

					for (unsigned int k = i + 1; k < j - 1; ++k)
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
	return NULL;
}

pengine::Scene* racer::RaceSceneFactory::CreateScene()
{
	pengine::Logger* logger = pengine::LoggerPool::GetInstance().GetLogger();
	RaceCart* racecart = new RaceCart();
	racecart->SetControllable(true);
	racecart->SetMass(100.0f);
	racecart->SetHorsePower(100000.0f);
	racecart->AddAll(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);

	pengine::Object3D* tiger = resourceManager->LoadXFile(&std::string("resources/cart/cart.x"));
	racecart->SetObject3D(tiger);

	RaceCart* racecart1 = new RaceCart();
	racecart1->SetMass(100.0f);
	racecart1->AddAll(-150.0f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	racecart1->SetObject3D(tiger);

	pengine::Object3D* trackStraight = resourceManager->LoadXFile(&std::string("resources/track/trackstraight.X"));
	pengine::Object3D* trackCurved = resourceManager->LoadXFile(&std::string("resources/track/trackcurved.X"));
	Track* track = new Track();
	
	track->AddTrackBlock(TrackBlock::TYPE::STRAIGHT, trackStraight);
	track->AddTrackBlock(TrackBlock::TYPE::STRAIGHT, trackStraight);
	track->AddTrackBlock(TrackBlock::TYPE::STRAIGHT, trackStraight);
	track->AddTrackBlock(TrackBlock::TYPE::LEFT, trackCurved);
	track->AddTrackBlock(TrackBlock::TYPE::RIGHT, trackCurved);
	track->AddTrackBlock(TrackBlock::TYPE::RIGHT, trackCurved);
	track->AddTrackBlock(TrackBlock::TYPE::STRAIGHT, trackStraight);
	track->AddTrackBlock(TrackBlock::TYPE::STRAIGHT, trackStraight);
	track->AddTrackBlock(TrackBlock::TYPE::LEFT, trackCurved);
	track->AddTrackBlock(TrackBlock::TYPE::RIGHT, trackCurved);
	track->AddTrackBlock(TrackBlock::TYPE::RIGHT, trackCurved);

	track->AddTrackBlock(TrackBlock::TYPE::STRAIGHT, trackStraight);
	track->AddTrackBlock(TrackBlock::TYPE::STRAIGHT, trackStraight);
	track->AddTrackBlock(TrackBlock::TYPE::STRAIGHT, trackStraight);
	track->AddTrackBlock(TrackBlock::TYPE::LEFT, trackCurved);
	track->AddTrackBlock(TrackBlock::TYPE::RIGHT, trackCurved);
	track->AddTrackBlock(TrackBlock::TYPE::RIGHT, trackCurved);
	track->AddTrackBlock(TrackBlock::TYPE::STRAIGHT, trackStraight);
	track->AddTrackBlock(TrackBlock::TYPE::STRAIGHT, trackStraight);
	track->AddTrackBlock(TrackBlock::TYPE::LEFT, trackCurved);
	track->AddTrackBlock(TrackBlock::TYPE::RIGHT, trackCurved);
	track->AddTrackBlock(TrackBlock::TYPE::RIGHT, trackCurved);

	pengine::Ground* ground = resourceManager->LoadGround(groundResource, groundTexture);
	ground->InitQuadTree(1);
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

	raceScene->SetAmountOfRenderTextures(1);

	return raceScene;
}