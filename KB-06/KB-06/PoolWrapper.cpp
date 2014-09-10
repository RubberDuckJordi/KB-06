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

	void PoolWrapper::setPool(D3DPOOL newPool)
	{
		pool = newPool;
	}

	D3DPOOL PoolWrapper::getPool()
	{
		return pool;
	}
private:
	D3DPOOL pool;

};

#endif