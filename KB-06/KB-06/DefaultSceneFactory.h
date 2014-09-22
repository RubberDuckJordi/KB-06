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
		void setMesh(Resource::Mesh* mesh);//debug!
		void setMesh2(Resource::Mesh* mesh);//debug!
		void setMesh3(Resource::Mesh* mesh);//debug!
	private:
		Resource::Mesh* mesh;//debug!
		Resource::Mesh* mesh2;//debug!
		Resource::Mesh* mesh3;//debug!
	};
}

#endif