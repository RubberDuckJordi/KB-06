
#include "TextureWrapper.h"


Renderer::TextureWrapper::TextureWrapper(LPDIRECT3DTEXTURE9* _texture)
{
	texture = _texture;
};

Renderer::TextureWrapper::~TextureWrapper()
{

};

void Renderer::TextureWrapper::SetTexture(LPDIRECT3DTEXTURE9* _texture)
{
	texture = _texture;
};

LPDIRECT3DTEXTURE9* Renderer::TextureWrapper::GetTexture()
{
	return texture;
};

