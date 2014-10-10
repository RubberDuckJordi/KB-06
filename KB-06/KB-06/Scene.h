#ifndef _PENGINE_SCENE_H_
#define _PENGINE_SCENE_H_

#include <list>
#include "Entity.h"
#include "EntityCamera.h"
#include "Renderer.h"
#include "LoggerPool.h"
#include "Input.h"
#include "Skybox.h"
#include "Ground.h"
#include "SceneCallback.h"
#include "Collidable.h"
#include <functional>

namespace pengine
{
	class Scene
	{
	public:
		Scene();
		~Scene();
		virtual void Update(float deltaTime, std::map<Input, long>* actions);
		void AddEntity(Entity* entity);
		void AddCollidable(Collidable* collidable);
		void Render(Renderer* renderer);

		EntityCamera* GetCurrentCamera();
		void SetCurrentCamera(EntityCamera* camera);
		void SetSceneCallback(SceneCallback* callback);
		void SetSkybox(Skybox* skybox);
		void SetGround(Ground* ground);
		SceneCallback* callback;

	protected:
		std::list<Entity*> entities;
		std::list<Collidable*> collidables;
		EntityCamera* currentCamera;
		Logger* logger;
		Skybox* skybox;
		Ground* ground;
	};
}
#endif
