// CubeGame.cpp : Defines the entry point for the console application.
//

#include "PEngine.h"
#include "RGBAColor.h"
#include "RaceSceneFactory.h"

#include "DirectXRenderer.h"
#include "HeightmapLoader.h"

#include "Object3D.h"
#include "SuperXLoader.h"
#include "EventManager.h"

int main(int argc, const char* argv[])
{
	pengine::PEngine pEngine;
	pengine::Logger* logger = pengine::LoggerPool::GetInstance().GetLogger();
	pEngine.Init();

	pEngine.NewWindow(10, 10, 500, 500);
	pEngine.InitRenderer();

	pengine::Object3D* object3d = pEngine.GetResourceManager()->LoadXFile(&std::string("resources/tiger.x"));
	pengine::Object3D* object3d2 = pEngine.GetResourceManager()->LoadXFile(&std::string("resources/debugSphere.x"));

	std::string rechtdoorPath = "resources/rechtdoor.x";
	std::string nietRechtdoorPath = "resources/niet-rechtdoor.x";

	pengine::Object3D* weg = pEngine.GetResourceManager()->LoadXFile(&rechtdoorPath);
	pengine::Object3D* weg2 = pEngine.GetResourceManager()->LoadXFile(&nietRechtdoorPath);

	racer::RaceSceneFactory* sceneFactory = new racer::RaceSceneFactory(pEngine.GetResourceManager());
	sceneFactory->SetXModel2(weg);
	sceneFactory->SetXModel3(weg2);
	sceneFactory->SetObject3D(object3d);
	sceneFactory->SetObject3D2(object3d2);
	sceneFactory->SetGroundResource("resources/heightmap.bmp");
	sceneFactory->SetGroundTexture("resources/heightmaptexture.bmp");
	sceneFactory->SetSkyboxTexture("resources/dome2.jpg");

	pEngine.AddSceneFactory("raceScene", sceneFactory);
	pengine::Scene* scene = pEngine.AddScene("raceScene");

	// <EventManager voorbeeld>
	EventManager* eventManager = new EventManager();
	eventManager->CreateNewEvent("event");
	class Iets : public EventListener {
		void ProcEvent(std::string name){
			std::cout << "Event prov example" << std::endl;
		}
	};
	Iets* iets = new Iets();
	eventManager->Subscribe("event", iets);
	eventManager->Proc("event");
	// </EventManager voorbeeld>

	pEngine.SetCurrentScene(scene);
	pEngine.GameLoop();
	return 0;
}

