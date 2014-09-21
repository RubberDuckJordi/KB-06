#ifndef _RESOURCE_BASEMESHFACTORY_H_
#define _RESOURCE_BASEMESHFACTORY_H_

#include "mesh.h"
#include <vector>

namespace Resource
{
	class BaseMeshLoader
	{
	public:
		BaseMeshLoader(){};
		~BaseMeshLoader();

		virtual Mesh Load(const std::string file) = 0;
		virtual std::string GetExtension() = 0;
	};
}
#endif