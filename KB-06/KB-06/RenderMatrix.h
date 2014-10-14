#ifndef _PENGINE_RENDERERMATRIX_H_
#define _PENGINE_RENDERERMATRIX_H_

#include "Vector3.h"

namespace pengine
{
	struct PEngineMatrix
	{
		float	_11, _12, _13, _14,
			_21, _22, _23, _24,
			_31, _32, _33, _34,
			_41, _42, _43, _44;
	};

	class RenderMatrix
	{
	public:
		RenderMatrix();
		~RenderMatrix();
		static void CreateMatrix(float x, float y, float z, float yaw, float pitch, float roll, float scaleX, float scaleY, float scaleZ, PEngineMatrix* matrix);
		static void CreateLookAtMatrix(Vector3 pos, Vector3 lookAtPos, Vector3 upVector, PEngineMatrix* receiver);
		static void MultiplyMatrices(PEngineMatrix* m1, PEngineMatrix* m2, PEngineMatrix* receiver);
		static void PrintMatrix(PEngineMatrix* matrix);
		PEngineMatrix* theMatrix;
	};
}
#endif