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
	RaceCart* racecart = new RaceCart();
	racecart->SetControllable(true);
	racecart->AddAll(7.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	racecart->SetXModel(xModel);

	RaceCart* racecart1 = new RaceCart();
	RaceCart* racecart2 = new RaceCart();
	RaceCart* racecart3 = new RaceCart();

	
	racecart1->AddAll(7.5f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	racecart2->AddAll(7.5f, 0.0f, -5.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	racecart3->AddAll(7.5f, -1.0f, 10.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);


	racecart1->SetXModel(xModel);
	racecart2->SetXModel(xModel);
	racecart3->SetXModel(xModel);

	RaceScene* raceScene = new RaceScene();
	raceScene->AddEntity(racecart);
	raceScene->AddEntity(racecart1);
	raceScene->AddEntity(racecart2);
	raceScene->AddEntity(racecart3);

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

void racer::RaceSceneFactory::SetXModel2(pengine::XModel* p_xModel)
{
	xModel2 = p_xModel;
}