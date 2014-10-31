#ifndef _PENGINE_VERTEXBUFFERWRAPPER_H_
#define _PENGINE_VERTEXBUFFERWRAPPER_H_

#include <d3dx9.h>

/*
Wrapper to wrap directX specific implementation
*/

namespace pengine
{
	class VertexBufferWrapper
	{
	public:
		VertexBufferWrapper();
		~VertexBufferWrapper();
		void SetVertexBuffer(IDirect3DVertexBuffer9* _VertexBuffer, unsigned int numVertices);
		IDirect3DVertexBuffer9* GetVertexBuffer();
		unsigned int GetNumVertices();

		void SetFVF(int fvf);
		int GetFVF();

	private:
		IDirect3DVertexBuffer9* vertexBuffer;
		int fvf;
		unsigned int numVertices;
	};
}
#endif