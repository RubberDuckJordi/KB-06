#include "Scene.h"
#include "CollisionEffect.h"

namespace pengine
{
	Scene::Scene()
	{
		logger = LoggerPool::GetInstance().GetLogger();
	}

	Scene::~Scene()
	{
		while (!entities.empty())
		{
			delete entities.front(), entities.pop_front();
		}
		LoggerPool::GetInstance().ReturnLogger(logger);

		delete ground;
	}

	void Scene::AddEntity(Entity* entity)
	{
		entities.push_back(entity);
	}

	void Scene::AddCollidable(Collidable* collidable)
	{
		collidables.push_back(collidable);
	}

	void Scene::SetSkybox(Skybox* p_skybox)
	{
		skybox = p_skybox;
	}

	void Scene::Update(float deltaTime, std::map<Input, long>* actions)
	{
		for (std::list<Entity*>::iterator i = entities.begin(); i != entities.end(); ++i)
		{
			(*i)->UpdateLogic(deltaTime, actions);
		}

		//The following code is highly inefficient ;)

		// Init the collision boxes
		for (std::list<Collidable*>::iterator i = collidables.begin(); i != collidables.end(); ++i)
		{
			(*i)->InitCollisionBox();
		}

		// Keep track of effects, will be executed after this loop
		std::list<COLLISIONEFFECT*> collisionEffects;

		// Collision detection
		for (std::list<Collidable*>::iterator i = collidables.begin(); i != collidables.end(); ++i)
		{
			for (std::list<Collidable*>::iterator j = collidables.begin(); j != collidables.end(); ++j)
			{
				if ((*i) != (*j))
				{
					if ((*i)->CheckCollision(*j))
					{
						COLLISIONEFFECT* effect = new COLLISIONEFFECT();
						effect->collidable1 = (*i);
						effect->collidable2 = (*j);

						Vector3* vector = (*i)->GetCollisionForceVector();
						Vector3* vectorj = (*j)->GetCollisionForceVector();
						effect->forceVectorX = vector->x - vectorj->x;
						effect->forceVectorY = vector->y - vectorj->y;
						effect->forceVectorZ = vector->z - vectorj->z;

						effect->mass = (*i)->GetCollisionMass();

						collisionEffects.push_back(effect);
					}
				}
			}
		}

		// Apply previously stored force changes
		for (std::list<COLLISIONEFFECT*>::iterator i = collisionEffects.begin(); i != collisionEffects.end(); ++i)
		{
			(*i)->collidable2->OnCollide(*i);
		}

		currentCamera->UpdateLogic(deltaTime, actions);
	}


	void Scene::Render(Renderer* renderer)
	{
		/*Resource::Vertex* cameraPosition = currentCamera->GetPosition();
		Resource::Vertex* cameraRotation = currentCamera->GetRotation();*/

		//renderer->SetViewMatrix(0, 0, -0.5f, 0, 0, 0.5f);
		renderer->SetActiveCamera(currentCamera->GetCameraData());

		Vertex* cameraPosition = currentCamera->GetPosition();

		if (skybox != NULL)
		{
			skybox->Draw(renderer, cameraPosition);
		}

		for each(Entity* entity in entities)
		{
			entity->Draw(renderer);
		}
		
		if (ground != NULL)
		{
			ground->Render(renderer);
		}

		renderer->SetCulling(PENGINE_CULL_NONE);
		renderer->SetFillMode(PENGINE_FILL_WIREFRAME);
		for (std::list<Collidable*>::iterator i = collidables.begin(); i != collidables.end(); ++i)
		{
			(*i)->DrawCollidable(renderer);
		}
		renderer->SetFillMode(PENGINE_FILL_SOLID);
		renderer->SetCulling(PENGINE_CULL_CCW);
	}

	EntityCamera* Scene::GetCurrentCamera()
	{
		return currentCamera;
	}

	void Scene::SetCurrentCamera(EntityCamera* camera)
	{
		currentCamera = camera;
	}

	void Scene::SetSceneCallback(SceneCallback* callback){
		this->callback = callback;
	}

	void Scene::SetGround(Ground* p_ground)
	{
		ground = p_ground;
	}
}