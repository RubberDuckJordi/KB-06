#ifndef _TEXTUREWRAPPER_H_
#define _TEXTUREWRAPPER_H_

#include <d3dx9.h>

namespace Renderer
{
	class TextureWrapper
	{
	public:
		TextureWrapper::TextureWrapper(LPDIRECT3DTEXTURE9* _texture);
		TextureWrapper::~TextureWrapper();
		void TextureWrapper::SetTexture(LPDIRECT3DTEXTURE9* _texture);
		LPDIRECT3DTEXTURE9* TextureWrapper::GetTexture();
	private:
		LPDIRECT3DTEXTURE9* texture;
	};

}

#endif