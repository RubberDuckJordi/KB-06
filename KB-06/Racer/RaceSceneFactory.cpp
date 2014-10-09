#include "RaceSceneFactory.h"
#include "RaceScene.h"
#include "RaceCart.h"
#include "DefaultEntity.h"
#include "track.h"
#include "trackblock.h"
#include "Ground.h"
#include "Material.h"

racer::RaceSceneFactory::RaceSceneFactory(pengine::ResourceManager* resourceManager)
:SceneFactory(resourceManager)
{

}

racer::RaceSceneFactory::~RaceSceneFactory()
{
	pengine::SceneFactory::~SceneFactory();
}

pengine::Scene* racer::RaceSceneFactory::CreateScene()
{
	RaceCart* racecart = new RaceCart();
	racecart->SetControllable(true);
	racecart->SetMass(100.0f);
	racecart->SetHorsePower(10.0f);
	racecart->AddAll(7.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	racecart->SetObject3D(object3d);

	RaceCart* racecart1 = new RaceCart();
	racecart1->SetMass(100.0f);
	RaceCart* racecart2 = new RaceCart();
	racecart2->SetMass(100.0f);

	racecart1->AddAll(7.5f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	racecart2->AddAll(7.5f, 0.0f, -5.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	racecart1->SetObject3D(object3d);
	racecart2->SetObject3D(object3d);


	TrackBlock* trackBlock1 = new TrackBlock(10, 10);
	trackBlock1->SetXModel(xModel2);
	TrackBlock* trackBlock2 = new TrackBlock(10, 10);
	trackBlock2->SetXModel(xModel2);
	TrackBlock* trackBlock3 = new TrackBlock(10, 12);
	trackBlock3->SetXModel(xModel3);
	TrackBlock* trackBlock4 = new TrackBlock(10, 12);
	trackBlock4->SetXModel(xModel3);

	Track* track = new Track();
	track->AddTrackBlock(trackBlock1);
	track->AddTrackBlock(trackBlock2);
	track->AddTrackBlock(trackBlock3);
	track->AddTrackBlock(trackBlock4);
	track->SetAll(0, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);

	pengine::Ground* ground = resourceManager->LoadGround(groundResource, groundTexture);
	pengine::Skybox* skybox = new pengine::Skybox();
	pengine::Material* material = new pengine::Material();
	material->texture = resourceManager->LoadBinaryFile(skyboxTexture);

	skybox->SetMaterial(material);

	RaceScene* raceScene = new RaceScene();
	raceScene->AddEntity(racecart);
	raceScene->AddEntity(racecart1);
	raceScene->AddEntity(racecart2);
	raceScene->AddCollidable(racecart);
	raceScene->AddCollidable(racecart1);
	raceScene->AddCollidable(racecart2);
	raceScene->AddEntity(track);
	raceScene->SetGround(ground);
	raceScene->SetSkybox(skybox);

	pengine::EntityCamera* camera = new pengine::EntityCamera();
	camera->useInput = false;
	raceScene->SetCurrentCamera(camera);
	raceScene->SetRaceCart(racecart);

	return raceScene;
}

void racer::RaceSceneFactory::SetXModel(pengine::XModel* p_xModel)
{
	xModel = p_xModel;
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