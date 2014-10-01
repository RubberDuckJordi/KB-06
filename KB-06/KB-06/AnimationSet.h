#ifndef _PENGINE_ANIMATIONSET_H_
#define _PENGINE_ANIMATIONSET_H_

#include "Animation.h"

#include <list>

namespace pengine
{
	class AnimationSet
	{
	public:
		~AnimationSet(void);
		AnimationSet* IsName(std::string &pText)
		{
			if (strcmp(_Name.c_str(), pText.c_str()) == 0)
			{
				return this;
			}
			return 0;
		};
		Animation* FindAnimation(std::string &pText);
		std::string _Name;
		std::list<Animation*> _Animations;
		uint32 _MaxKey; //Maximum time key for the full animation set
	};
}
#endif