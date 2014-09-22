#ifndef __SCENE_DEFAULT_ENTITY_H__
#define __SCENE_DEFAULT_ENTITY_H__

#include "Entity.h"
#include "Logger.h"
#include "Renderer.h"

namespace Scene{
	class DefaultEntity : public Entity {
	public:
		DefaultEntity();
		~DefaultEntity();
		void UpdateLogic(std::map<Input::Input, long>* actions);
		void Draw(Renderer::Renderer* renderer);
		void SetMesh(Resource::Mesh* mesh);
		float rotationMod = 0.0f;

	private:
		Resource::Mesh* myMesh;
	};

}

#endif