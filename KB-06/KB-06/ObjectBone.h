#ifndef _PENGINE_OBJECTBONE_H_
#define _PENGINE_OBJECTBONE_H_

#include "Bone.h"
#include "Animation.h"

namespace pengine
{
	class ObjectBone{
	public:
		ObjectBone(void) : _Bone(0), _Animation(0){ _TransformMatrix.Identity(); _CombinedMatrix.Identity(); _FinalMatrix.Identity(); };
		~ObjectBone(void);

		void CalcAttitude(ObjectBone* pParentBone); //compute the Final Matrix
		void CalcAnimation(uint16 &pKey); //retrieves a transformation matrice from an animation
		void CalcBindSpace(void){ _TransformMatrix = _Bone->_MatrixPos; }; //Sets up the original Matrix position as transformation matrix

		Bone* _Bone;
		Animation* _Animation;
		uint16 _AnimationIndexMat, _AnimationIndexS, _AnimationIndexR, _AnimationIndexT;
		Matrix<float> _TransformMatrix, _CombinedMatrix, _FinalMatrix;
		std::string _BoneName;
		std::list<ObjectBone*> _Bones;
	};
}
#endif