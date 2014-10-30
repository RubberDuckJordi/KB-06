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

	racecart->AddCheckPoint(block00);
	racecart->AddCheckPoint(block01);
	racecart->AddCheckPoint(block02);
	racecart->AddCheckPoint(block03);
	racecart->AddCheckPoint(block04);
	racecart->AddCheckPoint(block05);
	racecart->AddCheckPoint(block06);
	racecart->AddCheckPoint(block07);
	racecart->AddCheckPoint(block08);
	racecart->AddCheckPoint(block09);
	racecart->AddCheckPoint(block10);
	racecart->AddCheckPoint(block11);
	racecart->AddCheckPoint(block12);
	racecart->AddCheckPoint(block13);
	racecart->AddCheckPoint(block14);
	racecart->AddCheckPoint(block15);
	racecart->AddCheckPoint(block16);
	racecart->AddCheckPoint(block17);
	racecart->AddCheckPoint(block18);
	racecart->AddCheckPoint(block19);
	racecart->AddCheckPoint(block20);
	racecart->AddCheckPoint(block21);
	racecart->AddCheckPoint(block00); // Finish block

	racecart->SetLastCheckPoint(block00);
	racecart1->SetLastCheckPoint(block00);
	racecart->SetTrackHeight(trackStraight->GetMaxY());
	racecart1->SetTrackHeight(trackStraight->GetMaxY());
	racecart->AddPosition(0.0f, trackStraight->GetMaxY(), 0.0f);
	racecart1->AddPosition(0.0f, trackStraight->GetMaxY(), 0.0f);

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
	raceScene->SetRaceCart(racecart);

	raceScene->SetAmountOfRenderTextures(1);

	return raceScene;
}