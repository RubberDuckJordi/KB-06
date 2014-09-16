#ifndef _RESOURCE_BASEMESHFACTORY_H_
#define _RESOURCE_BASEMESHFACTORY_H_

#include "mesh.h"
#include "ResourceManager.h"

namespace Resource
{
	class BaseMeshFactory
	{
	public:
		BaseMeshFactory();
		~BaseMeshFactory();
		virtual Mesh Load(const std::string file, const ResourceManager* resourceManager) = 0;
		virtual std::string GetExtension() = 0;
	};
}
#endif