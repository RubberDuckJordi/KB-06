#ifndef _PENGINE_QUATERNION_H_
#define _PENGINE_QUATERNION_H_

#define MINFLOAT 1.17549435E-38F

#include "PengineDefinitions.h"

namespace pengine
{
	template <typename T>
	class Quaternion {
	public:
		T data[4];
		Quaternion(void)
		{
			memset(data, 0, 4 * sizeof(T));
		};
		Quaternion(const Quaternion<T> &pq)
		{
			memcpy(data, pq.data, 4 * sizeof(T));
		};
		Quaternion(const T* pT)
		{
			memcpy(data, pT, 4 * sizeof(T));
		};
		void Zero(void)
		{
			memset(data, 0, 4 * sizeof(T));
		};
		T operator[](int index)const
		{
			return data[index];
		};
		T& operator[](int index)
		{
			return data[index];
		};
		Quaternion<T>& operator=(const Quaternion<T> &pq)
		{
			memcpy(data, pq.data, 4 * sizeof(T));
			return *this;
		};
		Quaternion<T> operator+(Quaternion<T> pq)
		{
			T rdata[4];
			rdata[0] = pq.data[0] + data[0];
			rdata[1] = pq.data[1] + data[1];
			rdata[2] = pq.data[2] + data[2];
			rdata[3] = pq.data[3] + data[3];
			return Quaternion<T>(rdata);
		};
		Quaternion<T> operator*(Quaternion<T> pq);//wasn't implemented, unused?
		Quaternion<T> operator*(T pT)
		{
			T rdata[4];
			rdata[0] = pT * data[0];
			rdata[1] = pT * data[1];
			rdata[2] = pT * data[2];
			rdata[3] = pT * data[3];
			return Quaternion<T>(rdata);
		};
		T Dot(Quaternion<T> &pq)
		{
			return ((data[0] * pq.data[0]) + (data[1] * pq.data[1]) + (data[2] * pq.data[2]) + (data[3] * pq.data[3]));
		};
		Quaternion<T> Slerp(T pT, Quaternion<T> &pq)
		{
			//We calculate the angle spread between both quaternions
			T AngleCos = pq.Dot(*this);
			T Angle = qACos(AngleCos); //see the function ACos above

			if (Angle < MINFLOAT)
			{
				return Quaternion<T>(*this);
			}
			//We calculate the interpolated angle and deduce the resulting quaternion
			T InvAngleSin = (T)(1.0f / sin(Angle));

			T Coeff0 = sin((1 - pT) * Angle) * InvAngleSin;
			T Coeff1 = sin(pT * Angle) * InvAngleSin;
			return Quaternion<T>((*this * Coeff0) + (pq * Coeff1));
		};
	private:
		float qACos(float pValue)
		{
			if (-1.0f < pValue)
			{
				if (pValue < 1.0f)
				{
					return (float)acos(pValue);
				}
				else
				{
					return 0.0f;
				}
			}
			else
			{
				return M_PI;
			}
		};
	};
}
#endif