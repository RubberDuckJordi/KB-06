#include "TextureWrapper.h"

pengine::TextureWrapper::TextureWrapper(LPDIRECT3DTEXTURE9* _texture)
{
	texture = _texture;
}

pengine::TextureWrapper::~TextureWrapper()
{

}

void pengine::TextureWrapper::SetTexture(LPDIRECT3DTEXTURE9* _texture)
{
	texture = _texture;
}

LPDIRECT3DTEXTURE9* pengine::TextureWrapper::GetTexture()
{
	return texture;
}