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

	void ColorWrapper::setColor(D3DCOLOR newColor)
	{
		color = newColor;
	}

	D3DCOLOR ColorWrapper::getColor()
	{
		return color;
	}
private:
	D3DCOLOR color;

};

#endif