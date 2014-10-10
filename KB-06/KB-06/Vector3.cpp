#include "Vector3.h"

namespace pengine
{
	Vector3::Vector3(float X, float Y, float Z)
	{
		x = X;
		y = Y;
		z = Z;
	}

	Vector3::~Vector3()
	{

	}

	Vector3 Vector3::operator+(const Vector3 &vec) const
	{
		return Vector3(x + vec.x, y + vec.y, z + vec.z);
	}

	Vector3 Vector3::operator-(const Vector3 &vec) const
	{
		return Vector3(x - vec.x, y - vec.y, z - vec.z);
	}

	Vector3 Vector3::operator*(const Vector3 &vec) const
	{
		return Vector3(x * vec.x, y * vec.y, z * vec.z);
	}

	float Vector3::GetMagnitude()
	{
		return sqrtf(x * x + y * y + z * z);
	}

	float Vector3::GetXAngle()
	{
		Vector3 xVector;
		xVector.x = 1.0f;
		return CalculateAngle(*this, xVector);
	}

	float Vector3::GetZAngle()
	{
		Vector3 zVector;
		zVector.z = 1.0f;
		return CalculateAngle(*this, zVector);
	}

	float Vector3::GetYAngle()
	{
		Vector3 yVector;
		yVector.y = 1.0f;

		return CalculateAngle(*this, yVector);
	}

	float Vector3::CalculateAngle(Vector3& v1, Vector3& v2)
	{
		// http://www.intmath.com/vectors/7-vectors-in-3d-space.php#anglebetweenvectors
		float dotProduct = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
		float units = sqrt(v1.GetMagnitude() * v2.GetMagnitude());
		return acos(dotProduct / units);
	}

	Vector3 Vector3::normalize(Vector3 &vec1)
	{
		float magnitude = vec1.GetMagnitude();
		return Vector3(vec1.x / magnitude, vec1.y / magnitude, vec1.z / magnitude);
	}

	float Vector3::dot(Vector3 &vec1, Vector3 &vec2)
	{
		return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
	}

	Vector3 Vector3::cross(Vector3 &vec1, Vector3 &vec2)
	{
		return Vector3(vec1.y * vec2.z - vec1.z * vec2.y,
			vec1.z * vec2.x - vec1.x * vec2.z,
			vec1.x * vec2.y - vec1.y * vec2.x);
	}
}