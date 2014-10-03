// CubeGame.cpp : Defines the entry point for the console application.
//

#include "PEngine.h"
#include "RGBAColor.h"
#include "RaceSceneFactory.h"

#include "XModelLoader.h"
#include "DirectXRenderer.h"
#include "HeightmapLoader.h"

int main(int argc, const char* argv[])
{
	pengine::PEngine pEngine;
	pengine::Logger* logger = pengine::LoggerPool::GetInstance().GetInstance().GetLogger();
	pEngine.Init();

	pengine::HeightmapLoader heightmapLoader;
	pengine::Ground* ground = heightmapLoader.LoadHeightmap("resources/heightmap.bmp");

	pEngine.NewWindow(10, 10, 500, 500);
	pEngine.InitRenderer();

	pengine::XModel* xmodel = new pengine::XModel();
	pengine::XModelLoader* xmodelLoader = new pengine::XModelLoader();
	xmodelLoader->LoadXModel("resources/tiger.x", static_cast<pengine::DirectXRenderer*>(pEngine.GetRenderer()), xmodel);

	pengine::XModel* xmodel2 = new pengine::XModel();
	xmodelLoader->LoadXModel("resources/rechtdoor.x", static_cast<pengine::DirectXRenderer*>(pEngine.GetRenderer()), xmodel2);

	pengine::RGBAColor color;
	color.r = 1.0f;
	color.g = 0.25f;
	color.b = 1.0f;
	color.a = 1.0f;

	racer::RaceSceneFactory* sceneFactory = new racer::RaceSceneFactory();
	sceneFactory->SetXModel(xmodel);
	sceneFactory->SetXModel2(xmodel2);

	pEngine.AddSceneFactory("raceScene", sceneFactory);
	pengine::Scene* scene = pEngine.AddScene("raceScene");
	pEngine.SetCurrentScene(scene);
	pEngine.GetSceneManager()->GetCurrentScene()->InitSkybox(pEngine.GetRenderer(), "resources/dome.jpg");
	pEngine.GetSceneManager()->GetCurrentScene()->SetGround(ground);
	pEngine.GameLoop();

	pengine::LoggerPool::GetInstance().ReturnLogger(logger);

	return 0;
}

