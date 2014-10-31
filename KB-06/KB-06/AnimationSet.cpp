#include "AnimationSet.h"

namespace pengine
{
	AnimationSet::~AnimationSet()
	{
		while (!animations.empty())
		{
			delete animations.back(); animations.pop_back();
		}
	}

	AnimationSet* AnimationSet::IsName(std::string &pText)
	{
		if (strcmp(name.c_str(), pText.c_str()) == 0)
		{
			return this;
		}
		return 0;
	};

	Animation* AnimationSet::FindAnimation(std::string &pText)
	{
		for (std::list<Animation*>::iterator i = animations.begin(); i != animations.end(); i++)
		{
			if ((*i)->IsName(pText) != 0)
			{
				return (*i)->IsName(pText);
			}
		}
		return 0;
	}
}