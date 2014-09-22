// CubeGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "PEngine.h"
#include "ObjMeshLoader.h"
#include "MtlLoader.h"
#include "RGBAColor.h"
#include "Mesh.h"
#include "SceneFactory.h"
#include "DefaultSceneFactory.h"

int _tmain(int argc, _TCHAR* argv[])
{
	PEngine pEngine;
	Logger::Logger* logger = Logger::LoggerPool::GetInstance().GetInstance().GetLogger();
	pEngine.Init();

	pEngine.GetWindowManager()->AddWindowListener(pEngine.GetInputManager());
	pEngine.GetWindowManager()->NewWindow(10, 10, 500, 500);
	pEngine.GetRenderer()->InitD3D(pEngine.GetWindowManager()->GetLastWindow()->GetHWND());
	pEngine.GetResourceManager()->AddMeshLoader(new Resource::ObjMeshLoader());
	pEngine.GetResourceManager()->AddMaterialLoader(new Resource::MtlLoader());

	Resource::RGBAColor color;
	color.r = 1.0f;
	color.g = 0.25f;
	color.b = 1.0f;
	color.a = 1.0f;
	Resource::Mesh* mesh = pEngine.GetResourceManager()->LoadMesh("resources/cube.obj.mesh", "obj.mesh");

	Scene::DefaultSceneFactory* sceneFactory = new Scene::DefaultSceneFactory();
	sceneFactory->setMesh(mesh);

	pEngine.GetSceneManager()->AddSceneFactory("iets", sceneFactory);
	Scene::Scene* scene = pEngine.GetSceneManager()->AddScene("iets");
	pEngine.GetSceneManager()->SetCurrentScene(scene);
	
	//pEngine.GetRenderer()->SetViewMatrix(0.0f, 0.0f, -2.0f, 0.0f, 0.0f, 0.0f);
	pEngine.GetRenderer()->SetProjectionMatrix(3.14159265358979323846f / 4, 100.0f);
	pEngine.GetRenderer()->SetDefaultRenderStates();
	while (pEngine.GetWindowManager()->HasActiveWindow())
	{

		pEngine.GetWindowManager()->UpdateWindows();
		
		// Logics
		std::map<Input::Input, long>* actions = pEngine.GetInputManager()->GetCurrentActions();

		pEngine.GetSceneManager()->UpdateActiveScene(actions);

		// Visuals
		pEngine.GetRenderer()->ClearScene(0UL, 0UL, color, 1.0f, 0UL);
		pEngine.GetRenderer()->BeginScene();
		pEngine.GetRenderer()->SetLights();
		pEngine.GetSceneManager()->RenderActiveScene(pEngine.GetRenderer());

		pEngine.GetRenderer()->EndScene();
		pEngine.GetRenderer()->PresentScene(pEngine.GetWindowManager()->GetLastWindow()->GetHWND());
	}
	Logger::LoggerPool::GetInstance().ReturnLogger(logger);
}

