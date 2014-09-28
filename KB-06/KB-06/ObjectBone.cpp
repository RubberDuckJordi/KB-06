#include "ObjectBone.h"

ObjectBone::~ObjectBone(void){
	while (!_Bones.empty())
	{
		delete _Bones.back(); _Bones.pop_back();
	}
}

void ObjectBone::CalcAttitude(ObjectBone* pParentBone){
	if (pParentBone == 0)
	{
		_CombinedMatrix = _TransformMatrix;
	}
	else
	{
		_CombinedMatrix = _TransformMatrix * pParentBone->_CombinedMatrix;
	}

	_FinalMatrix = _Bone->_SkinOffset * _CombinedMatrix;
}/**/

/*************************************************
NEW- NEW- NEW- NEW- NEW- NEW- NEW- NEW- NEW- NEW*/

void ObjectBone::CalcAnimation(uint16 &pKey){
	if (_Animation == 0)
	{
		return;
	}

	Matrix<float> Mat;
	float DeltaKey; //difference between two time keys
	float cTime; //pKey minus current key time: cTime / DeltaKey gives the interpolation factor

	//If the transformations are expressed as matrices
	if (!_Animation->_Matrices.empty())
	{
		if (pKey == 0)
		{
			_AnimationIndexMat = 0;
		}

		if (_AnimationIndexMat == _Animation->_Matrices.size() - 1)
		{
			//If we are at the last matrix index use the last matrix as a transform matrix
			Mat = (_Animation->_Matrices[_AnimationIndexMat])->Matrix;
		}
		else
		{
			//Advance the internal matrix animation index according to the main Time count
			while (pKey > (_Animation->_Matrices[_AnimationIndexMat + 1])->Time)
			{
				_AnimationIndexMat++;
				if (_AnimationIndexMat >= _Animation->_Matrices.size())
				{
					_AnimationIndexMat = _Animation->_Matrices.size() - 1;
					break;
				}
			}

			//interpolate the transform matrix between this matrix index and
			//the next using the Time count parameter
			DeltaKey = (_Animation->_Matrices[_AnimationIndexMat + 1])->Time - (_Animation->_Matrices[_AnimationIndexMat])->Time;
			cTime = pKey - (_Animation->_Matrices[_AnimationIndexMat])->Time;
			Mat = (_Animation->_Matrices[_AnimationIndexMat])->Matrix + (((_Animation->_Matrices[_AnimationIndexMat + 1])->Matrix - (_Animation->_Matrices[_AnimationIndexMat])->Matrix) * (cTime / DeltaKey));
		}
		_TransformMatrix = Mat;
	}
	else
	{
		Quaternion<float> Quat;
		Vector<float> Scale;
		Vertex Translate;

		_TransformMatrix.Identity();
		if (pKey == 0)
		{
			_AnimationIndexR = 0;
			_AnimationIndexS = 0;
			_AnimationIndexT = 0;
		}

		//If there are rotations
		if (!_Animation->_Rotations.empty())
		{
			if (_AnimationIndexR == _Animation->_Rotations.size() - 1)
			{
				//If we are at the last rotation index use the last rotation
				Quat = (_Animation->_Rotations[_AnimationIndexR])->Rotation;
			}
			else
			{
				//Advance the internal rotation animation index according to the main Time count
				while (pKey > (_Animation->_Rotations[_AnimationIndexR + 1])->Time)
				{
					_AnimationIndexR++;
					if (_AnimationIndexR >= _Animation->_Rotations.size())
					{
						_AnimationIndexR = _Animation->_Rotations.size() - 1;
						break;
					}
				}
				//Interpolate the quaternion
				DeltaKey = (_Animation->_Rotations[_AnimationIndexR + 1])->Time - (_Animation->_Rotations[_AnimationIndexR])->Time;
				cTime = pKey - (_Animation->_Rotations[_AnimationIndexR])->Time;
				Quat = (_Animation->_Rotations[_AnimationIndexR])->Rotation.Slerp(cTime / DeltaKey, (_Animation->_Rotations[_AnimationIndexR + 1])->Rotation);
			}
			Mat.Identity();
			Mat.QuaternionMatrix(Quat[1], Quat[2], Quat[3], Quat[0]);
			_TransformMatrix *= Mat;
		}

		//if there are scalings
		if (!_Animation->_Scalings.empty())
		{
			if (_AnimationIndexS == _Animation->_Scalings.size() - 1)
			{
				//If we are at the last scaling index use the last scaling
				Scale = (_Animation->_Scalings[_AnimationIndexS])->Scale;
			}
			else
			{
				//Advance the internal scaling animation index according to the main Time count
				while (pKey > (_Animation->_Scalings[_AnimationIndexS + 1])->Time)
				{
					_AnimationIndexS++;
					if (_AnimationIndexS >= _Animation->_Scalings.size())
					{
						_AnimationIndexS = _Animation->_Scalings.size() - 1;
						break;
					}
				}
				//Interpolate the vector
				DeltaKey = (_Animation->_Scalings[_AnimationIndexS + 1])->Time - (_Animation->_Scalings[_AnimationIndexS])->Time;
				cTime = pKey - (_Animation->_Scalings[_AnimationIndexS])->Time;
				Scale = (_Animation->_Scalings[_AnimationIndexS])->Scale + (((_Animation->_Scalings[_AnimationIndexS + 1])->Scale - (_Animation->_Scalings[_AnimationIndexS])->Scale) * (cTime / DeltaKey));
			}

			Mat.Identity();
			Mat.ScalingMatrix(Scale);
			_TransformMatrix *= Mat;
		}

		//if there are translations
		if (!_Animation->_Translations.empty())
		{
			if (_AnimationIndexT == _Animation->_Translations.size() - 1)
			{
				//If we are at the last translation index use the last translation
				Translate = (_Animation->_Translations[_AnimationIndexT])->Translation;
			}
			else
			{
				//Advance the internal translation animation index according to the main Time count
				while (pKey > (_Animation->_Translations[_AnimationIndexT + 1])->Time)
				{
					_AnimationIndexT++;
					if (_AnimationIndexT >= _Animation->_Translations.size())
					{
						_AnimationIndexT = _Animation->_Translations.size() - 1;
						break;
					}
				}
				//interpolate the vector
				DeltaKey = (_Animation->_Translations[_AnimationIndexT + 1])->Time - (_Animation->_Translations[_AnimationIndexT])->Time;
				cTime = pKey - (_Animation->_Translations[_AnimationIndexT])->Time;
				Translate = (_Animation->_Translations[_AnimationIndexT])->Translation 
					+ (((_Animation->_Translations[_AnimationIndexT + 1])->Translation 
					- (_Animation->_Translations[_AnimationIndexT])->Translation) * (cTime / DeltaKey));
			}
			Mat.Identity();
			Mat.TranslationMatrix(Translate);
			_TransformMatrix *= Mat;
		}
	}
}/**/