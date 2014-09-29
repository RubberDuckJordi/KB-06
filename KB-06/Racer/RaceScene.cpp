#include "RaceScene.h"

racer::RaceScene::RaceScene()
{

}

racer::RaceScene::~RaceScene()
{

}

void racer::RaceScene::Update(std::map<pengine::Input, long>* actions)
{
	Scene::Update(actions);
	GetCurrentCamera()->SetThirdPersonEntity(raceCart, 10.0f, 5.0f);
}

void racer::RaceScene::SetRaceCart(pengine::Entity* entity)
{
	raceCart = entity;
}

void racer::RaceScene::Render(pengine::Renderer* renderer)
{
	Scene::Render(renderer);
}