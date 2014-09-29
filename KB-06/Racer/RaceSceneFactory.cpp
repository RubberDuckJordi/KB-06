#include "RaceSceneFactory.h"
#include "RaceScene.h"
#include "RaceCart.h"
#include "DefaultEntity.h"

racer::RaceSceneFactory::RaceSceneFactory()
{

}

racer::RaceSceneFactory::~RaceSceneFactory()
{

}

pengine::Scene* racer::RaceSceneFactory::CreateScene()
{
	pengine::DefaultEntity* entity = new pengine::DefaultEntity();
	RaceCart* racecart = new RaceCart();
	pengine::DefaultEntity* entity3 = new pengine::DefaultEntity();
	pengine::DefaultEntity* entity4 = new pengine::DefaultEntity();

	entity->AddAll(7.5f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	racecart->AddAll(7.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	entity3->AddAll(7.5f, 0.0f, -5.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	entity4->AddAll(7.5f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);

	entity->SetXModel(xModel);
	racecart->SetXModel(xModel);
	entity3->SetXModel(xModel);
	entity4->SetXModel(xModel);

	RaceScene* raceScene = new RaceScene();
	raceScene->AddEntity(entity);
	raceScene->AddEntity(racecart);
	raceScene->AddEntity(entity3);
	raceScene->AddEntity(entity4);

	pengine::EntityCamera* camera = new pengine::EntityCamera();
	camera->AddPosition(0.0f, 20.0f, 0.1f);
	camera->useInput = false;
	raceScene->SetCurrentCamera(camera);
	raceScene->SetRaceCart(racecart);

	return raceScene;
}

void racer::RaceSceneFactory::SetXModel(pengine::XModel* p_xModel)
{
	xModel = p_xModel;
}

void racer::RaceSceneFactory::SetXModel2(pengine::XModel* p_xModel)
{
	xModel2 = p_xModel;
}