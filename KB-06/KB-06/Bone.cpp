#include "Bone.h"

namespace pengine
{
	Bone::Bone() : nVertices(0), vertices(0), weights(0)
	{
		matrixPos.Identity();
		_SkinOffset.Identity();
	}

	Bone::~Bone()
	{
		if (vertices != 0)
		{
			delete[] vertices;
		}

		if (weights != 0)
		{
			delete[] weights;
		}

		while (!bones.empty())
		{
			delete bones.back(); bones.pop_back();
		}
	}

	Bone* Bone::IsName(std::string &BoneName)
	{
		if (strcmp(name.c_str(), BoneName.c_str()) == 0)
			return this;

		if (bones.empty())
			return 0;

		for (std::list<Bone*>::iterator i = bones.begin(); i != bones.end(); i++)
			if ((*i)->IsName(BoneName) != 0)
				return (*i)->IsName(BoneName);
		return 0;
	}

	void Bone::UpdateIndices(uint16 pIndex)
	{
		for (uint32 i = 0; i < nVertices; i++)
			vertices[i] += pIndex;
	}
}