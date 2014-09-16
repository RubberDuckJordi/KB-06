#ifndef _RESOURCE_MATERIAL_H_
#define _RESOURCE_MATERIAL_H_

#include "RGBColor.h"
#include <string>

namespace Resource
{
	struct Material 
	{
		std::string name;
		RGBColor ambientColor;
		RGBColor diffuseColor;
		RGBColor SpecularColor;
		float specularWeight;
		float alpha;
	};
}
#endif