#include "RaceScene.h"

racer::RaceScene::RaceScene()
{

}

racer::RaceScene::~RaceScene()
{

}

void racer::RaceScene::Update(float deltaTime, std::map<pengine::Input, long>* actions)
{
	Scene::Update(deltaTime, actions);
	GetCurrentCamera()->SetThirdPersonEntity(raceCart, 0.1f, 20.0f);
}

void racer::RaceScene::SetRaceCart(pengine::Entity* entity)
{
	raceCart = entity;
}

void racer::RaceScene::Render(pengine::Renderer* renderer)
{
	Scene::Render(renderer);
}