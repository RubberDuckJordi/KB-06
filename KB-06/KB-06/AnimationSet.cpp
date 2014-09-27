#include "AnimationSet.h"

AnimationSet::~AnimationSet(void)
{
	while (!_Animations.empty())
	{
		delete _Animations.back(); _Animations.pop_back();
	}
}

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