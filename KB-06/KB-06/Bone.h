#include "Matrix.h"
#include "Types.h"

#include <string>
#include <list>

class Bone
{
public:
	Bone(void) : _nVertices(0), _Vertices(0), _Weights(0)
	{
		_MatrixPos.Identity(); _SkinOffset.Identity();
	};
	~Bone(void);
	Bone* IsName(std::string &BoneName);
	void UpdateIndices(uint16 pIndex);

	Matrix<float> _MatrixPos, _SkinOffset;
	uint32 _nVertices;
	uint16* _Vertices;
	float* _Weights;
	std::string _MeshName;
	std::string _Name;
	std::list<Bone*> _Bones;
};