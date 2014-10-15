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

	void PEngine::GameLoop(){
		RGBAColor color;
		color.r = 1.0f;
		color.g = 0.25f;
		color.b = 1.0f;
		color.a = 1.0f;
		std::chrono::high_resolution_clock::time_point currentTime = std::chrono::high_resolution_clock::now();
		GetRenderer()->SetLights();
		while (GetWindowManager()->HasActiveWindow())
		{
			std::chrono::high_resolution_clock::time_point newTime = std::chrono::high_resolution_clock::now();
			float deltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(newTime - currentTime).count();
			currentTime = std::chrono::high_resolution_clock::now();

			const int fps = int(1 / deltaTime);

			GetWindowManager()->GetLastWindow()->SetTitle(("fps: " + std::to_string(fps)).c_str());
			GetWindowManager()->UpdateWindows();

			// Logics
			std::map<Input, long>* actions = GetInputManager()->GetCurrentActions();
			GetSceneManager()->UpdateActiveScene(deltaTime, actions);

			// Visuals
			GetRenderer()->ClearScene(0UL, 0UL, color, 1.0f, 0UL);
			GetRenderer()->BeginScene();
			GetSceneManager()->RenderActiveScene(GetRenderer());
			GetRenderer()->EndScene();
			for (auto windowIt = GetWindowManager()->GetAllWindows()->begin(); windowIt != GetWindowManager()->GetAllWindows()->end(); ++windowIt)
			{
				GetRenderer()->PresentScene((*windowIt)->GetHWND());
			}
			GetWindowManager()->PurgeClosedWindows();
		}
	}
}