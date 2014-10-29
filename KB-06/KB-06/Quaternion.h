#ifndef _PENGINE_QUATERNION_H_
#define _PENGINE_QUATERNION_H_

#define MINFLOAT 1.17549435E-38F

#include "PengineDefinitions.h"

namespace pengine
{
	class Quaternion {
	public:
		float data[4];
		Quaternion();
		Quaternion(const Quaternion &pq);
		Quaternion(const float* pT);
		void Zero();
		float operator[](int index)const;
		float& operator[](int index);
		Quaternion& operator=(const Quaternion &pq);
		Quaternion operator+(Quaternion pq);
		Quaternion operator*(Quaternion pq);//wasn't implemented, unused?
		Quaternion operator*(float pT);
		float Dot(Quaternion &pq);
		Quaternion Slerp(float pT, Quaternion &pq);
	private:
		float qACos(float pValue);
	};
}
#endif