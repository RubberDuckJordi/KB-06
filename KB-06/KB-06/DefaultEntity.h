#ifndef __SCENE_DEFAULT_ENTITY_H__
#define __SCENE_DEFAULT_ENTITY_H__

#include "Entity.h"
#include "Logger.h"

namespace Scene{
	class DefaultEntity : public Entity {
	public:
		DefaultEntity();
		~DefaultEntity();
		void Update();
	};
}

#endif