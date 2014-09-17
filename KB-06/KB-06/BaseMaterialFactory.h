#ifndef _RESOURCE_BASEMATERIALFACTORY_H_
#define _RESOURCE_BASEMATERIALFACTORY_H_

#include "mesh.h"
#include <vector>

namespace Resource
{
	class BaseMaterialFactory
	{
	public:
		BaseMaterialFactory();
		~BaseMaterialFactory();

		virtual std::pair<Material, std::vector<const std::string>> Load(const std::string file) = 0;
		virtual std::string GetExtension() = 0;
	};
}
#endif