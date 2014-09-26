#ifndef __SCENE_DEFAULT_SCENE_FACTORY_H__
#define __SCENE_DEFAULT_SCENE_FACTORY_H__

#include "SceneFactory.h"
#include "Mesh.h"
#include "XModel.h"

namespace pengine
{
	class DefaultSceneFactory : public SceneFactory
	{
	public:
		DefaultSceneFactory();
		~DefaultSceneFactory();
		Scene* CreateScene();
		void setMesh(Mesh* mesh);//debug!
		void setMesh2(Mesh* mesh);//debug!
		void setMesh3(Mesh* mesh);//debug!
		void SetXModel(XModel*); //debug
		void SetXModel2(XModel*); //debug
	private:
		Mesh* mesh;//debug!
		Mesh* mesh2;//debug!
		Mesh* mesh3;//debug!

		XModel* xModel; //debug.
		XModel* xModel2; //debug.
	};
}
#endif