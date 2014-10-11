#include "AnimationSet.h"

namespace pengine
{
	AnimationSet::~AnimationSet()
	{
		while (!_Animations.empty())
		{
			delete _Animations.back(); _Animations.pop_back();
		}
	}

	AnimationSet* AnimationSet::IsName(std::string &pText)
	{
		if (strcmp(_Name.c_str(), pText.c_str()) == 0)
		{
			return this;
		}
		return 0;
	};

	Animation* AnimationSet::FindAnimation(std::string &pText)
	{
		for (std::list<Animation*>::iterator i = _Animations.begin(); i != _Animations.end(); i++)
		{
			if ((*i)->IsName(pText) != 0)
			{
				return (*i)->IsName(pText);
			}
		}
		return 0;
	}
}