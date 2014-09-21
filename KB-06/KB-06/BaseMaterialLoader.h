#ifndef _RESOURCE_BASEMATERIALFACTORY_H_
#define _RESOURCE_BASEMATERIALFACTORY_H_

#include "mesh.h"
#include <vector>
#include <map>

namespace Resource
{
	class BaseMaterialLoader
	{
	public:
		BaseMaterialLoader(){};
		~BaseMaterialLoader();

		virtual std::map<std::string, Material> Load(const std::string file) = 0;
		virtual std::string GetExtension() = 0;
	};
}
#endif