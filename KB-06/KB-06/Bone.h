#ifndef _PENGINE_BONE_H_
#define _PENGINE_BONE_H_

#include "Matrix.h"
#include "Types.h"

#include <string>
#include <list>

namespace pengine
{
	class Bone
	{
	public:
		Bone();
		~Bone();
		Bone* IsName(std::string &BoneName);
		void UpdateIndices(uint16 pIndex);

		Matrix _MatrixPos, _SkinOffset;
		uint32 _nVertices;
		uint16* _Vertices;
		float* _Weights;
		std::string _MeshName;
		std::string _Name;
		std::list<Bone*> _Bones;
	};
}
#endif