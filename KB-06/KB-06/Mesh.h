#ifndef _RESOURCE_MESH_H_
#define _RESOURCE_MESH_H_
#include <vector>
#include "Subset.h"

namespace Resource
{
	struct Mesh
	{
		std::vector<Subset> subsets;
	};
}
#endif