#include "Material.h"

namespace pengine
{
	Material::Material()
	{
		diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
		ambient = { 1.0f, 1.0f, 1.0f };
		specular = { 1.0f, 1.0f, 1.0f };
		emissive = { 1.0f, 1.0f, 1.0f };
		power = 50;
	}

	Material::~Material()
	{
		//We don't delete the texture because we're not the owner... the resource manager is!
	}

	bool Material::IsName(std::string &pText)
	{
		if (strcmp(pText.c_str(), name.c_str()) == 0)
		{
			return true;
		}
		return false;
	}
}