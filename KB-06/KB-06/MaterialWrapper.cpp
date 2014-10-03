#include "MaterialWrapper.h"

namespace pengine
{
	MaterialWrapper::MaterialWrapper(D3DMATERIAL9* _material)
	{
		material = _material;
	}

	MaterialWrapper::~MaterialWrapper()
	{

	}

	void MaterialWrapper::SetMaterial(D3DMATERIAL9* _material)
	{
		material = _material;
	}

	D3DMATERIAL9* MaterialWrapper::GetMaterial()
	{
		return material;
	}
}