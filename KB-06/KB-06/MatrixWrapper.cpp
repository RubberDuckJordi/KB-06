#include "MatrixWrapper.h"



    Renderer::MatrixWrapper::MatrixWrapper(D3DXMATRIX newMatrix)
	{
		matrix = newMatrix;
	}

	Renderer::MatrixWrapper::~MatrixWrapper()
	{

	}

	void Renderer::MatrixWrapper::SetMatrix(D3DXMATRIX newMatrix)
	{
		matrix = newMatrix;
	}

	D3DXMATRIX Renderer::MatrixWrapper::GetMatrix()
	{
		return matrix;
	}



