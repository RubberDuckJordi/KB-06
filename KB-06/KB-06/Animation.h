#ifndef _PENGINE_ANIMATION_H_
#define _PENGINE_ANIMATION_H_

#include "Types.h"
#include "Vector.h"
#include "Quaternion.h"
#include "Matrix.h"
#include "Vertex.h"

#include <string>
#include <vector>

namespace pengine
{
	typedef struct
	{
		uint32 Time;
		Quaternion<float> Rotation;
	} RotateKey;

	typedef struct
	{
		uint32 Time;
		Vertex Translation;
	} PositionKey;

	typedef struct
	{
		uint32 Time;
		Vector<float> Scale;
	} ScaleKey;

	typedef struct
	{
		uint32 Time;
		Matrix<float> Matrix;
	} MatrixKey;

	class Animation
	{
	public:
		~Animation();
		Animation* Get();
		Animation* IsName(std::string &pText);

		std::string _BoneName;
		std::vector<ScaleKey*> _Scalings;
		std::vector<RotateKey*> _Rotations;
		std::vector<PositionKey*> _Translations;
		std::vector<MatrixKey*> _Matrices;
	};
}
#endif