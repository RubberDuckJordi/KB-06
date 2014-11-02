#ifndef _PENGINE_TEXTUREWRAPPER_H_
#define _PENGINE_TEXTUREWRAPPER_H_

#include <d3dx9.h>

/*
Wrapper to wrap directX specific implementation

CLASS IS DEPRECATED BY Resource/BinaryData
*/

namespace pengine
{
	class TextureWrapper
	{
	public:
		TextureWrapper(LPDIRECT3DTEXTURE9* _texture);
		~TextureWrapper();
		void SetTexture(LPDIRECT3DTEXTURE9* _texture);
		LPDIRECT3DTEXTURE9* GetTexture();
	private:
		LPDIRECT3DTEXTURE9* texture;
	};
}
#endif