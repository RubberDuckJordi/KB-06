#include "Scene.h"
#include "CollisionEffect.h"

namespace pengine
{
	Scene::Scene()
	{
		logger = LoggerPool::GetInstance().GetLogger();
		amountOfRenderTextures = 0;
		wireFrameActivated = false;
	}

	Scene::~Scene()
	{
		while (!entities.empty())
		{
			delete entities.front(), entities.pop_front();
		}
		delete ground;
	}

	void Scene::Update(float deltaTime, std::map<Input, long>* actions)
	{
		// Toggle wireframe
		typedef std::map<pengine::Input, long>::iterator it_type;
		for (it_type iterator = (*actions).begin(); iterator != (*actions).end(); ++iterator)
		{
			float speed = static_cast<float>(iterator->second);

			switch (iterator->first)
			{
			case pengine::Input::KEY_TAB:
				wireFrameActivated = !wireFrameActivated;
				break;
			}
		}

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

	void Scene::AddEntity(Entity* entity)
	{
		entities.push_back(entity);
	}

	void Scene::AddCollidable(Collidable* collidable)
	{
		collidables.push_back(collidable);
	}

	void Scene::RenderToTexture(int texture, Renderer* renderer)
	{
		//keep it empty so we're not forcing the client to implement this function.
	}

	void Scene::Render(Renderer* renderer)
	{
		/*Resource::Vertex* cameraPosition = currentCamera->GetPosition();
		Resource::Vertex* cameraRotation = currentCamera->GetRotation();*/

		//renderer->SetViewMatrix(0, 0, -0.5f, 0, 0, 0.5f);
		renderer->SetViewMatrix(currentCamera->GetViewMatrix(), false);
		renderer->SetProjectionMatrix(currentCamera->GetProjectionMatrix());


		Vector3* cameraPosition = currentCamera->GetPosition();
		if (skybox != NULL)
		{
			skybox->Draw(renderer, cameraPosition);
		}

		int entitiesLoaded = 0;
		for each(Entity* entity in entities)
		{
			if (currentCamera->SphereInFrustum(entity->GetPosition(), entity->GetRadius()))
			{
				entity->Draw(renderer);
				++entitiesLoaded;
			}
		}
		//logger->Log(Logger::DEBUG, "Rendered " + std::to_string(entitiesLoaded) + " of " + std::to_string(entities.size()) + " entities");

		if (ground != NULL)
		{
			ground->Render(renderer);
		}

		renderer->SetFillMode(PENGINE_FILL_WIREFRAME);
		Material mat;
		mat.ambient = { 1.0f, 0.0f, 0.0f };
		mat.diffuse = { 1.0f, 0.0f, 0.0f, 1.0f };
		mat.emissive = { 1.0f, 0.0f, 0.0f };
		mat.specular = { 1.0f, 0.0f, 0.0f };
		mat.power = 50.0f;
		renderer->SetMaterial(&mat);//WHY DOES THIS NOT MAKE THE WIREFRAME RED?!?!? >:( I DON'T UNDERSTAND!
		for (auto i = collidables.begin(); i != collidables.end(); ++i)
		{
			(*i)->DrawCollidable(renderer);
		}
		renderer->SetFillMode(PENGINE_FILL_SOLID);

		//restore wireframe status
		if (wireFrameActivated)
		{
			renderer->SetFillMode(PENGINE_FILL_WIREFRAME);
		}
		else
		{
			renderer->SetFillMode(PENGINE_FILL_SOLID);
		}

	}

	EntityCamera* Scene::GetCurrentCamera()
	{
		return currentCamera;
	}

	void Scene::SetCurrentCamera(EntityCamera* camera)
	{
		currentCamera = camera;
	}

	void Scene::SetSceneCallback(SceneCallback* callback)
	{
		this->callback = callback;
	}

	void Scene::SetSkybox(Skybox* p_skybox)
	{
		skybox = p_skybox;
	}

	void Scene::SetGround(Ground* p_ground)
	{
		ground = p_ground;
	}

	void Scene::SetAmountOfRenderTextures(int amount)
	{
		amountOfRenderTextures = amount;
	}

	int Scene::GetAmountOfRenderTextures()
	{
		return amountOfRenderTextures;
	}
}