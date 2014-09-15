#ifndef _POOLWRAPPER_CPP_
#define _POOLWRAPPER_CPP_

#include <d3dx9.h>



class PoolWrapper
{
public:
	PoolWrapper::PoolWrapper(D3DPOOL newPool)
	{
		pool = newPool;
	}

	PoolWrapper::~PoolWrapper()
	{

	}

	void PoolWrapper::SetPool(D3DPOOL newPool)
	{
		pool = newPool;
	}

	D3DPOOL PoolWrapper::GetPool()
	{
		return pool;
	}
private:
	D3DPOOL pool;

};

#endif