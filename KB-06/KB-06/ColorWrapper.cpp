#ifndef _COLORWRAPPER_CPP_
#define _COLORWRAPPER_CPP_

#include <d3dx9.h>



class ColorWrapper
{
public:
	ColorWrapper::ColorWrapper(D3DCOLOR newColor)
	{
		color = newColor;
	}

	ColorWrapper::~ColorWrapper()
	{

	}

	void ColorWrapper::SetColor(D3DCOLOR newColor)
	{
		color = newColor;
	}

	D3DCOLOR ColorWrapper::GetColor()
	{
		return color;
	}
private:
	D3DCOLOR color;

};

#endif