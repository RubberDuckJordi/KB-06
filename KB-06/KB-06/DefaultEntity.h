#ifndef _PENGINE_DEFAULT_ENTITY_H_
#define _PENGINE_DEFAULT_ENTITY_H_

#include "Entity.h"
#include "Logger.h"
#include "Renderer.h"

namespace pengine
{
	class DefaultEntity : public Entity {
	public:
		DefaultEntity();
		~DefaultEntity();
		void UpdateLogic(float deltaTime, std::map<Input, long>* actions);
		void Draw(Renderer* renderer);
		float rotationMod = 0.0f;

	private:
	};
}
#endif