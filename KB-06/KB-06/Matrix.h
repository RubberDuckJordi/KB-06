#ifndef _PENGINE_MATRIX_H_
#define _PENGINE_MATRIX_H_

#include "Vector.h"
#include "Vertex.h"
#include "Types.h"
#include "Vector3.h"//same functionality as Vector.h, different implementation
#include <d3dx9.h>//ugly, might as well go fix this...
#include "PengineDefinitions.h"
#include "LoggerPool.h"
#include <sstream>

namespace pengine
{
	class Matrix
	{
	public:
		float data[16];
		Matrix()
		{
			memset(data, 0, 16 * sizeof(float));
		};
		Matrix(const Matrix &pm)
		{
			memcpy(data, pm.data, 16 * sizeof(float));
		};
		Matrix(const float* pT)
		{
			memcpy(data, pT, 16 * sizeof(float));
		};
		void Zero()
		{
			memset(data, 0, 16 * sizeof(float));
		};
		void Identity()
		{
			memset(data, 0, 16 * sizeof(float));
			data[0] = 1;
			data[5] = 1;
			data[10] = 1;
			data[15] = 1;
		};
		Matrix& operator=(const Matrix &pm)
		{
			memcpy(data, pm.data, 16 * sizeof(float));
			return *this;
		};
		Matrix operator+(Matrix pm)
		{
			float Rdata[16];
			for (k = 0; k < 16; k++)
			{
				Rdata[k] = data[k] + pm.data[k];
			}
			return Matrix(Rdata);
		};
		Matrix operator-(Matrix pm)
		{
			float Rdata[16];
			for (k = 0; k < 16; k++)
			{
				Rdata[k] = data[k] - pm.data[k];
			}
			return Matrix(Rdata);
		};
		Matrix operator*(Matrix pm)
		{
			float Rdata[16];
			for (row = 0; row < 16; row += 4)
			{
				for (col = 0; col < 4; col++)
				{
					l = 0;
					Rdata[row + col] = 0;
					for (k = 0; k < 4; k++, l += 4)
					{
						Rdata[row + col] += data[row + k] * pm.data[l + col];
					}
				}
			}
			return Matrix(Rdata);
		};
		Matrix& operator*=(Matrix &pm)
		{
			float Rdata[16];
			for (row = 0; row < 16; row += 4)
			{
				for (col = 0; col < 4; col++)
				{
					l = 0;
					Rdata[row + col] = 0;
					for (k = 0; k < 4; k++, l += 4)
					{
						Rdata[row + col] += data[row + k] * pm.data[l + col];
					}
				}
			}
			memcpy(data, Rdata, 16 * sizeof(float));
			return *this;
		};
		Matrix operator*(float pT)
		{
			float Rdata[16];
			memcpy(Rdata, data, 16 * sizeof(float));
			for (k = 0; k < 16; k++)
			{
				Rdata[k] *= pT;
			}
			return Matrix(Rdata);
		};
		Vector operator*(const Vector& pV)
		{
			float vdata[4], pvdata[4];
			pvdata[0] = pV.x;
			pvdata[1] = pV.y;
			pvdata[2] = pV.z;
			pvdata[3] = 0;
			for (col = 0; col < 4; col++)
			{
				vdata[row] = 0;
				k = 0;
				for (row = 0; row < 4; row++, k += 4)
				{
					vdata[col] += data[k + col] * pvdata[row];
				}
			}
			return Vector(vdata[0], vdata[1], vdata[2]);
		};

		Vertex operator*(const Vertex& pV)
		{
			float vdata[4], pvdata[4];

			pvdata[0] = pV.x;
			pvdata[1] = pV.y;
			pvdata[2] = pV.z;
			pvdata[3] = 1.0f;

			for (col = 0; col < 4; col++)
			{
				k = 0;
				vdata[col] = 0;
				for (row = 0; row < 4; row++, k += 4)
				{
					vdata[col] += data[k + col] * pvdata[row];
				}
			}

			return{ vdata[0], vdata[1], vdata[2], pV.tu, pV.tv };
		};

		float operator[](int index)const
		{
			return data[index];
		};
		float& operator[](int index)
		{
			return data[index];
		};

		float _fastcall Index(int pRow, int pCol)const
		{
			return data[(pRow << 2) + pCol];
		};
		float operator()(int pRow, int pCol)const
		{
			return data[(pRow << 2) + pCol];
		};
		float& operator()(int pRow, int pCol)
		{
			return data[(pRow << 2) + pCol];
		};
		Vector GetRow(int index)
		{
			index <<= 2;
			return Vector(data[index++], data[index++], data[index]);
		};
		Vector GetColumn(int index)
		{
			return Vector(data[index], data[index + 4], data[index + 8]);
		};
		void ScalingMatrix(const Vector &pvT)
		{
			Identity();
			data[0] = pvT.x;
			data[5] = pvT.y;
			data[10] = pvT.z;
		};

