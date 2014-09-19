#ifndef _MATRIXWRAPPER_H_
#define _MATRIXWRAPPER_H_

#include <d3dx9.h>


namespace Renderer
{
	class MatrixWrapper
	{
	public:
		MatrixWrapper::MatrixWrapper(D3DXMATRIX newMatrix);
		MatrixWrapper::~MatrixWrapper();
		void MatrixWrapper::SetMatrix(D3DXMATRIX newMatrix);
		D3DXMATRIX MatrixWrapper::GetMatrix();
	private:
		D3DXMATRIX matrix;

	};

}

#endif