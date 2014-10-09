#ifndef _PENGINE_VERTEX_H_
#define _PENGINE_VERTEX_H_

namespace pengine
{
	struct Vertex
	{
		float x, y, z, tu, tv;

		Vertex operator+(Vertex pA)
		{
			Vertex result;
			result.x = x + pA.x;
			result.y = y + pA.y;
			result.z = z + pA.z;
			return result;
		};

		Vertex operator-(Vertex pA)
		{
			Vertex result;
			result.x = x - pA.x;
			result.y = y - pA.y;
			result.z = z - pA.z;
			return result;
		};

		Vertex operator*(float scalar)
		{
			Vertex result;
			result.x = x * scalar;
			result.y = y * scalar;
			result.z = z * scalar;
			return result;
		};
	};

	
}
#endif
