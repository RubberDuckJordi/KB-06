#ifndef _RESOURCE_BASEMESHLOADER_H_
#define _RESOURCE_BASEMESHLOADER_H_

#include "mesh.h"
#include "ResourceManager.h"

namespace Resource
{

	class ResourceManager;

	class BaseMeshLoader
	{
	public:
		BaseMeshLoader();
		~BaseMeshLoader();
		virtual Mesh Load(std::string file, const ResourceManager* resourceManager) = 0;
		virtual std::string GetExtension() = 0;
	};
}
#endif