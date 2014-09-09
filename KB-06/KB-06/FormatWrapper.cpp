#ifndef _FORMATWRAPPER_CPP_
#define _FORMATWRAPPER_CPP_

#include <d3dx9.h>



class FormatWrapper
{
public:
	FormatWrapper::FormatWrapper(D3DFORMAT newFormat)
	{
		format = newFormat;
	}

	FormatWrapper::~FormatWrapper()
	{

	}

	void FormatWrapper::setFormat(D3DFORMAT newFormat)
	{
		format = newFormat;
	}

	D3DFORMAT FormatWrapper::getFormat()
	{
		return format;
	}
private:
	D3DFORMAT format;

};

#endif