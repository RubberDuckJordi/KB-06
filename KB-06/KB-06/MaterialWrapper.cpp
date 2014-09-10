#ifndef _MATERIALWRAPPER_CPP_
#define _MATERIALWRAPPER_CPP_

#include <d3dx9.h>

class MaterialWrapper
{
public:
	MaterialWrapper::MaterialWrapper(D3DMATERIAL9 _material)
	{
		material = _material;
	};

	MaterialWrapper::~MaterialWrapper()
	{

	};

	void MaterialWrapper::SetMaterial(D3DMATERIAL9 _material)
	{
		material = _material;
	};

	D3DMATERIAL9 MaterialWrapper::GetMaterial()
	{
		return material;
	};

private:
	D3DMATERIAL9 material;
};

#endif