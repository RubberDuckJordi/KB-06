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

pengine::Object3D* kapotlelijk(pengine::ResourceManager* resourceManager)
{
	std::string file = "resources/tiger.x";
	pengine::Model3D* model = resourceManager->LoadXFile(&file);

	for (std::list<pengine::Mesh*>::iterator i = model->_Meshes.begin(); i != model->_Meshes.end(); ++i)
	{
		for (std::list<pengine::Material*>::iterator j = (*i)->_Materials.begin(); j != (*i)->_Materials.end(); ++j)
		{
			if ((*j)->texturePath != "")
			{
				(*j)->texture = resourceManager->LoadBinaryFile("resources/" + (*j)->texturePath);
			}
		}
	}
	model->ConcatenateMeshes();

	pengine::Object3D* MyObject = new pengine::Object3D();
	MyObject->SetupModel(model);
	unsigned short int index = 0;
	MyObject->MapAnimationSet(index);
	//We set the interval of animation in steps
	MyObject->showWarning = false;
	MyObject->SetAnimationStep(80);
	MyObject->ClearSkinnedVertices();
	MyObject->UpdateAnimation();



	return MyObject;
}

pengine::Object3D* kapotlelijk(pengine::ResourceManager* resourceManager, std::string file)
{
	pengine::Model3D* model = resourceManager->LoadXFile(&file);

	for (std::list<pengine::Mesh*>::iterator i = model->_Meshes.begin(); i != model->_Meshes.end(); ++i)
	{
		for (std::list<pengine::Material*>::iterator j = (*i)->_Materials.begin(); j != (*i)->_Materials.end(); ++j)
		{
			if ((*j)->texturePath != "")
			{
				(*j)->texture = resourceManager->LoadBinaryFile("resources/" + (*j)->texturePath);
			}
		}
	}
	model->ConcatenateMeshes();

	pengine::Object3D* MyObject = new pengine::Object3D();
	MyObject->SetupModel(model);
	MyObject->showWarning = false;
	MyObject->ClearSkinnedVertices();


	return MyObject;
}

int main(int argc, const char* argv[])
{
	pengine::PEngine pEngine;
	pengine::Logger* logger = pengine::LoggerPool::GetInstance().GetInstance().GetLogger();
	pEngine.Init();

	pEngine.NewWindow(10, 10, 500, 500);
	pEngine.InitRenderer();

	pengine::Object3D* object3d = kapotlelijk(pEngine.GetResourceManager());

	pengine::Object3D* weg = kapotlelijk(pEngine.GetResourceManager(), "resources/rechtdoor.x");
	pengine::Object3D* weg2 = kapotlelijk(pEngine.GetResourceManager(), "resources/niet-rechtdoor.x");

	racer::RaceSceneFactory* sceneFactory = new racer::RaceSceneFactory(pEngine.GetResourceManager());
	sceneFactory->SetXModel2(weg);
	sceneFactory->SetXModel3(weg2);
	sceneFactory->SetObject3D(object3d);
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

	pengine::LoggerPool::GetInstance().ReturnLogger(logger);

	return 0;
}

