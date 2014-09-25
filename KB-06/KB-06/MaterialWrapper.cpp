#include "MaterialWrapper.h"

Renderer::MaterialWrapper::MaterialWrapper(D3DMATERIAL9* _material)
{
	material = _material;
}

Renderer::MaterialWrapper::~MaterialWrapper()
{

}

void Renderer::MaterialWrapper::SetMaterial(D3DMATERIAL9* _material)
{
	material = _material;
}

D3DMATERIAL9* Renderer::MaterialWrapper::GetMaterial()
{
	return material;
}
