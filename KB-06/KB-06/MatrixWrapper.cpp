#ifndef _MATRIXWRAPPER_CPP_
#define _MATRIXWRAPPER_CPP_

#include <d3dx9.h>



class MatrixWrapper
{
public:
	MatrixWrapper::MatrixWrapper(D3DXMATRIX newMatrix)
	{
		matrix = newMatrix;
	}

	MatrixWrapper::~MatrixWrapper()
	{

	}

	void MatrixWrapper::SetMatrix(D3DXMATRIX newMatrix)
	{
		matrix = newMatrix;
	}

	D3DXMATRIX MatrixWrapper::GetMatrix()
	{
		return matrix;
	}
private:
	D3DXMATRIX matrix;

};

#endif