#ifndef _PENGINE_ANIMATIONSET_H_
#define _PENGINE_ANIMATIONSET_H_

#include "Animation.h"

#include <list>

namespace pengine
{
	class AnimationSet
	{
	public:
		~AnimationSet();
		AnimationSet* IsName(std::string &pText);
		Animation* FindAnimation(std::string &pText);
		std::string _Name;
		std::list<Animation*> _Animations;
		uint32 _MaxKey; //Maximum time key for the full animation set
	};
}
#endif