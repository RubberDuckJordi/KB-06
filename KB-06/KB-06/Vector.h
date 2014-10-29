#ifndef _PENGINE_VECTOR_H_
#define _PENGINE_VECTOR_H_

namespace pengine
{
	class Vector
	{
	public:
		float x, y, z;
		Vector();

		Vector(float px, float py, float pz);

		Vector(const Vector &pv);

		Vector(const float* &pv);

		Vector& operator=(const Vector &pv);

		inline void Set(float px, float py, float pz);
		bool operator>(const Vector &pv);

		float operator[](int index)const;
		float& operator[](int index);

		Vector operator+(Vector pv)const;
		Vector operator-(Vector& pv)const;
		Vector operator*(float pT)const;

		void Normalize();
		float Dot(Vector pV)const;
		Vector Cross(Vector pV)const;
		Vector UnitCross(Vector pV)const;
	};
}
#endif