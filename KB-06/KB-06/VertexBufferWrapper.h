#ifndef _VERTEXBUFFERWRAPPER_H_
#define _VERTEXBUFFERWRAPPER_H_

#include <d3dx9.h>

namespace Renderer
{
	class VertexBufferWrapper
	{
	public:
		VertexBufferWrapper::VertexBufferWrapper(IDirect3DVertexBuffer9** _VertexBuffer);
		VertexBufferWrapper::~VertexBufferWrapper();
		void VertexBufferWrapper::SetVertexBuffer(IDirect3DVertexBuffer9** _VertexBuffer);
		IDirect3DVertexBuffer9** VertexBufferWrapper::GetVertexBuffer();
	private:
		IDirect3DVertexBuffer9** VertexBuffer;
	};

}

#endif