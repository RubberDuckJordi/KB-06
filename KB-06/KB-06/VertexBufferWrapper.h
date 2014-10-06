#ifndef _PENGINE_VERTEXBUFFERWRAPPER_H_
#define _PENGINE_VERTEXBUFFERWRAPPER_H_

#include <d3dx9.h>

namespace pengine
{
	class VertexBufferWrapper
	{
	public:
		VertexBufferWrapper();
		~VertexBufferWrapper();
		void SetVertexBuffer(IDirect3DVertexBuffer9** _VertexBuffer);
		IDirect3DVertexBuffer9** GetVertexBuffer();

	private:
		IDirect3DVertexBuffer9** VertexBuffer;
	};
}
#endif