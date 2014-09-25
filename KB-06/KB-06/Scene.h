#ifndef __SCENE_SCENE_H__
#define __SCENE_SCENE_H__

#include <list>
#include "Entity.h"
#include "EntityCamera.h"
#include "Renderer.h"
#include "LoggerPool.h"
#include "Input.h"

namespace Scene
{
	class Scene
	{
	public:
		Scene();
		~Scene();
		virtual void Update(std::map<Input::Input, long>* actions);
		void AddEntity(Entity* entity);
		void Render(Renderer::Renderer* renderer);

		EntityCamera* GetCurrentCamera();
		void SetCurrentCamera(EntityCamera* camera);
	protected:
		std::list<Entity*> entities;
		EntityCamera* currentCamera;
		Logger::Logger* logger;
	};
}
#endif
