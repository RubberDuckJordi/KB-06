#include "TextureWrapper.h"

namespace pengine
{
	TextureWrapper::TextureWrapper(LPDIRECT3DTEXTURE9* _texture)
	{
		texture = _texture;
	}

	TextureWrapper::~TextureWrapper()
	{
		delete texture;
	}

	void TextureWrapper::SetTexture(LPDIRECT3DTEXTURE9* _texture)
	{
		texture = _texture;
	}

	LPDIRECT3DTEXTURE9* TextureWrapper::GetTexture()
	{
		return texture;
	}
}