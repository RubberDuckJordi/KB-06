#ifndef _TEXTUREWRAPPER_CPP_
#define _TEXTUREWRAPPER_CPP_

#include <d3dx9.h>

class TextureWrapper
{
public:
	TextureWrapper::TextureWrapper(LPDIRECT3DTEXTURE9 _texture)
	{
		texture = _texture;
	};

	TextureWrapper::~TextureWrapper()
	{

	};

	void TextureWrapper::SetTexture(LPDIRECT3DTEXTURE9 _texture)
	{
		texture = _texture;
	};

	LPDIRECT3DTEXTURE9 TextureWrapper::GetTexture()
	{
		return texture;
	};

private:
	LPDIRECT3DTEXTURE9 texture;
};

#endif