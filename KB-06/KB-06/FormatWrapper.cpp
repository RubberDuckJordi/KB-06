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

	void FormatWrapper::SetFormat(D3DFORMAT newFormat)
	{
		format = newFormat;
	}

	D3DFORMAT FormatWrapper::GetFormat()
	{
		return format;
	}
private:
	D3DFORMAT format;

};

#endif