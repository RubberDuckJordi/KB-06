#ifndef _MESHWRAPPER_CPP_
#define _MESHWRAPPER_CPP_

#include <d3dx9.h>

class MeshWrapper
{
public:
	MeshWrapper::MeshWrapper(LPD3DXMESH _mesh)
	{
		mesh = _mesh;
	};

	MeshWrapper::~MeshWrapper()
	{

	};

	void MeshWrapper::SetMesh(LPD3DXMESH _mesh)
	{
		mesh = _mesh;
	};

	LPD3DXMESH MeshWrapper::GetMesh()
	{
		return mesh;
	};

private:
	LPD3DXMESH mesh;
};

#endif