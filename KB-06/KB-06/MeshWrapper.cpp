#include "MeshWrapper.h"

pengine::MeshWrapper::MeshWrapper(LPD3DXMESH* _mesh)
{
	mesh = _mesh;
}

pengine::MeshWrapper::~MeshWrapper()
{

}

void pengine::MeshWrapper::SetMesh(LPD3DXMESH* _mesh)
{
	mesh = _mesh;
}

LPD3DXMESH* pengine::MeshWrapper::GetMesh()
{
	return mesh;
}