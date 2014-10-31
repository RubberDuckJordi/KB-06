#include "Animation.h"
namespace pengine
{
	Animation::~Animation()
	{
		while (!scalings.empty())
		{
			delete scalings.back();
			scalings.pop_back();
		}
		while (!rotations.empty())
		{
			delete rotations.back();
			rotations.pop_back();
		}
		while (!translations.empty())
		{
			delete translations.back();
			translations.pop_back();
		}
		while (!matrices.empty())
		{
			delete matrices.back();
			matrices.pop_back();
		}
	}

	Animation* Animation::IsName(std::string &pText)
	{
		if (strcmp(boneName.c_str(), pText.c_str()) == 0)
		{
			return this;
		}
		return 0;
	}
}