		void TranslationMatrix(const std::array<float, 3> &pAT)
		{
			Identity();
			data[12] = pAT[0];
			data[13] = pAT[1];
			data[14] = pAT[2];
		};

		void TranslationMatrix(Vertex &pAT)
		{
			Identity();
			data[12] = pAT.x;
			data[13] = pAT.y;
			data[14] = pAT.z;
		};
		void QuaternionMatrix(float &x, float &y, float &z, float &w)
		{
			float xx = x*x; float yy = y*y; float zz = z*z;
			float xy = x*y; float xz = x*z; float yz = y*z;
			float wx = w*x; float wy = w*y; float wz = w*z;

			data[0] = 1 - 2 * (yy + zz);
			data[1] = 2 * (xy - wz);
			data[2] = 2 * (xz + wy);

			data[4] = 2 * (xy + wz);
			data[5] = 1 - 2 * (xx + zz);
			data[6] = 2 * (yz - wx);

			data[8] = 2 * (xz - wy);
			data[9] = 2 * (yz + wx);
			data[10] = 1 - 2 * (xx + yy);

			data[3] = data[7] = data[11] = 0.0f;
			data[12] = data[13] = data[14] = 0.0f;
			data[15] = 1.0f;
		};

		static void CreateMatrix(float x, float y, float z, float yaw, float pitch, float roll, float scaleX, float scaleY, float scaleZ, Matrix* receiver)
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

			(*receiver)[0] = result._11;
			(*receiver)[1] = result._12;
			(*receiver)[2] = result._13;
			(*receiver)[3] = result._14;
			(*receiver)[4] = result._21;
			(*receiver)[5] = result._22;
			(*receiver)[6] = result._23;
			(*receiver)[7] = result._24;
			(*receiver)[8] = result._31;
			(*receiver)[9] = result._32;
			(*receiver)[10] = result._33;
			(*receiver)[11] = result._34;
			(*receiver)[12] = result._41;
			(*receiver)[13] = result._42;
			(*receiver)[14] = result._43;
			(*receiver)[15] = result._44;
		};
		static void CreateLookAtMatrix(Vector3 pos, Vector3 lookAtPos, Vector3 upVector, Matrix* receiver)
		{
			Vector3 zaxis = Vector3::normalize(lookAtPos - pos);
			Vector3 xaxis = Vector3::normalize(Vector3::cross(upVector, zaxis));
			Vector3 yaxis = Vector3::cross(zaxis, xaxis);

			(*receiver)[0] = xaxis.x;
			(*receiver)[4] = xaxis.y;
			(*receiver)[8] = xaxis.z;
			(*receiver)[12] = -Vector3::dot(xaxis, pos);

			(*receiver)[1] = yaxis.x;
			(*receiver)[5] = yaxis.y;
			(*receiver)[9] = yaxis.z;
			(*receiver)[13] = -Vector3::dot(yaxis, pos);

			(*receiver)[2] = zaxis.x;
			(*receiver)[6] = zaxis.y;
			(*receiver)[10] = zaxis.z;
			(*receiver)[14] = -Vector3::dot(zaxis, pos);

			(*receiver)[3] = 0.0f;
			(*receiver)[7] = 0.0f;
			(*receiver)[11] = 0.0f;
			(*receiver)[15] = 1.0f;
		};
		static void PrintMatrix(Matrix* matrix)
		{
			std::ostringstream oss;
			oss.precision(6);
			oss << std::fixed;//make sure the decimal notation fills the precision... Like so: 10.23000

			oss << "The content of the matrix is:"
				<< "\n[" << (*matrix)[0] << ",\t" << (*matrix)[1] << ",\t" << (*matrix)[2] << ",\t" << (*matrix)[3] << "]"
				<< "\n[" << (*matrix)[4] << ",\t" << (*matrix)[5] << ",\t" << (*matrix)[6] << ",\t" << (*matrix)[7] << "]"
				<< "\n[" << (*matrix)[8] << ",\t" << (*matrix)[9] << ",\t" << (*matrix)[10] << ",\t" << (*matrix)[11] << "]"
				<< "\n[" << (*matrix)[12] << ",\t" << (*matrix)[13] << ",\t" << (*matrix)[14] << ",\t" << (*matrix)[15] << "]";

			Logger* l = LoggerPool::GetInstance().GetLogger();
			l->Log(Logger::DEBUG, oss.str());
			l = NULL;
		};

	private:
		int k, l, row, col;
	};
}
#endif