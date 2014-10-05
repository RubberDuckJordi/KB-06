// CubeGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "PEngine.h"
#include "RGBAColor.h"
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

	pengine::IO_Model_X* loader = new pengine::IO_Model_X();
	pengine::Model3D* model = new pengine::Model3D();
	loader->Load("resources/camera.x", model);

	for (std::list<pengine::Mesh*>::iterator i = model->_Meshes.begin(); i != model->_Meshes.end(); ++i)
	{
		for (std::deque<pengine::Material*>::iterator j = (*i)->_Materials.begin(); j != (*i)->_Materials.end(); ++j)
		{
			logger->LogAll(pengine::Logger::DEBUG, "Texture name CubeGame: ", (*j)->texturePath);
			if ((*j)->texturePath != "")
			{
				(*j)->texture = pEngine.GetResourceManager()->LoadBinaryFile("resources/" + (*j)->texturePath);
			}
		}
	}
	model->ConcatenateMeshes();

	pengine::Object3D MyObject;
	MyObject.SetupModel(model);
	unsigned short int index = 0;
	MyObject.MapAnimationSet(index);
	//We set the interval of animation in steps
	MyObject.SetAnimationStep(80);//should use deltatime*80 here, and set it every time...
	MyObject.UpdateAnimation();
	MyObject.showWarning = false;

	pengine::DefaultSceneFactory* sceneFactory = new pengine::DefaultSceneFactory();
	sceneFactory->SetXModel(xmodel);
	sceneFactory->SetXModel2(xmodel2);

	pEngine.GetSceneManager()->AddSceneFactory("iets", sceneFactory);
	pengine::Scene* scene = pEngine.GetSceneManager()->SetScene("iets");
	pEngine.GetSceneManager()->SetCurrentScene(scene);
	pEngine.GetSceneManager()->GetCurrentScene()->InitSkybox(pEngine.GetRenderer(), "resources/dome.jpg");

	pEngine.GetRenderer()->SetProjectionMatrix(M_PI / 4, 100.0f);
	pEngine.GetRenderer()->SetDefaultRenderStates();
	bool pressPlus = false;
	pEngine.GetRenderer()->SetLights();//every time?

	while (pEngine.GetWindowManager()->HasActiveWindow())
	{
		pEngine.GetWindowManager()->UpdateWindows();

		// Logics
		std::map<pengine::Input, long>* actions = pEngine.GetInputManager()->GetCurrentActions();

		pEngine.GetSceneManager()->UpdateActiveScene(1.0f, actions);

		// Visuals
		pEngine.GetRenderer()->ClearScene(0UL, 0UL, color, 1.0f, 0UL);
		pEngine.GetRenderer()->BeginScene();

		pEngine.GetSceneManager()->RenderActiveScene(pEngine.GetRenderer());


		bool holdPlus = false;
		typedef std::map<pengine::Input, long>::iterator it_type;
		for (it_type iterator = (*actions).begin(); iterator != (*actions).end(); iterator++)
		{
			switch (iterator->first)
			{
			case pengine::Input::KEY_ADD:
				if (!pressPlus)
				{
					++index;
					MyObject.MapAnimationSet(index);
					pressPlus = true;
				}
				holdPlus = true;
				break;
			default:
				break;
			}
		}
		if (!holdPlus && pressPlus)
		{
			pressPlus = false;
		}
		//MyObject.UpdateAnimation();
		pengine::RenderMatrix* aMatrix = new pengine::RenderMatrix();
		aMatrix->CreateMatrix(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.1f, 0.1f, 0.1f, aMatrix->theMatrix);
		pEngine.GetRenderer()->SetActiveMatrix(aMatrix->theMatrix);
		MyObject.Draw(pEngine.GetRenderer());
		//pEngine.GetSkyBox()->Draw(pEngine.GetRenderer(), aMatrix);

		pEngine.GetRenderer()->EndScene();
		pEngine.GetRenderer()->PresentScene(pEngine.GetWindowManager()->GetLastWindow()->GetHWND());
		delete aMatrix;
	}
	pengine::LoggerPool::GetInstance().ReturnLogger(logger);
}

