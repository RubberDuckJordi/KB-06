#pragma once

#include <math.h>

class Vector3
{

public:
	float x, y, z;
	//default constructor
	Vector3(float X = 0, float Y = 0, float Z = 0)
	{
		x = X;
		y = Y;
		z = Z;
	}
	~Vector3(){};

	//calculate and return the magnitude of this vector
	/*float GetMagnitude()
	{
		return sqrtf(x * x + y * y + z * z);
	}*/

	//multiply this vector by a scalar
	/*Vector3 operator*(float num) const
	{
		return Vector3(x * num, y * num, z * num);
	}*/

	//pass in a vector, pass in a scalar, return the product
	/*friend Vector3 operator*(float num, Vector3 const &vec)
	{
		return Vector3(vec.x * num, vec.y * num, vec.z * num);
	}*/

	//add two vectors
	Vector3 operator+(const Vector3 &vec) const
	{
		return Vector3(x + vec.x, y + vec.y, z + vec.z);
	}

	//subtract two vectors
	Vector3 operator-(const Vector3 &vec) const
	{
		return Vector3(x - vec.x, y - vec.y, z - vec.z);
	}

	//normalize given vector
	static Vector3 normalize(Vector3 &vec1)
	{
		float magnitude = sqrtf(vec1.x * vec1.x + vec1.y * vec1.y + vec1.z * vec1.z);
		/*vec1.x /= magnitude;
		vec1.y /= magnitude;
		vec1.z /= magnitude;*/
		return Vector3(vec1.x / magnitude, vec1.y / magnitude, vec1.z / magnitude);
	}

	//calculate and return dot product
	static float dot(Vector3 &vec1, Vector3 &vec2)
	{
		return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
	}

	//calculate and return cross product
	static Vector3 cross(Vector3 &vec1, Vector3 &vec2)
	{
		return Vector3(vec1.y * vec2.z - vec1.z * vec2.y,
			vec1.z * vec2.x - vec1.x * vec2.z,
			vec1.x * vec2.y - vec1.y * vec2.x);
	}
};