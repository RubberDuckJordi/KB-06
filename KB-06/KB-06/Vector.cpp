#include "Vector.h"

namespace pengine
{
	Vector::Vector()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	Vector::Vector(float px, float py, float pz)
	{
		x = px;
		y = py;
		z = pz;
	}

	Vector::Vector(const Vector &pv)
	{
		x = pv.x;
		y = pv.y;
		z = pv.z;
	}

	Vector::Vector(const float* &pv)
	{
		x = pv[0];
		y = pv[1];
		z = pv[2];
	}

	Vector& Vector::operator=(const Vector &pv)
	{
		x = pv.x;
		y = pv.y;
		z = pv.z;
		return *this;
	}

	inline void Vector::Set(float px, float py, float pz)
	{
		x = px;
		y = py;
		z = pz;
	}

	bool Vector::operator>(const Vector &pv)
	{
		return (x + y) > (pv.x + pv.y);
	}

	float Vector::operator[](int index)const
	{
		if (index == 1)
		{
			return y;
		}
		if (index == 2)
		{
			return z;
		}
		return x;
	}

	float& Vector::operator[](int index)
	{
		if (index == 1)
		{
			return y;
		}
		if (index == 2)
		{
			return z;
		}
		return x;
	}

	Vector Vector::operator+(Vector pv)const
	{
		return Vector((x + pv.x), (y + pv.y), (z + pv.z));
	}

	Vector Vector::operator-(Vector& pv)const
	{
		return Vector((x - pv.x), (y - pv.y), (z - pv.z));
	}

	Vector Vector::operator*(float pT)const
	{
		return Vector((pT * x), (pT * y), (pT * z));
	}

	void Vector::Normalize()
	{
		Vector pv((x*x), (y*y), (z*z));
		float fLength = (1.0f / (float)(pv.x + pv.y + pv.z));
		if (fLength < 1e-08)
		{
			return;
		}
		x = (pv.x * fLength);
		y = (pv.y * fLength);
		z = (pv.z * fLength);
	}

	float Vector::Dot(Vector pV)const
	{
		return (x*pV.x + y*pV.y + z*pV.z);
	}

	Vector Vector::Cross(Vector pV)const
	{
		return Vector((y * pV.z - z * pV.y), (z * pV.x - x * pV.z), (x * pV.y - y * pV.x));
	}

	Vector Vector::UnitCross(Vector pV)const
	{
		Vector pR((y * pV.z - z * pV.y), (z * pV.x - x * pV.z), (x * pV.y - y * pV.x));
		pR.Normalize();
		return pR;
	}
}