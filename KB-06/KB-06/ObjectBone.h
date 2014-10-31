#ifndef _PENGINE_OBJECTBONE_H_
#define _PENGINE_OBJECTBONE_H_

#include "Bone.h"
#include "Animation.h"

namespace pengine
{
	class ObjectBone{
	public:
		ObjectBone();
		~ObjectBone();

		//compute the Final Matrix
		void CalcAttitude(ObjectBone* pParentBone);

		//retrieves a transformation matrice from an animation
		void CalcAnimation(uint16 &pKey);

		//Sets up the original Matrix position as transformation matrix
		void CalcBindSpace();

		Bone* bone;
		Animation* animation;
		uint16 animationIndexMat, animationIndexS, animationIndexR, animationIndexT;
		Matrix transformMatrix, combinedMatrix, finalMatrix;
		std::string boneName;
		std::list<ObjectBone*> bones;
	};
}
#endif