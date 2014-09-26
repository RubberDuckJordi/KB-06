#ifndef __SCENE_DEFAULT_ENTITY_H__
#define __SCENE_DEFAULT_ENTITY_H__

#include "Entity.h"
#include "Logger.h"
#include "Renderer.h"
#include "XModel.h"

namespace pengine
{
	class DefaultEntity : public Entity {
	public:
		DefaultEntity();
		~DefaultEntity();
		void UpdateLogic(std::map<Input, long>* actions);
		void Draw(Renderer* renderer);
		void SetMesh(Mesh* mesh);
		float rotationMod = 0.0f;
		void SetXModel(XModel*); //debug

	private:
		XModel* xModel; //debug
		Mesh* myMesh;
	};
}
#endif