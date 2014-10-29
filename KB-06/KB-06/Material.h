#ifndef _PENGINE_MATERIAL_H
#define _PENGINE_MATERIAL_H

#include "RGBAColor.h"
#include "RGBColor.h"
#include "BinaryData.h"

#include <string>

namespace pengine
{
	class Material
	{
	public:

		Material();

		~Material();

		bool IsName(std::string &pText);

		//The name of the material
		std::string name;

		std::string texturePath;
		BinaryData* texture;

		RGBAColor   diffuse;        /* Diffuse color RGBA */
		RGBColor    ambient;        /* Ambient color RGB */
		RGBColor    specular;       /* Specular 'shininess' */
		RGBColor    emissive;       /* Emissive color RGB */
		float       power;          /* Sharpness if specular highlight */
	};
}
#endif