#include "Bone.h"

Bone::~Bone(void){
	if (_Vertices != 0) delete[] _Vertices;
	if (_Weights != 0) delete[] _Weights;
	while (!_Bones.empty())
	{
		delete _Bones.back(); _Bones.pop_back();
	}
}

Bone* Bone::IsName(std::string &BoneName)
{
	if (strcmp(_Name.c_str(), BoneName.c_str()) == 0)
		return this;

	if (_Bones.empty())
		return 0;

	for (std::list<Bone*>::iterator i = _Bones.begin(); i != _Bones.end(); i++)
		if ((*i)->IsName(BoneName) != 0)
			return (*i)->IsName(BoneName);
	return 0;
}

void Bone::UpdateIndices(uint16 pIndex)
{
	for (uint32 i = 0; i < _nVertices; i++)
		_Vertices[i] += pIndex;
}