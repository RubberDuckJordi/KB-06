#ifndef _PENGINEanimationsET_H_
#define _PENGINEanimationsET_H_

#include "Animation.h"

#include <list>

namespace pengine
{
	class AnimationSet
	{
	public:
		~AnimationSet();
		// Returns this pointer if the name of the animation 
		AnimationSet* IsName(std::string &pText);
		// Finds a specific animation in the animation set
		Animation* FindAnimation(std::string &pText);
		std::string name;
		std::list<Animation*> animations;
		uint32 maxKey; //Maximum time key for the full animation set
	};
}
#endif