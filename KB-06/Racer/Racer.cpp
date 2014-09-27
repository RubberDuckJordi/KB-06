// CubeGame.cpp : Defines the entry point for the console application.
//

#include "PEngine.h"
#include "ObjMeshLoader.h"
#include "MtlLoader.h"
#include "RGBAColor.h"
#include "Mesh.h"
#include "SceneFactory.h"
#include "DefaultSceneFactory.h"

#include "XModelLoader.h"
#include "DirectXRenderer.h"

int main(int argc, char* argv[])
{
	pengine::PEngine pEngine;
	pengine::Logger* logger = pengine::LoggerPool::GetInstance().GetInstance().GetLogger();
	pEngine.Init();

	pEngine.GetWindowManager()->AddWindowListener(pEngine.GetInputManager());
	pEngine.GetWindowManager()->NewWindow(10, 10, 500, 500);
	pEngine.GetRenderer()->InitD3D(pEngine.GetWindowManager()->GetLastWindow()->GetHWND());
	pEngine.GetResourceManager()->AddMeshLoader(new pengine::ObjMeshLoader());
	pEngine.GetResourceManager()->AddMaterialLoader(new pengine::MtlLoader());

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

	pengine::Mesh* mesh = pEngine.GetResourceManager()->LoadMesh("resources/cube.obj.mesh", "obj.mesh");
	pengine::Mesh* mesh2 = pEngine.GetResourceManager()->LoadMesh("resources/cubeClone.obj.mesh", "obj.mesh");
	pengine::Mesh* mesh3 = pEngine.GetResourceManager()->LoadMesh("resources/cubeCloneClone.obj.mesh", "obj.mesh");

	pengine::DefaultSceneFactory* sceneFactory = new pengine::DefaultSceneFactory();
	sceneFactory->setMesh(mesh);
	sceneFactory->setMesh2(mesh2);
	sceneFactory->setMesh3(mesh3);
	sceneFactory->SetXModel(xmodel);
	sceneFactory->SetXModel2(xmodel2);

	pEngine.GetSceneManager()->AddSceneFactory("iets", sceneFactory);
	pengine::Scene* scene = pEngine.GetSceneManager()->AddScene("iets");
	pEngine.GetSceneManager()->SetCurrentScene(scene);

	pEngine.GetRenderer()->SetProjectionMatrix(M_PI / 4, 100.0f);
	pEngine.GetRenderer()->SetDefaultRenderStates();
	while (pEngine.GetWindowManager()->HasActiveWindow())
	{
		pEngine.GetWindowManager()->UpdateWindows();

		// Logics
		std::map<pengine::Input, long>* actions = pEngine.GetInputManager()->GetCurrentActions();

		pEngine.GetSceneManager()->UpdateActiveScene(actions);

		// Visuals
		pEngine.GetRenderer()->ClearScene(0UL, 0UL, color, 1.0f, 0UL);
		pEngine.GetRenderer()->BeginScene();
		pEngine.GetRenderer()->SetLights();
		pEngine.GetSceneManager()->RenderActiveScene(pEngine.GetRenderer());

		pEngine.GetRenderer()->EndScene();
		pEngine.GetRenderer()->PresentScene(pEngine.GetWindowManager()->GetLastWindow()->GetHWND());
	}
	pengine::LoggerPool::GetInstance().ReturnLogger(logger);
}
