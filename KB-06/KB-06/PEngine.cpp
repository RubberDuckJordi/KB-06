#include "stdafx.h"
#include "PEngine.h"
#include "DirectInputDeviceFactory.h"
#include "DirectXRenderer.h"

pengine::PEngine::PEngine()
{
	logger = LoggerPool::GetInstance().GetLogger();
	logger->NewFile();
}

pengine::PEngine::~PEngine()
{
	delete inputManager;
	delete windowManager;
	delete sceneManager;
	delete renderer;
	delete resourceManager;

	logger->Log(Logger::INFO, "Destructed PEngine");
	LoggerPool::GetInstance().ReturnLogger(logger);
}

void pengine::PEngine::Init()
{
	// Aanmaken van deze factory moet in een abstract factory gaan gebeuren
	windowManager = new WindowManager();
	InputDeviceFactory* inputDeviceFactory = new DirectInputDeviceFactory();
	inputManager = new InputManager(inputDeviceFactory);
	windowManager->AddWindowListener(inputManager);
	renderer = new DirectXRenderer();
	sceneManager = new SceneManager();
	resourceManager = new ResourceManager();
}

void pengine::PEngine::InitRenderer(){
	GetRenderer()->InitD3D(GetWindowManager()->GetLastWindow()->GetHWND());
	GetRenderer()->SetProjectionMatrix(M_PI / 4, 100.0f);
	GetRenderer()->SetDefaultRenderStates();

}

pengine::WindowManager* pengine::PEngine::GetWindowManager()
{
	return windowManager;
}

pengine::ResourceManager* pengine::PEngine::GetResourceManager()
{
	return resourceManager;
}

pengine::SceneManager* pengine::PEngine::GetSceneManager()
{
	return sceneManager;
}

pengine::InputManager* pengine::PEngine::GetInputManager()
{
	return inputManager;
}

pengine::Renderer* pengine::PEngine::GetRenderer()
{
	return renderer;
}

void pengine::PEngine::NewWindow(int x, int y, int width, int height){
	GetWindowManager()->NewWindow(x, y, width, height);
}

void pengine::PEngine::AddSceneFactory(char* key, SceneFactory* sceneFactory){
	GetSceneManager()->AddSceneFactory("raceScene", sceneFactory);
}

pengine::Scene* pengine::PEngine::AddScene(char* sceneFactory){
	return sceneManager->AddScene(sceneFactory);
}

void pengine::PEngine::SetCurrentScene(Scene* scene){
	sceneManager->SetCurrentScene(scene);
}

void pengine::PEngine::GameLoop(){
	pengine::RGBAColor color;
	color.r = 1.0f;
	color.g = 0.25f;
	color.b = 1.0f;
	color.a = 1.0f;

	while (GetWindowManager()->HasActiveWindow())
	{
		GetWindowManager()->UpdateWindows();

		// Logics
		std::map<pengine::Input, long>* actions = GetInputManager()->GetCurrentActions();
		GetSceneManager()->UpdateActiveScene(actions);

		// Visuals
		GetRenderer()->ClearScene(0UL, 0UL, color, 1.0f, 0UL);
		GetRenderer()->BeginScene();
		GetRenderer()->SetLights();
		GetSceneManager()->RenderActiveScene(GetRenderer());
		GetRenderer()->EndScene(); 
		for (auto windowIt = GetWindowManager()->GetAllWindows()->begin(); windowIt != GetWindowManager()->GetAllWindows()->end(); ++windowIt)
		{
			GetRenderer()->PresentScene((*windowIt)->GetHWND());
		}
	}
}