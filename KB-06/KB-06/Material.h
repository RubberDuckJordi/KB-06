#ifndef _PENGINE_MATERIAL_H
#define _PENGINE_MATERIAL_H

#include "Types.h"
#include "Array.h"
#include "RGBAColor.h"
#include "RGBColor.h"
#include "BinaryData.h"

#include <string>

namespace pengine
{
	class Material
	{
	public:

		Material()
		{
			diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
			ambient = { 1.0f, 1.0f, 1.0f };
			specular = { 1.0f, 1.0f, 1.0f };
			emissive = { 1.0f, 1.0f, 1.0f };
			power = 50;
		};

		~Material()
		{
			//We don't delete the texture because we're not the owner... the resource manager is!
		};

		bool IsName(std::string &pText)
		{
			if (strcmp(pText.c_str(), name.c_str()) == 0)
			{
				return true;
			}
			return false;
		}

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