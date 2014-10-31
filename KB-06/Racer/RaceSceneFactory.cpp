#include "RaceSceneFactory.h"
#include "RaceScene.h"
#include "RaceCart.h"
#include "DefaultEntity.h"
#include "track.h"
#include "trackblock.h"
#include "Ground.h"
#include "Material.h"

#include "TinyEntity.h"

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

	

	pengine::EntityCamera* camera = new pengine::EntityCamera();
	camera->useInput = false;
	scene->SetCurrentCamera(camera);
	scene->SetAmountOfRenderTextures(1);
	return scene;
}

pengine::Scene* racer::RaceSceneFactory::CreateScene()
{
	pengine::Logger* logger = pengine::LoggerPool::GetInstance().GetLogger();

	TinyEntity* tiny = new TinyEntity();
	tiny->SetObject3D(resourceManager->LoadXFile(&std::string("resources/tiny/tiny.x")));
	tiny->SetAll(0, 122, 0, 0, 270, 0, 0.05f, 0.05f, 0.05f);

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
	raceScene->AddEntity(tiny);
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

	std::string* shaderp = resourceManager->LoadShaderFile("resources/shaders/shaderp.fx");
	raceScene->shaderp = shaderp;
	return raceScene;
}