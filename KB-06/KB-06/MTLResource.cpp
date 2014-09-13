#include "stdafx.h"
#include "MTLResource.h"


Resource::MTLResource::MTLResource()
{
}


Resource::MTLResource::~MTLResource()
{
}

Resource::Material Resource::MTLResource::GetMaterial(char* name)
{
	return materials[name];
}

void Resource::MTLResource::AddMaterial(char* name, Material material)
{
	materials[name] = material;
}

std::map<char*, Resource::Material>* Resource::MTLResource::GetAllMaterials()
{
	return &materials;
}

void Resource::MTLResource::SetLoaded(bool state)
{
	isLoaded = state;
}