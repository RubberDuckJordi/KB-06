#include "VertexBufferWrapper.h"

	Renderer::VertexBufferWrapper::VertexBufferWrapper(IDirect3DVertexBuffer9** _VertexBuffer)
	{
		VertexBuffer = _VertexBuffer;
	};

	Renderer::VertexBufferWrapper::~VertexBufferWrapper()
	{

	};


	void Renderer::VertexBufferWrapper::SetVertexBuffer(IDirect3DVertexBuffer9** _VertexBuffer)

	{
		VertexBuffer = _VertexBuffer;
	};


	IDirect3DVertexBuffer9** Renderer::VertexBufferWrapper::GetVertexBuffer()

	{
		return VertexBuffer;
	};

