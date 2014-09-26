#include "VertexBufferWrapper.h"

pengine::VertexBufferWrapper::VertexBufferWrapper(IDirect3DVertexBuffer9** _VertexBuffer)
{
	VertexBuffer = _VertexBuffer;
}

pengine::VertexBufferWrapper::~VertexBufferWrapper()
{

}

void pengine::VertexBufferWrapper::SetVertexBuffer(IDirect3DVertexBuffer9** _VertexBuffer)
{
	VertexBuffer = _VertexBuffer;
}

IDirect3DVertexBuffer9** pengine::VertexBufferWrapper::GetVertexBuffer()
{
	return VertexBuffer;
}

