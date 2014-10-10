#ifndef _VECTOR3_H_
#define _VECTOR3_H_

#include <math.h>
namespace pengine
{
	class Vector3
	{
	public:
		float x, y, z;
		//default constructor
		Vector3(float X = 0, float Y = 0, float Z = 0);
		~Vector3();

		//add two vectors
		Vector3 operator+(const Vector3 &vec) const;

		//subtract two vectors
		Vector3 operator-(const Vector3 &vec) const;

		//
		Vector3 operator*(const Vector3 &vec) const;

		float GetMagnitude();

		float GetXAngle();

		float GetZAngle();

		float GetYAngle();

		static float CalculateAngle(Vector3& v1, Vector3& v2);

		//normalize given vector
		static Vector3 normalize(Vector3 &vec1);

		//calculate and return dot product
		static float dot(Vector3 &vec1, Vector3 &vec2);

		//calculate and return cross product
		static Vector3 cross(Vector3 &vec1, Vector3 &vec2);
	};
}
#endif