#include "RenderMatrix.h"
#include <d3dx9.h>
#include "PengineDefinitions.h"
#include "LoggerPool.h"
#include <sstream>

namespace pengine
{
	RenderMatrix::RenderMatrix()
	{
		theMatrix = new PEngineMatrix();
		theMatrix->_11 = 1.0f;
		theMatrix->_22 = 1.0f;
		theMatrix->_33 = 1.0f;
		theMatrix->_44 = 1.0f;
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

	void RenderMatrix::CreateLookAtMatrix(Vector3 pos, Vector3 lookAtPos, Vector3 upVector, PEngineMatrix* receiver)
	{
		Vector3 zaxis = Vector3::normalize(lookAtPos - pos);
		Vector3 xaxis = Vector3::normalize(Vector3::cross(upVector, zaxis));
		Vector3 yaxis = Vector3::cross(zaxis, xaxis);

		receiver->_11 = xaxis.x;
		receiver->_21 = xaxis.y;
		receiver->_31 = xaxis.z;
		receiver->_41 = -Vector3::dot(xaxis, pos);

		receiver->_12 = yaxis.x;
		receiver->_22 = yaxis.y;
		receiver->_32 = yaxis.z;
		receiver->_42 = -Vector3::dot(yaxis, pos);

		receiver->_13 = zaxis.x;
		receiver->_23 = zaxis.y;
		receiver->_33 = zaxis.z;
		receiver->_43 = -Vector3::dot(zaxis, pos);

		receiver->_14 = 0.0f;
		receiver->_24 = 0.0f;
		receiver->_34 = 0.0f;
		receiver->_44 = 1.0f;
	}

	void RenderMatrix::MultiplyMatrices(PEngineMatrix* m1, PEngineMatrix* m2, PEngineMatrix* receiver)
	{
		D3DXMatrixMultiply((D3DXMATRIX *)receiver, (D3DXMATRIX *)m1, (D3DXMATRIX *)m2);
	}

	void RenderMatrix::PrintMatrix(PEngineMatrix* matrix)
	{
		std::ostringstream oss;
		oss.precision(6);
		oss << std::fixed;//make sure the decimal notation fills the precision... Like so: 10.23000

		oss << "The content of the matrix is:"
			<< "\n[" << matrix->_11 << ",\t" << matrix->_12 << ",\t" << matrix->_13 << ",\t" << matrix->_14 << "]"
			<< "\n[" << matrix->_21 << ",\t" << matrix->_22 << ",\t" << matrix->_23 << ",\t" << matrix->_24 << "]"
			<< "\n[" << matrix->_31 << ",\t" << matrix->_32 << ",\t" << matrix->_33 << ",\t" << matrix->_34 << "]"
			<< "\n[" << matrix->_41 << ",\t" << matrix->_42 << ",\t" << matrix->_43 << ",\t" << matrix->_44 << "]";

		LoggerPool::GetInstance().GetLogger()->Log(Logger::DEBUG, oss.str());
	}

}