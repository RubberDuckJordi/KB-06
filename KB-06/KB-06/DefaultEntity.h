#ifndef _PENGINE_DEFAULT_ENTITY_H_
#define _PENGINE_DEFAULT_ENTITY_H_

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
		void UpdateLogic(float deltaTime, std::map<Input, long>* actions);
		void Draw(Renderer* renderer);
		//void SetMesh(Mesh* mesh);
		float rotationMod = 0.0f;
		void SetXModel(XModel*); //debug

	private:
		XModel* xModel; //debug
		//Mesh* myMesh;
	};
}
#endif