#include "stdafx.h"
#include "RenderMatrix.h"
#include <d3dx9.h>
#include "PengineDefinitions.h"

RenderMatrix::RenderMatrix()
{
	theMatrix = new PEngineMatrix();
}


RenderMatrix::~RenderMatrix()
{
	delete theMatrix;
}

void RenderMatrix::CreateMatrix(float x, float y, float z, float yaw, float pitch, float roll, float scaleX, float scaleY, float scaleZ, PEngineMatrix* matrix)
{
	//If we want to do this right, this method should do the math using our own functions, not the ones of DirectX, that is out our scope however...
	D3DXMATRIX rotation;
	D3DXMATRIX scale;
	D3DXMATRIX result;

	D3DXMatrixTranslation(&result, x, y, z);


	if (yaw != 0 || pitch != 0 || roll != 0)//Is it more efficient to check if the rotation matrix is needed or to just make it?
	{
		D3DXMatrixRotationYawPitchRoll(&rotation, RADIANS(yaw), RADIANS(pitch), RADIANS(roll));
		D3DXMatrixMultiply(&result, &rotation, &result);
	}

	if (scaleX != 1 || scaleY != 1 || scaleZ != 1)//Is it more efficient to check if the scaling matrix is needed or to just make it?
	{
		D3DXMatrixScaling(&scale, scaleX, scaleY, scaleZ);
		D3DXMatrixMultiply(&result, &scale, &result);
	}
	matrix->_11 = result._11;
	matrix->_12 = result._12;
	matrix->_13 = result._13;
	matrix->_14 = result._14;
	matrix->_21 = result._21;
	matrix->_22 = result._22;
	matrix->_23 = result._23;
	matrix->_24 = result._24;
	matrix->_31 = result._31;
	matrix->_32 = result._32;
	matrix->_33 = result._33;
	matrix->_34 = result._34;
	matrix->_41 = result._41;
	matrix->_42 = result._42;
	matrix->_43 = result._43;
	matrix->_44 = result._44;
}
