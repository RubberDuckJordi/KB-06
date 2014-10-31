#ifndef _PENGINEbone_H_
#define _PENGINEbone_H_

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
		// Returns this pointer if bone name is equal to the BoneName parameter
		Bone* IsName(std::string &BoneName);
		void UpdateIndices(uint16 pIndex);

		Matrix matrixPos, _SkinOffset;
		uint32 nVertices;
		uint16* vertices;
		float* weights;
		std::string meshName;
		std::string name;
		std::list<Bone*> bones;
	};
}
#endif