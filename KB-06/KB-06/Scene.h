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
#include <vector>

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
		void AddStaticCollidable(Collidable* collidable);
		/*!
		This function is called right after loading all the resources, 
		allowing the skybox/ground/entities to cache their resources to
		the renderer, if they have any.
		Should be overwritten if you have specific resources in your
		program that need to be cached to the renderer, make sure to
		call pengine::Scene::CacheToRenderer(renderer) too.
		*/
		virtual void CacheToRenderer(Renderer* renderer);
		/*!
		You will have to set the camera yourself, then render whatever you please.
		This function will not be called if SetAmountOfRenderTextures is not called or 0.
		*/
		virtual void RenderToTexture(int texture, Renderer* renderer);
		virtual void Render(Renderer* renderer);

		EntityCamera* GetCurrentCamera();
		void SetCurrentCamera(EntityCamera* camera);
		void SetSceneCallback(SceneCallback* callback);
		void SetSkybox(Skybox* skybox);
		void SetGround(Ground* ground);
		void SetAmountOfRenderTextures(int amount);
		int GetAmountOfRenderTextures();

	protected:
		void GoDeeper(QuadNode* node, int chunkStartX, int chunkStartZ, int chunkEndX, int chunkEndZ, int depth);
		void ProcessCollision();
		void UpdateLevelOfDetail();

		bool wireFrameActivated;
		std::list<Entity*> entities;
		
		// Lists are separated for performance, static collidables don't need to be checked agaist eachother.
		std::list<Collidable*> collidables;
		std::list<Collidable*> staticCollidables;

		EntityCamera* currentCamera;
		Logger* logger;
		SceneCallback* callback;
		Skybox* skybox;
		Ground* ground;
		int amountOfRenderTextures;
	};
}
#endif
