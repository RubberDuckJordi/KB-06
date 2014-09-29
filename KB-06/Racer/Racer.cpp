// CubeGame.cpp : Defines the entry point for the console application.
//

#include "PEngine.h"
#include "RGBAColor.h"
#include "RaceSceneFactory.h"

#include "XModelLoader.h"
#include "DirectXRenderer.h"

int main(int argc, const char* argv[])
{
	pengine::PEngine pEngine;
	pengine::Logger* logger = pengine::LoggerPool::GetInstance().GetInstance().GetLogger();
	pEngine.Init();

	pEngine.GetWindowManager()->AddWindowListener(pEngine.GetInputManager());
	pEngine.GetWindowManager()->NewWindow(10, 10, 500, 500);
	pEngine.GetRenderer()->InitD3D(pEngine.GetWindowManager()->GetLastWindow()->GetHWND());

	pengine::XModel* xmodel = new pengine::XModel();
	pengine::XModelLoader* xmodelLoader = new pengine::XModelLoader();
	xmodelLoader->LoadXModel("resources/tiger.x", static_cast<pengine::DirectXRenderer*>(pEngine.GetRenderer()), xmodel);

	pengine::XModel* xmodel2 = new pengine::XModel();
	xmodelLoader->LoadXModel("resources/camera.x", static_cast<pengine::DirectXRenderer*>(pEngine.GetRenderer()), xmodel2);

	pengine::RGBAColor color;
	color.r = 1.0f;
	color.g = 0.25f;
	color.b = 1.0f;
	color.a = 1.0f;

	racer::RaceSceneFactory* sceneFactory = new racer::RaceSceneFactory();
	sceneFactory->SetXModel(xmodel);
	sceneFactory->SetXModel2(xmodel2);

	pEngine.GetSceneManager()->AddSceneFactory("raceScene", sceneFactory);
	pengine::Scene* scene = pEngine.GetSceneManager()->AddScene("raceScene");
	pEngine.GetSceneManager()->SetCurrentScene(scene);

	pEngine.GetRenderer()->SetProjectionMatrix(M_PI / 4, 100.0f);
	pEngine.GetRenderer()->SetDefaultRenderStates();
	while (pEngine.GetWindowManager()->HasActiveWindow())
	{
		pEngine.GetWindowManager()->UpdateWindows();

		// Logics
		std::map<pengine::Input, long>* actions = pEngine.GetInputManager()->GetCurrentActions();

		pEngine.GetSceneManager()->UpdateActiveScene(1.0f, actions);

		// Visuals
		pEngine.GetRenderer()->ClearScene(0UL, 0UL, color, 1.0f, 0UL);
		pEngine.GetRenderer()->BeginScene();
		pEngine.GetRenderer()->SetLights();
		pEngine.GetSceneManager()->RenderActiveScene(pEngine.GetRenderer());

		pEngine.GetRenderer()->EndScene();
		pEngine.GetRenderer()->PresentScene(pEngine.GetWindowManager()->GetLastWindow()->GetHWND());
	}
	pengine::LoggerPool::GetInstance().ReturnLogger(logger);

	return 0;
}

