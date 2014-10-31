#ifndef _PENGINEanimation_H_
#define _PENGINEanimation_H_

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

		std::string boneName;
		std::vector<ScaleKey*> scalings;
		std::vector<RotateKey*> rotations;
		std::vector<PositionKey*> translations;
		std::vector<MatrixKey*> matrices;
	};
}
#endif