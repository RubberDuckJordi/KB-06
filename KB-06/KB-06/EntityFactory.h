#ifndef __SCENE_ENTITY_FACTORY_H__
#define __SCENE_ENTITY_FACTORY_H__

#include "Entity.h"

namespace Scene{
	class EntityFactory {
	public:
		virtual Entity* CreateEntity() = 0;
	};
}

#endif