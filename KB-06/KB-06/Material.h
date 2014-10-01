#ifndef _PENGINE_MATERIAL_H_
#define _PENGINE_MATERIAL_H_

#include "RGBColor.h"
#include <string>
#include "BinaryData.h"

namespace pengine
{
	struct Material
	{
		std::string name;
		BinaryData defaultTexture;
		RGBColor ambientColor;
		RGBColor diffuseColor;
		RGBColor SpecularColor;
		float specularWeight;
		float alpha;
	};
}
#endif