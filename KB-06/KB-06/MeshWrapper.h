#ifndef _MESHWRAPPER_H_
#define _MESHWRAPPER_H_

#include <d3dx9.h>

namespace Renderer
{
	class MeshWrapper
	{
	public:
		MeshWrapper::MeshWrapper(LPD3DXMESH _mesh);
		MeshWrapper::~MeshWrapper();
		void MeshWrapper::SetMesh(LPD3DXMESH _mesh);
		LPD3DXMESH MeshWrapper::GetMesh();
	private:
		LPD3DXMESH mesh;
	};
} 

#endif