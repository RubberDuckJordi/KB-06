// CubeGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "PEngine.h"
#include "ObjMeshFactory.h"
#include "RGBAColor.h"
#include "Mesh.h"
#include "SceneFactory.h"
#include "DefaultSceneFactory.h"

int _tmain(int argc, _TCHAR* argv[])
{
	PEngine pEngine;
	Logger::Logger* logger = Logger::LoggerPool::GetInstance().GetInstance().GetLogger();
	pEngine.Init();

	pEngine.GetWindowManager()->NewWindow(10, 10, 500, 500);
	pEngine.GetRenderer()->InitD3D(pEngine.GetWindowManager()->GetLastWindow()->GetHWND());
	pEngine.GetResourceManager()->AddMeshLoader(new Resource::ObjMeshFactory());
	
	Scene::SceneFactory* sceneFactory = new Scene::DefaultSceneFactory();
	pEngine.GetSceneManager()->AddSceneFactory("iets", sceneFactory);
	pEngine.GetSceneManager()->AddScene("iets");
	Resource::RGBAColor color;
	color.r = 1.0f;
	color.g = 1.0f;
	color.b = 1.0f;
	color.a = 0.5f;
	Resource::Mesh* mesh = pEngine.GetResourceManager()->LoadMesh("cube.obj.mesh", "obj.mesh");

	pEngine.GetRenderer()->SetViewMatrix(0.0f, 0.0f, -2.0f, 0.0f, 0.0f, 0.0f);
	pEngine.GetRenderer()->SetProjectionMatrix(3.14159265358979323846f / 4, 100.0f);
	while (pEngine.GetWindowManager()->HasActiveWindow())
	{

		pEngine.GetWindowManager()->UpdateWindows();
		
		// Logics
		std::map<Input::Input, long> actions = pEngine.GetInputManager()->GetCurrentActions(pEngine.GetWindowManager()->GetLastWindow());
		if (actions.size() > 0){
			logger->Log(Logger::Logger::INFO, "Input!");
		}
		pEngine.GetSceneManager()->UpdateActiveScene(actions);

		// Visuals
		pEngine.GetRenderer()->ClearScene(0UL, 0UL, color, 1.0f, 0UL);
		pEngine.GetRenderer()->BeginScene();
		pEngine.GetSceneManager()->RenderActiveScene(pEngine.GetRenderer());

		pEngine.GetRenderer()->Draw(mesh);
		pEngine.GetRenderer()->EndScene();
		pEngine.GetRenderer()->PresentScene(pEngine.GetWindowManager()->GetLastWindow()->GetHWND());
	}
	Logger::LoggerPool::GetInstance().ReturnLogger(logger);
}
