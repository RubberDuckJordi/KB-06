#ifndef __SCENE_DEFAULT_SCENE_FACTORY_H__
#define __SCENE_DEFAULT_SCENE_FACTORY_H__

#include "SceneFactory.h"
#include "Mesh.h"

namespace Scene{
	class DefaultSceneFactory : public SceneFactory
	{
	public:
		DefaultSceneFactory();
		~DefaultSceneFactory();
		Scene* CreateScene();
		void setMesh(Resource::Mesh* mesh);
	private:
		Resource::Mesh* mesh;
	};
}

#endif