#ifndef _PENGINE_VERTEX_H_
#define _PENGINE_VERTEX_H_

namespace pengine
{
	struct Vertex
	{
		float x, y, z, tu, tv;

		/*!
		Does NOT add texture coordinates!
		*/
		Vertex operator+(Vertex pA)
		{
			Vertex result;
			result.x = x + pA.x;
			result.y = y + pA.y;
			result.z = z + pA.z;
			result.tu = pA.tu;
			result.tv = pA.tv;
			return result;
		};

		/*!
		Does NOT subtract texture coordinates!
		*/
		Vertex operator-(Vertex pA)
		{
			Vertex result;
			result.x = x - pA.x;
			result.y = y - pA.y;
			result.z = z - pA.z;
			result.tu = pA.tu;
			result.tv = pA.tv;
			return result;
		};

		/*!
		Does NOT multiply texture coordinates!
		*/
		Vertex operator*(float scalar)
		{
			Vertex result;
			result.x = x * scalar;
			result.y = y * scalar;
			result.z = z * scalar;
			result.tu = tu;
			result.tv = tv;
			return result;
		};
	};

	
}
#endif
