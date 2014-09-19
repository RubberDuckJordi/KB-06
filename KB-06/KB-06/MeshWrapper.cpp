#include "MeshWrapper.h"

    Renderer::MeshWrapper::MeshWrapper(LPD3DXMESH _mesh)
	{
		mesh = _mesh;
	};

	Renderer::MeshWrapper::~MeshWrapper()
	{

	};

	void Renderer::MeshWrapper::SetMesh(LPD3DXMESH _mesh)
	{
		mesh = _mesh;
	};

	LPD3DXMESH Renderer::MeshWrapper::GetMesh()
	{
		return mesh;
	};



