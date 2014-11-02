#ifndef _PENGINE_MESHWRAPPER_H_
#define _PENGINE_MESHWRAPPER_H_

#include <d3dx9.h>

/*
Wrapper to wrap directX specific implementation

CLASS IS DEPRECATED BY Resource/RobertX/Mesh

*/

namespace pengine
{
	class MeshWrapper
	{
	public:
		MeshWrapper(LPD3DXMESH* _mesh);
		~MeshWrapper();
		void SetMesh(LPD3DXMESH* _mesh);
		LPD3DXMESH* GetMesh();
	private:
		LPD3DXMESH* mesh;
	};
}
#endif