#ifndef _RESOURCE_OBJLOADER_H_
#define _RESOURCE_OBJLOADER_H_
//#include "BaseMeshLoader.h"
#include "ResourceFactory.h"
namespace Resource
{
	class ObjLoader : public ResourceFactory
	{
	public:
		ObjLoader();
		//Mesh Load(const std::string file, const ResourceManager* resourceManager);
		//std::string GetExtension();
		Resource* LoadResource(char* path, ResourceManager* rsmgr);
	};
}

#endif