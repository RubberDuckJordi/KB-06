#ifndef __SCENE_DEFAULT_ENTITY_FACTORY_H__
#define __SCENE_DEFAULT_ENTITY_FACTORY_H__

#include "EntityFactory.h"
#include "DefaultEntity.h"

namespace Scene{
	class DefaultEntityFactory : public EntityFactory{
	public:
		DefaultEntityFactory();
		~DefaultEntityFactory();
		Entity* CreateEntity();
	};
}

#endif