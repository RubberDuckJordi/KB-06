#include "MaterialWrapper.h"

pengine::MaterialWrapper::MaterialWrapper(D3DMATERIAL9* _material)
{
	material = _material;
}

pengine::MaterialWrapper::~MaterialWrapper()
{

}

void pengine::MaterialWrapper::SetMaterial(D3DMATERIAL9* _material)
{
	material = _material;
}

D3DMATERIAL9* pengine::MaterialWrapper::GetMaterial()
{
	return material;
}
