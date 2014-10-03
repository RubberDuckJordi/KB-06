#include "VertexBufferWrapper.h"

namespace pengine
{
	VertexBufferWrapper::VertexBufferWrapper(IDirect3DVertexBuffer9** _VertexBuffer)
	{
		VertexBuffer = _VertexBuffer;
	}

	VertexBufferWrapper::~VertexBufferWrapper()
	{

	}

	void VertexBufferWrapper::SetVertexBuffer(IDirect3DVertexBuffer9** _VertexBuffer)
	{
		VertexBuffer = _VertexBuffer;
	}

	IDirect3DVertexBuffer9** VertexBufferWrapper::GetVertexBuffer()
	{
		return VertexBuffer;
	}
}