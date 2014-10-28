#include "PEngine.h"
#include "DirectInputDeviceFactory.h"
#include "DirectXRenderer.h"

#include <chrono>
#include <ctime>
#include <ratio>

namespace pengine
{
	PEngine::PEngine()
	{
		logger = LoggerPool::GetInstance().GetLogger();
		logger->Log(Logger::INFO, "Constructed PEngine");
	}

	PEngine::~PEngine()
	{
		delete inputManager;
		delete windowManager;
		delete sceneManager;
		delete renderer;
		delete resourceManager;
		logger->Log(Logger::INFO, "Destructed PEngine");
	}

	void PEngine::Init()
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

	void PEngine::InitRenderer(){
		GetRenderer()->InitD3D(GetWindowManager()->GetLastWindow()->GetHWND());
		GetRenderer()->SetProjectionMatrix(M_PI / 4, 100.0f);
		GetRenderer()->SetDefaultRenderStates();
	}

	WindowManager* PEngine::GetWindowManager()
	{
		return windowManager;
	}

	ResourceManager* PEngine::GetResourceManager()
	{
		return resourceManager;
	}

	SceneManager* PEngine::GetSceneManager()
	{
		return sceneManager;
	}

	InputManager* PEngine::GetInputManager()
	{
		return inputManager;
	}

	Renderer* PEngine::GetRenderer()
	{
		return renderer;
	}

	void PEngine::SetShader(Shader* shader)
	{
		TestShader = shader;
	}

	Shader* PEngine::GetShader()
	{
		return TestShader;
	}

	void PEngine::NewWindow(int x, int y, int width, int height){
		GetWindowManager()->NewWindow(x, y, width, height);
	}

	void PEngine::AddSceneFactory(char* key, SceneFactory* sceneFactory){
		GetSceneManager()->AddSceneFactory("raceScene", sceneFactory);
	}

	Scene* PEngine::AddScene(char* sceneFactory){
		return sceneManager->SetScene(sceneFactory);
	}

	void PEngine::SetCurrentScene(Scene* scene){
		sceneManager->SetCurrentScene(scene);
	}

	Scene* PEngine::CreateScene(char* sceneFactory, std::string* filePath)
	{
		std::vector<std::string>* sceneFile = resourceManager->LoadSceneFile(filePath);
		Scene* scene = sceneManager->CreateScene(sceneFile, sceneFactory, resourceManager);
		resourceManager->CacheToRenderer(renderer);//maybe not the nicest place, but works! :)
		scene->CacheToRenderer(renderer);
		sceneManager->SetCurrentScene(scene);


		return scene;
	}

	void PEngine::GameLoop()
	{
		double currentTime = clock();
		GetRenderer()->SetLights();
		while (GetWindowManager()->HasActiveWindow())
		{
			double newTime = clock();
			float deltaTime = (newTime - currentTime) / CLOCKS_PER_SEC;
			currentTime = clock();

			const int fps = int(1 / deltaTime);

			GetWindowManager()->GetLastWindow()->SetTitle(("fps: " + std::to_string(fps)).c_str());
			GetWindowManager()->UpdateWindows();

			// Logics
			std::map<Input, long>* actions = GetInputManager()->GetCurrentActions();
			GetSceneManager()->UpdateActiveScene(deltaTime, actions);

			// Visuals
			GetSceneManager()->RenderActiveScene(GetRenderer()); 
			/*
			GetAllWindows() is a thing not allowed in any kind of manager...
			for (auto windowIt = GetWindowManager()->GetAllWindows()->begin(); windowIt != GetWindowManager()->GetAllWindows()->end(); ++windowIt)
			{
				GetRenderer()->PresentScene((*windowIt)->GetHWND());
			}*/
			GetRenderer()->PresentScene(GetWindowManager()->GetLastWindow()->GetHWND());
			GetWindowManager()->PurgeClosedWindows();
		}
	}
}