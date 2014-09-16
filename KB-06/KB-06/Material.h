#ifndef _RESOURCE_MATERIAL_H_
#define _RESOURCE_MATERIAL_H_

#include "RGBColor.h"

namespace Resource
{
	struct Material 
	{
		char* name;
		RGBColor ambientColor;
		RGBColor diffuseColor;
		RGBColor SpecularColor;
		float specularWeight;
		float alpha;
	};
}
#endif