#ifndef _PENGINE_VECTOR_H_
#define _PENGINE_VECTOR_H_

namespace pengine
{
	template <typename T>
	class Vector
	{
	public:
		T x, y, z;
		Vector(void) : x(0), y(0), z(0)
		{
		};
		Vector(T px, T py, T pz) : x(px), y(py), z(pz)
		{
		};
		Vector(const Vector<T> &pv) :x(pv.x), y(pv.y), z(pv.z)
		{
		};
		Vector(const T* &pv)
		{
			x = pv[0];
			y = pv[1];
			z = pv[2];
		};

		Vector<T>& operator=(const Vector<T> &pv)
		{
			x = pv.x;
			y = pv.y;
			z = pv.z;
			return *this;
		};

		inline void Set(T px, T py, T pz)
		{
			x = px;
			y = py;
			z = pz;
		};
		bool operator>(const Vector<T> &pv)
		{
			return (x + y) > (pv.x + pv.y);
		};

		T operator[](int index)const
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
		};
		T& operator[](int index)
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
		};

		Vector<T> operator+(Vector<T> pv)const
		{
			return Vector<T>((T)(x + pv.x), (T)(y + pv.y), (T)(z + pv.z));
		};
		Vector<T> operator-(Vector<T>& pv)const
		{
			return Vector<T>((T)(x - pv.x), (T)(y - pv.y), (T)(z - pv.z));
		};
		Vector<T> operator*(T pT)const
		{
			return Vector<T>((T)(pT * x), (T)(pT * y), (T)(pT * z));
		};

		void Normalize(void)
		{
			Vector<T> pv((T)(x*x), (T)(y*y), (T)(z*z));
			T fLength = (T)(1.0f / (float)(pv.x + pv.y + pv.z));
			if (fLength < 1e-08)
			{
				return;
			}
			x = (T)(pv.x * fLength);
			y = (T)(pv.y * fLength);
			z = (T)(pv.z * fLength);
		};
		T Dot(Vector<T> pV)const
		{
			return (T)(x*pV.x + y*pV.y + z*pV.z);
		};
		Vector<T> Cross(Vector<T> pV)const
		{
			return Vector<T>((T)(y * pV.z - z * pV.y), (T)(z * pV.x - x * pV.z), (T)(x * pV.y - y * pV.x));
		};
		Vector<T> UnitCross(Vector<T> pV)const
		{
			Vector<T> pR((T)(y * pV.z - z * pV.y), (T)(z * pV.x - x * pV.z), (T)(x * pV.y - y * pV.x));
			pR.Normalize();
			return pR;
		};
	};
	typedef Vector<float> vector;
}
#endif