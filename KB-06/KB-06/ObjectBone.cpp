#include "ObjectBone.h"
#include "LoggerPool.h"

namespace pengine
{
	ObjectBone::ObjectBone() : bone(0), animation(0)
	{
		transformMatrix.Identity();
		combinedMatrix.Identity();
		finalMatrix.Identity();
	}

	ObjectBone::~ObjectBone()
	{
		while (!bones.empty())
		{
			delete bones.back(); bones.pop_back();
		}
	}

	void ObjectBone::CalcAttitude(ObjectBone* pParentBone)
	{
		if (pParentBone == 0)
		{
			combinedMatrix = transformMatrix;
		}
		else
		{
			combinedMatrix = transformMatrix * pParentBone->combinedMatrix;
		}

		finalMatrix = bone->_SkinOffset * combinedMatrix;
	}

	void ObjectBone::CalcAnimation(uint16 &pKey)
	{
		if (animation == 0)
		{
			return;
		}

		Matrix Mat;
		float DeltaKey; //difference between two time keys
		float cTime; //pKey minus current key time: cTime / DeltaKey gives the interpolation factor

		//If the transformations are expressed as matrices
		if (!animation->matrices.empty())
		{
			if (pKey == 0)
			{
				animationIndexMat = 0;
			}

			if (animationIndexMat == animation->matrices.size() - 1)
			{
				//If we are at the last matrix index use the last matrix as a transform matrix
				Mat = (animation->matrices[animationIndexMat])->Matrix;
			}
			else
			{
				//Advance the internal matrix animation index according to the main Time count
				while (pKey > (animation->matrices[animationIndexMat + 1])->Time)
				{
					animationIndexMat++;
					if (animationIndexMat >= animation->matrices.size())
					{
						animationIndexMat = animation->matrices.size() - 1;
						break;
					}
				}

				//interpolate the transform matrix between this matrix index and
				//the next using the Time count parameter
				DeltaKey = (float)((animation->matrices[animationIndexMat + 1])->Time - (animation->matrices[animationIndexMat])->Time);
				cTime = (float)(pKey - (animation->matrices[animationIndexMat])->Time);
				Mat = (animation->matrices[animationIndexMat])->Matrix + (((animation->matrices[animationIndexMat + 1])->Matrix - (animation->matrices[animationIndexMat])->Matrix) * (cTime / DeltaKey));
			}
			transformMatrix = Mat;
		}
		else
		{
			Quaternion Quat;
			Vector Scale;
			Vertex Translate;

			transformMatrix.Identity();
			if (pKey == 0)
			{
				animationIndexR = 0;
				animationIndexS = 0;
				animationIndexT = 0;
			}

			//If there are rotations
			if (!animation->rotations.empty())
			{
				if (animationIndexR == animation->rotations.size() - 1)
				{
					//If we are at the last rotation index use the last rotation
					Quat = (animation->rotations[animationIndexR])->Rotation;
				}
				else
				{
					//Advance the internal rotation animation index according to the main Time count
					while (pKey > (animation->rotations[animationIndexR + 1])->Time)
					{
						animationIndexR++;
						if (animationIndexR >= animation->rotations.size())
						{
							animationIndexR = animation->rotations.size() - 1;
							break;
						}
					}
					//Interpolate the quaternion
					DeltaKey = (float)((animation->rotations[animationIndexR + 1])->Time - (animation->rotations[animationIndexR])->Time);
					cTime = (float)(pKey - (animation->rotations[animationIndexR])->Time);
					Quat = (animation->rotations[animationIndexR])->Rotation.Slerp(cTime / DeltaKey, (animation->rotations[animationIndexR + 1])->Rotation);
				}
				Mat.Identity();
				Mat.QuaternionMatrix(Quat[1], Quat[2], Quat[3], Quat[0]);
				transformMatrix *= Mat;
			}

			//if there are scalings
			if (!animation->scalings.empty())
			{
				if (animationIndexS == animation->scalings.size() - 1)
				{
					//If we are at the last scaling index use the last scaling
					Scale = (animation->scalings[animationIndexS])->Scale;
				}
				else
				{
					//Advance the internal scaling animation index according to the main Time count
					while (pKey > (animation->scalings[animationIndexS + 1])->Time)
					{
						animationIndexS++;
						if (animationIndexS >= animation->scalings.size())
						{
							animationIndexS = animation->scalings.size() - 1;
							break;
						}
					}
					//Interpolate the vector
					DeltaKey = (float)((animation->scalings[animationIndexS + 1])->Time - (animation->scalings[animationIndexS])->Time);
					cTime = (float)(pKey - (animation->scalings[animationIndexS])->Time);
					Scale = (animation->scalings[animationIndexS])->Scale + (((animation->scalings[animationIndexS + 1])->Scale - (animation->scalings[animationIndexS])->Scale) * (cTime / DeltaKey));
				}

				Mat.Identity();
				Mat.ScalingMatrix(Scale);
				transformMatrix *= Mat;
			}

			//if there are translations
			if (!animation->translations.empty())
			{
				if (animationIndexT == animation->translations.size() - 1)
				{
					//If we are at the last translation index use the last translation
					Translate = (animation->translations[animationIndexT])->Translation;
				}
				else
				{
					//Advance the internal translation animation index according to the main Time count
					while (pKey > (animation->translations[animationIndexT + 1])->Time)
					{
						animationIndexT++;
						if (animationIndexT >= animation->translations.size())
						{
							animationIndexT = animation->translations.size() - 1;
							break;
						}
					}
					//interpolate the vector
					DeltaKey = (float)((animation->translations[animationIndexT + 1])->Time - (animation->translations[animationIndexT])->Time);
					cTime = (float)(pKey - (animation->translations[animationIndexT])->Time);
					Translate = (animation->translations[animationIndexT])->Translation + (((animation->translations[animationIndexT + 1])->Translation - (animation->translations[animationIndexT])->Translation) * (cTime / DeltaKey));
				}
				Mat.Identity();
				Mat.TranslationMatrix(Translate);
				transformMatrix *= Mat;
			}
		}
	}

	void ObjectBone::CalcBindSpace()
	{
		transformMatrix = bone->matrixPos;
	}
}