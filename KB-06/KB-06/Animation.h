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
	struct RotateKey
	{
		uint32 Time;
		Quaternion Rotation;
	};

	struct PositionKey
	{
		uint32 Time;
		Vertex Translation;
	};

	struct ScaleKey
	{
		uint32 Time;
		Vector Scale;
	};

	struct MatrixKey
	{
		uint32 Time;
		Matrix Matrix;
	};

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