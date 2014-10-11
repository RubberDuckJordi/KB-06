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

		Bone* _Bone;
		Animation* _Animation;
		uint16 _AnimationIndexMat, _AnimationIndexS, _AnimationIndexR, _AnimationIndexT;
		Matrix<float> _TransformMatrix, _CombinedMatrix, _FinalMatrix;
		std::string _BoneName;
		std::list<ObjectBone*> _Bones;
	};
}
#endif