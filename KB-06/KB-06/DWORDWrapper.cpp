
#ifndef _DWORDWRAPPER_CPP_
#define _DWORDWRAPPER_CPP_

#include <d3dx9.h>

class DWORDWrapper
{
public:
	DWORDWrapper::DWORDWrapper(DWORD _dword)
	{
		dword = _dword;
	};

	DWORDWrapper::~DWORDWrapper()
	{

	};

	void DWORDWrapper::GetDWORD(DWORD _dword)
	{
		dword = _dword;
	};

	DWORD DWORDWrapper::GetDWORD()
	{
		return dword;
	};

private:
	DWORD dword;
};


#endif