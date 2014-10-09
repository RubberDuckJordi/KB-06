// CubeGame.cpp : Defines the entry point for the console application.
//

#include "PEngine.h"
#include "RGBAColor.h"
#include "RaceSceneFactory.h"

#include "XModelLoader.h"
#include "DirectXRenderer.h"
#include "HeightmapLoader.h"

#include "Object3D.h"
#include "SuperXLoader.h"

pengine::Object3D* kapotlelijk(pengine::ResourceManager* resourceManager)
{
	pengine::SuperXLoader* loader = new pengine::SuperXLoader();
	pengine::Model3D* model = new pengine::Model3D();
	loader->Load("resources/tiger.x", model);

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

	delete loader;


	return MyObject;
}

int main(int argc, const char* argv[])
{
	pengine::PEngine pEngine;
	pengine::Logger* logger = pengine::LoggerPool::GetInstance().GetInstance().GetLogger();
	pEngine.Init();

	pEngine.NewWindow(10, 10, 500, 500);
	pEngine.InitRenderer();

	pengine::XModel* xmodel = new pengine::XModel();
	pengine::XModelLoader* xmodelLoader = new pengine::XModelLoader();
	xmodelLoader->LoadXModel("resources/tiger.x", static_cast<pengine::DirectXRenderer*>(pEngine.GetRenderer()), xmodel);

	pengine::XModel* xmodel2 = new pengine::XModel();
	xmodelLoader->LoadXModel("resources/rechtdoor.x", static_cast<pengine::DirectXRenderer*>(pEngine.GetRenderer()), xmodel2);

	pengine::Object3D* object3d = kapotlelijk(pEngine.GetResourceManager());

	pengine::RGBAColor color;
	color.r = 1.0f;
	color.g = 0.25f;
	color.b = 1.0f;
	color.a = 1.0f;

	racer::RaceSceneFactory* sceneFactory = new racer::RaceSceneFactory(pEngine.GetResourceManager());
	sceneFactory->SetXModel(xmodel);
	sceneFactory->SetXModel2(xmodel2);
	sceneFactory->SetObject3D(object3d);
	sceneFactory->SetGroundResource("resources/heightmap.bmp");
	sceneFactory->SetGroundTexture("resources/heightmaptexture.bmp");
	sceneFactory->SetSkyboxTexture("resources/dome2.jpg");

	pEngine.AddSceneFactory("raceScene", sceneFactory);
	pengine::Scene* scene = pEngine.AddScene("raceScene");
	pEngine.SetCurrentScene(scene);
	pEngine.GameLoop();

	pengine::LoggerPool::GetInstance().ReturnLogger(logger);

	return 0;
}

