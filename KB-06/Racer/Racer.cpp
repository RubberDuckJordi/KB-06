// CubeGame.cpp : Defines the entry point for the console application.
//

#include "PEngine.h"
#include "RGBAColor.h"
#include "RaceSceneFactory.h"

#include "DirectXRenderer.h"
#include "HeightmapLoader.h"

#include "Object3D.h"
#include "SuperXLoader.h"

int main(int argc, const char* argv[])
{
	pengine::PEngine pEngine;
	pengine::Logger* logger = pengine::LoggerPool::GetInstance().GetLogger();
	pEngine.Init();

	pEngine.NewWindow(10, 10, 750, 750);
	pEngine.InitRenderer();

	//!!!WE ARE MANAGING A SCENE OUTSIDE THE SCENE MANAGER!!!
	racer::RaceSceneFactory* sceneFactory = new racer::RaceSceneFactory(pEngine.GetResourceManager());
	sceneFactory->SetGroundResource("resources/heightmap.bmp");
	sceneFactory->SetGroundTexture("resources/heightmaptexture.bmp");
	sceneFactory->SetSkyboxTexture("resources/dome2.jpg");

	pEngine.AddSceneFactory("raceScene", sceneFactory);
	pengine::Scene* scene = pEngine.AddScene("raceScene");

	pengine::BinaryData* font = pEngine.GetResourceManager()->LoadBinaryFile("resources/font.png");//we should probably do this in the scene
	pEngine.GetRenderer()->SetFontTexture(font);

	scene->CacheToRenderer(pEngine.GetRenderer());
	pEngine.GetResourceManager()->CacheToRenderer(pEngine.GetRenderer());
	//!!!WE ARE MANAGING A SCENE OUTSIDE THE SCENE MANAGER!!!


	pEngine.SetCurrentScene(scene);
	pEngine.GameLoop();
	return 0;
}

