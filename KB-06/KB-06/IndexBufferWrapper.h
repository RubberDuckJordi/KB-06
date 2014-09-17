#ifndef _INDEXBUFFERWRAPPER_H_
#define _INDEXBUFFERWRAPPER_H_

#include <d3dx9.h>

namespace Renderer
{
	class IndexBufferWrapper
	{
	public:
		IndexBufferWrapper(IDirect3DIndexBuffer9** _IndexBuffer);
		~IndexBufferWrapper();
		void SetIndexBuffer(IDirect3DIndexBuffer9** _IndexBuffer);
		IDirect3DIndexBuffer9** GetIndexBuffer();


	private:
		IDirect3DIndexBuffer9** IndexBuffer;
	};
}

#endif