#include "DefaultScene.h"
#include "Logger.h"

Scene::DefaultScene::DefaultScene(){

}

Scene::DefaultScene::~DefaultScene(){

}

void Scene::DefaultScene::Update(){
	Scene::Update();
	Logger::Logger::GetLogger("main")->Log(Logger::Logger::DEBUG, "DefaultScene::Update()");
}