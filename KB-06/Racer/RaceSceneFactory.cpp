#include "RaceSceneFactory.h"
#include "RaceScene.h"
#include "RaceCart.h"
#include "DefaultEntity.h"
#include "track.h"
#include "trackblock.h"

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
	racecart->SetMass(100.0f);
	racecart->SetHorsePower(10.0f);
	racecart->AddAll(7.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	racecart->SetXModel(xModel);

	RaceCart* racecart1 = new RaceCart();
	RaceCart* racecart2 = new RaceCart();

	
	racecart1->AddAll(7.5f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	racecart2->AddAll(7.5f, 0.0f, -5.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	racecart1->SetXModel(xModel);
	racecart2->SetXModel(xModel);


	TrackBlock* trackBlock1 = new TrackBlock(10, 10);
	trackBlock1->SetXModel(xModel2);
	TrackBlock* trackBlock2 = new TrackBlock(10, 10);
	trackBlock2->SetXModel(xModel2);
	TrackBlock* trackBlock3 = new TrackBlock(10, 10);
	trackBlock3->SetXModel(xModel2);
	TrackBlock* trackBlock4 = new TrackBlock(10, 10);
	trackBlock4->SetXModel(xModel2);

	Track* track = new Track();
	track->AddTrackBlock(trackBlock1);
	track->AddTrackBlock(trackBlock2);
	track->AddTrackBlock(trackBlock3);
	track->AddTrackBlock(trackBlock4);
	track->SetAll(0, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);

	RaceScene* raceScene = new RaceScene();
	raceScene->AddEntity(racecart);
	raceScene->AddEntity(racecart1);
	raceScene->AddEntity(racecart2);
	raceScene->AddEntity(track);

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