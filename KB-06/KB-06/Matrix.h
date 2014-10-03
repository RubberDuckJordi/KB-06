#ifndef _PENGINE_MATRIX_H_
#define _PENGINE_MATRIX_H_

#include "Vector.h"
#include "Array.h"
#include "Vertex.h"

namespace pengine
{
	template <typename T>
	class Matrix
	{
	public:
		T data[16];
		Matrix(void)
		{
			memset(data, 0, 16 * sizeof(T));
		};
		Matrix(const Matrix<T> &pm)
		{
			memcpy(data, pm.data, 16 * sizeof(T));
		};
		Matrix(const T* pT)
		{
			memcpy(data, pT, 16 * sizeof(T));
		};
		void Zero(void)
		{
			memset(data, 0, 16 * sizeof(T));
		};
		void Identity(void)
		{
			memset(data, 0, 16 * sizeof(T));
			data[0] = (T)1;
			data[5] = (T)1;
			data[10] = (T)1;
			data[15] = (T)1;
		};
		Matrix<T>& operator=(const Matrix<T> &pm)
		{
			memcpy(data, pm.data, 16 * sizeof(T));
			return *this;
		};
		Matrix<T> operator+(Matrix<T> pm)
		{
			T Rdata[16];
			for (k = 0; k < 16; k++)
			{
				Rdata[k] = data[k] + pm.data[k];
			}
			return Matrix<T>(Rdata);
		};
		Matrix<T> operator-(Matrix<T> pm)
		{
			T Rdata[16];
			for (k = 0; k < 16; k++)
			{
				Rdata[k] = data[k] - pm.data[k];
			}
			return Matrix<T>(Rdata);
		};
		Matrix<T> operator*(Matrix<T> pm)
		{
			T Rdata[16];
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
			return Matrix<T>(Rdata);
		};
		Matrix<T>& operator*=(Matrix<T> &pm)
		{
			T Rdata[16];
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
			memcpy(data, Rdata, 16 * sizeof(T));
			return *this;
		};
		Matrix<T> operator*(T pT)
		{
			T Rdata[16];
			memcpy(Rdata, data, 16 * sizeof(T));
			for (k = 0; k < 16; k++)
			{
				Rdata[k] *= pT;
			}
			return Matrix<T>(Rdata);
		};
		Vector<T> operator*(const Vector<T>& pV)
		{
			T vdata[4], pvdata[4];
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
			return Vector<T>(vdata);
		};

		Vertex operator*(const Vertex& pV)
		{
			T vdata[4], pvdata[4];

			//memcpy(pvdata, pV.data, 3 * sizeof(T));
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
			/*Vertex theVertex;
			theVertex.x = vdata[0];
			theVertex.y = vdata[1];
			theVertex.z = vdata[2];*/
			return{ vdata[0], vdata[1], vdata[2] };
		};

		T operator[](int index)const
		{
			return data[index];
		};
		T& operator[](int index)
		{
			return data[index];
		};

		T _fastcall Index(int pRow, int pCol)const
		{
			return data[(pRow << 2) + pCol];
		};
		T operator()(int pRow, int pCol)const
		{
			return data[(pRow << 2) + pCol];
		};
		T& operator()(int pRow, int pCol)
		{
			return data[(pRow << 2) + pCol];
		};
		Vector<T> GetRow(int index)
		{
			index <<= 2;
			return Vector<T>(data[index++], data[index++], data[index]);
		};
		Vector<T> GetColumn(int index)
		{
			return Vector<T>(data[index], data[index + 4], data[index + 8]);
		};
		void ScalingMatrix(const Vector<T> &pvT)
		{
			Identity();
			data[0] = pvT.x;
			data[5] = pvT.y;
			data[10] = pvT.z;
		};

		void TranslationMatrix(const Array<T, 3> &pAT)
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
		void QuaternionMatrix(T &x, T &y, T &z, T &w)
		{
			T xx = x*x; T yy = y*y; T zz = z*z;
			T xy = x*y; T xz = x*z; T yz = y*z;
			T wx = w*x; T wy = w*y; T wz = w*z;

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

	private:
		int k, l, row, col;
	};
	typedef Matrix<float> matrix;
}
#endif