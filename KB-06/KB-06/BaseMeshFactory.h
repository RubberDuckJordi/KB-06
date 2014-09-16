#ifndef _RESOURCE_BASEMESHFACTORY_H_
#define _RESOURCE_BASEMESHFACTORY_H_

#include "mesh.h"

namespace Resource
{
	class BaseMeshFactory
	{
	public:
		BaseMeshFactory();
		~BaseMeshFactory();

		virtual Mesh Load(const std::string file) = 0;
		virtual std::string GetExtension() = 0;
	};
}
#endif