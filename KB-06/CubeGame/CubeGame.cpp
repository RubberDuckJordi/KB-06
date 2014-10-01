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
#include "Skybox.h"

#include "XModelLoader.h"
#include "DirectXRenderer.h"


#include "SuperXLoader.h"
#include "Object3D.h"
#include "RenderMatrix.h"

int _tmain(int argc, _TCHAR* argv[])
{
	pengine::PEngine pEngine;
	pengine::Logger* logger = pengine::LoggerPool::GetInstance().GetInstance().GetLogger();
	pEngine.Init();

	pEngine.GetWindowManager()->AddWindowListener(pEngine.GetInputManager());
	pEngine.GetWindowManager()->NewWindow(750, 10, 500, 500);
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


	IO_Model_X* loader = new IO_Model_X();
	Model3D* model = new Model3D();
	loader->Load("resources/tiny/tiny_4anim.x", model);
	model->ConcatenateMeshes();

	Object3D MyObject;
	MyObject.SetupModel(model);
	unsigned short int index = 2;
	MyObject.MapAnimationSet(index);
	//We set the interval of animation in steps
	MyObject.SetAnimationStep(80);
	MyObject.Update();

	pengine::DefaultSceneFactory* sceneFactory = new pengine::DefaultSceneFactory();
	sceneFactory->setMesh(mesh);
	sceneFactory->setMesh2(mesh2);
	sceneFactory->setMesh3(mesh3);
	sceneFactory->SetXModel(xmodel);
	sceneFactory->SetXModel2(xmodel2);

	pEngine.GetSceneManager()->AddSceneFactory("iets", sceneFactory);
	pengine::Scene* scene = pEngine.GetSceneManager()->SetScene("iets");
	pEngine.GetSceneManager()->SetCurrentScene(scene);
	pEngine.GetSceneManager()->GetCurrentScene()->InitSkybox(pEngine.GetRenderer(), "resources/grass.jpg");

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
		
		typedef std::map<pengine::Input, long>::iterator it_type;
		for (it_type iterator = (*actions).begin(); iterator != (*actions).end(); iterator++)
		{
			switch (iterator->first)
			{
			case pengine::Input::KEY_HOME:
				MyObject.ClearSkinnedVertices();
				MyObject.UpdateAnimation();
				//logger->LogAll(0, "finalmatrix: ");
				break;
			case pengine::Input::KEY_ADD:
				++index;
				MyObject.MapAnimationSet(index);
				//logger->LogAll(0, "finalmatrix: ");
				break;
			default:
				break;
			}
		}
		pengine::RenderMatrix* aMatrix = new pengine::RenderMatrix();
		aMatrix->CreateMatrix(0.0f, -25.0f, 0.0f, 0.0f, -90.0f, 0.0f, 0.1f, 0.1f, 0.1f, aMatrix->theMatrix);
		pEngine.GetRenderer()->SetActiveMatrix(aMatrix->theMatrix);
		MyObject.Draw(pEngine.GetRenderer());
		//pEngine.GetSkyBox()->Draw(pEngine.GetRenderer(), aMatrix);

		pEngine.GetRenderer()->EndScene();
		pEngine.GetRenderer()->PresentScene(pEngine.GetWindowManager()->GetLastWindow()->GetHWND());
		//delete aMatrix;
	}
	pengine::LoggerPool::GetInstance().ReturnLogger(logger);
}

