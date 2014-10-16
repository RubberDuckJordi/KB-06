#include "SceneManager.h"
#include "SceneCallback.h"

namespace pengine
{
	SceneManager::SceneManager()
	{
		logger = LoggerPool::GetInstance().GetLogger();
	}

	SceneManager::~SceneManager()
	{
		logger->Log(Logger::INFO, "SceneManager destructed");
	}

	std::vector<std::string>* SceneManager::ReadScene(std::string* path, ResourceManager* resourceManager)
	{
		std::vector<std::string>* sceneFile = resourceManager->LoadSceneFile(path);

		return sceneFile;
	}

	Scene* SceneManager::CreateScene(std::vector<std::string>* sceneFile, char* factoryKey, ResourceManager* resourceManager)
	{
		SceneFactory* factory = sceneFactories.at(factoryKey);
		Scene* scene = factory->CreateScene(sceneFile, resourceManager);
		currentScene->SetSceneCallback(this);
		return scene;
	}

	void SceneManager::AddSceneFactory(char* key, SceneFactory* sceneFactory)
	{
		sceneFactories[key] = sceneFactory;
	}

	Scene* SceneManager::SetScene(char* sceneFactory)
	{
		if (sceneFactories.find(sceneFactory) != sceneFactories.end())
		{
			Scene* currentScene = sceneFactories.at(sceneFactory)->CreateScene();
			currentScene->SetSceneCallback(this);
			return currentScene;
		}
		else
		{
			logger->Log(Logger::ERR, "SceneFactory \"" + std::string(sceneFactory) + "\" not found");
			return NULL;
		}
	}

	void SceneManager::RemoveScene(Scene* scene)
	{

	}

	void SceneManager::UpdateScene(Scene* scene)
	{

	}

	void SceneManager::UpdateActiveScene(float deltaTime, std::map<Input, long>* actions)
	{
		currentScene->Update(deltaTime, actions);
	}

	void SceneManager::RenderActiveScene(Renderer* renderer)
	{
		if (currentScene == NULL)
		{
			if (scenes.size() > 0)
			{
				logger->Log(Logger::WARNING, "CurrentScene not set, defaulting to the first added scene");
				currentScene = scenes.front();
			}
			else
			{
				logger->Log(Logger::ERR, "CurrentScene not set and no scenes available in the SceneManager");
				return;
			}
		}
		currentScene->Render(renderer);
	}

	void SceneManager::SetCurrentScene(Scene* scene)
	{
		currentScene = scene;
	}

	Scene* SceneManager::GetCurrentScene()
	{
		return currentScene;
	}

	void SceneManager::ChangeScene(char* identifier){
		SetScene(identifier);
	}
}