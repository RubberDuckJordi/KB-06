#include "Scene.h"
#include "CollisionEffect.h"

namespace pengine
{
	Scene::Scene()
	{
		logger = LoggerPool::GetInstance().GetLogger();
		gravity = Vector3(0.0f, -9.81f, 0.0f);
	}

	Scene::~Scene()
	{
		while (!entities.empty())
		{
			delete entities.front(), entities.pop_front();
		}
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
		int numOfIterations = (int)(deltaTime / 0.1f) + 1;	// Calculate Number Of Iterations To Be Made At 
															// This Update Depending On maxPossible_dt And dt
		if (numOfIterations != 0)							// Avoid Division By Zero
			deltaTime = deltaTime / numOfIterations;		// dt Should Be Updated According To numOfIterations

		for (int a = 0; a < numOfIterations; ++a)			// We Need To Iterate Simulations "numOfIterations" Times
		{
			for (std::list<Entity*>::iterator i = entities.begin(); i != entities.end(); ++i)
			{
				(*i)->UpdateLogic(deltaTime, actions);
			}
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
			if(currentCamera->SphereInFrustum(entity->GetPosition(), entity->GetRadius()))
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
		for (std::list<Collidable*>::iterator i = collidables.begin(); i != collidables.end(); ++i)
		{
			(*i)->DrawCollidable(renderer);
		}
		renderer->SetFillMode(PENGINE_FILL_SOLID);

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

	void Scene::SetGround(Ground* p_ground)
	{
		ground = p_ground;
	}
}