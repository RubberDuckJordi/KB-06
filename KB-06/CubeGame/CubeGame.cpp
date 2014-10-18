// CubeGame.cpp : Defines the entry point for the console application.
//

#include "PEngine.h"
#include "RGBAColor.h"
#include "SceneFactory.h"
#include "DefaultSceneFactory.h"
#include "DirectXRenderer.h"

#include "SuperXLoader.h"
#include "Object3D.h"
#include "Matrix.h"

//#include "Shader.h"

int main(int argc, const char* argv[])
{
	pengine::PEngine pEngine;
	pengine::Logger* logger = pengine::LoggerPool::GetInstance().GetInstance().GetLogger();
	pEngine.Init();

	pEngine.GetWindowManager()->AddWindowListener(pEngine.GetInputManager());
	pEngine.GetWindowManager()->NewWindow(750, 10, 750, 750);
	
	pEngine.InitRenderer();
	/*pEngine.GetRenderer()->CreateD2DFactory();
	pEngine.GetRenderer()->CreateRenderTarget(pEngine.GetWindowManager()->GetLastWindow()->GetHWND());
	pEngine.GetRenderer()->CreateWICImagingFactory();
	pEngine.GetRenderer()->CreateDecoder("resources/testHUD.bmp");
	pEngine.GetRenderer()->CreateFormatConverter();
	pEngine.GetRenderer()->GetBitmapFrame();
	pEngine.GetRenderer()->InitializeBMP();
	pEngine.GetRenderer()->CreateBitmapFromWIC();*/


	pengine::DefaultSceneFactory* sceneFactory = new pengine::DefaultSceneFactory(pEngine.GetResourceManager());
	sceneFactory->SetSkyboxTexture("resources/dome.jpg");

	pEngine.GetSceneManager()->AddSceneFactory("iets", sceneFactory);
	pengine::Scene* scene = pEngine.GetSceneManager()->SetScene("iets");
	pEngine.GetSceneManager()->SetCurrentScene(scene);

	pEngine.SetShader(pEngine.GetResourceManager()->LoadShader("", "", "TestShader", pEngine.GetRenderer()));
	
//	pEngine.GetShader()->InitShader(pEngine.GetRenderer());

	pengine::BinaryData* font = pEngine.GetResourceManager()->LoadBinaryFile("resources/font.png");
	pEngine.GetRenderer()->SetFontTexture(font);

	pEngine.SetCurrentScene(scene);
	pEngine.GameLoop();
	
}