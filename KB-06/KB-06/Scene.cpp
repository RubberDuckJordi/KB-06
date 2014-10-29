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
		while (!collidables.empty())
		{
			delete collidables.front(), collidables.pop_front();
		}
		while (!staticCollidables.empty())
		{
			delete staticCollidables.front(), staticCollidables.pop_front();
		}
		delete callback;
		delete currentCamera;
		delete skybox;
		delete ground;
	}

	void Scene::Update(float deltaTime, std::map<Input, long>* actions)
	{
		// Toggle wireframe
		typedef std::map<pengine::Input, long>::iterator it_type;
		for (it_type iterator = (*actions).begin(); iterator != (*actions).end(); ++iterator)
		{
			switch (iterator->first)
			{
			case pengine::Input::KEY_TAB:
				wireFrameActivated = !wireFrameActivated;
				break;
			}
		}

		ProcessCollision();

		for (std::list<Entity*>::iterator i = entities.begin(); i != entities.end(); ++i)
		{
			(*i)->UpdateLogic(deltaTime, actions);
		}

		currentCamera->UpdateLogic(deltaTime, actions);

		// Update ground level of detail
		UpdateLevelOfDetail();
	}

	void Scene::ProcessCollision()
	{
		//The following code is highly inefficient ;)

		// Init the collision boxes
		for (std::list<Collidable*>::iterator i = collidables.begin(); i != collidables.end(); ++i)
		{
			(*i)->InitCollisionBox();
		}
		for (std::list<Collidable*>::iterator i = staticCollidables.begin(); i != staticCollidables.end(); ++i)
		{
			(*i)->InitCollisionBox();
		}

		// Keep track of effects, will be executed after this loop
		std::list<COLLISIONEFFECT*> collisionEffects;

		// Collision detection for movable objects
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
						effect->isStatic = false;

						effect->type = (*i)->GetType();

						effect->mass = (*i)->GetCollisionMass();

						collisionEffects.push_back(effect);

						// effect of second object
						COLLISIONEFFECT* effect2 = new COLLISIONEFFECT();
						effect2->collidable1 = (*j);
						effect2->collidable2 = (*i);

						effect2->forceVectorX = vectorj->x - vector->x;
						effect2->forceVectorY = vectorj->y - vector->y;
						effect2->forceVectorZ = vectorj->z - vector->z;

						effect2->mass = (*j)->GetCollisionMass();
						effect2->isStatic = false;

						effect2->type = (*j)->GetType();

						collisionEffects.push_back(effect2);
					}
				}
			}
		}

		// Collision detection for static objects
		for (std::list<Collidable*>::iterator i = collidables.begin(); i != collidables.end(); ++i)
		{
			for (std::list<Collidable*>::iterator j = staticCollidables.begin(); j != staticCollidables.end(); ++j)
			{
				if ((*j)->CheckCollision(*i))
				{
					// Only the movable object needs to receive an effect
					// It only needs to know that there is a collision with a static object.
					COLLISIONEFFECT* effect = new COLLISIONEFFECT();
					effect->collidable1 = (*j);
					effect->collidable2 = (*i);
					effect->type = (*j)->GetType();
					effect->isStatic = true;

					collisionEffects.push_back(effect);

					// The static object might still want to know what collided
					COLLISIONEFFECT* effect2 = new COLLISIONEFFECT();
					effect2->collidable1 = (*i);
					effect2->collidable2 = (*j);
					effect2->type = (*i)->GetType();
					effect2->isStatic = false;

					collisionEffects.push_back(effect2);
				}
			}
		}

		// Apply previously stored force changes
		for (std::list<COLLISIONEFFECT*>::iterator i = collisionEffects.begin(); i != collisionEffects.end(); ++i)
		{
			(*i)->collidable2->OnCollide(*i);
		}

		for (std::list<COLLISIONEFFECT*>::iterator i = collisionEffects.begin(); i != collisionEffects.end(); ++i)
		{
			delete (*i);
		}
	}

	void Scene::UpdateLevelOfDetail()
	{
		// If the quadtree doesn't support the depth, set it to the quadtree's depth
		// quadtree's depth can be set by the user when creating the scene
		int levelOfDetailDepth = ground->GetQuadTreeDepth();

		int widthChunk = (ground->GetWidth() - 1) / (levelOfDetailDepth + 1);
		int depthChunk = (ground->GetHeight() - 1) / (levelOfDetailDepth + 1);

		QuadNode* rootNode = ground->GetQuadTree();

		for (int i = 0; i <= levelOfDetailDepth; ++i)
		{
			for (int j = 0; j <= levelOfDetailDepth; ++j)
			{
				int chunkStartX = i * widthChunk;
				int chunkStartZ = j * depthChunk;
				int chunkEndX = widthChunk + i * widthChunk;
				int chunkEndZ = depthChunk + j * depthChunk;

				GoDeeper(rootNode, chunkStartX, chunkStartZ, chunkEndX, chunkEndZ, levelOfDetailDepth);
			}
		}
	}

	void Scene::GoDeeper(QuadNode* node, int chunkStartX, int chunkStartZ, int chunkEndX, int chunkEndZ, int depth)
	{
		// There is no need to go deeper or set the level of distance if the chunk is not within the node's boundaries
		if ((node->GetMinX() >= chunkEndX || node->GetMaxX() <= chunkStartX) ||
			(node->GetMinZ() >= chunkEndZ || node->GetMaxZ() <= chunkStartZ))
		{
			return;
		}

		if (depth == 0 || node->IsLeaf())
		{
			// Calculate the middle point of the chunk and the node to be able to calculate the distance
			int chunkPointX = chunkStartX + ((chunkEndX - chunkStartX) / 2);
			int chunkPointZ = chunkStartZ + ((chunkEndZ - chunkStartZ) / 2);

			int nodePointX = node->GetMinX() + ((node->GetMaxX() - node->GetMinX()) / 2);
			int nodePointZ = node->GetMinZ() + ((node->GetMaxZ() - node->GetMinZ()) / 2);

			int distance = sqrt(pow(currentCamera->GetPosition()->z - nodePointX, 2) + pow(currentCamera->GetPosition()->x - nodePointZ, 2));

			int nodesDistance = distance / (min(chunkEndX - chunkStartX, chunkEndZ - chunkStartZ));
			node->SetLevelOfDetail(1 << nodesDistance);
			return;
		}

		for (std::map<char, QuadNode*> ::iterator i = node->GetChildren()->begin(); i != node->GetChildren()->end(); ++i) {
			GoDeeper(i->second, chunkStartX, chunkStartZ, chunkEndX, chunkEndZ, depth - 1);
		}
	}

	void Scene::AddEntity(Entity* entity)
	{
		entities.push_back(entity);
	}

	void Scene::AddCollidable(Collidable* collidable)
	{
		collidables.push_back(collidable);
	}

	void Scene::AddStaticCollidable(Collidable* collidable)
	{
		staticCollidables.push_back(collidable);
	}

	void Scene::CacheToRenderer(Renderer* renderer)
	{
		skybox->CacheToRenderer(renderer);
		ground->CacheToRenderer(renderer);
		if (entities.size() != 0)
		{
			for (auto i = entities.begin(); i != entities.end(); ++i)
			{
				(*i)->CacheToRenderer(renderer);
			}
		}
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
		renderer->SetViewMatrix(currentCamera->GetViewMatrix());
		renderer->SetProjectionMatrix(currentCamera->GetProjectionMatrix());


		Vector3* cameraPosition = currentCamera->GetPosition();
		if (skybox != NULL)
		{
			skybox->Render(renderer, cameraPosition);
		}

		int entitiesLoaded = 0;
		for each(Entity* entity in entities)
		{
			/*if (currentCamera->SphereInFrustum(entity->GetPosition(), entity->GetRadius()))
			{*/
			entity->Render(renderer);
			++entitiesLoaded;
			//}
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
		for (auto i = staticCollidables.begin(); i != staticCollidables.end(); ++i)
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