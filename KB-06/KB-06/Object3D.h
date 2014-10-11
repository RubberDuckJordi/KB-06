////////////////////////////////////////////////////////////////
// 3DObject_GL.h
// OpenGL Screen implmentation
//
////////////////////////////////////////////////////////////////

#ifndef _PENGINE_OBJECT3D_H_
#define _PENGINE_OBJECT3D_H_

#include "Mesh.h" //based on the correct Mesh element
#include "Matrix.h"
#include "Bone.h"
#include "AnimationSet.h"
#include "Model3D.h"
#include "Renderer.h"
#include "ObjectBone.h"
#include "Rectangle.h"

namespace pengine
{
	class Object3D
	{
	public:
		Object3D(void) :_Skeleton(0), _SkinnedVertices(0), _Model(0), _AnimationStep(1)
		{
		};
		~Object3D(void)
		{
			if (_SkinnedVertices != 0)
			{
				delete[] _SkinnedVertices;
			}
		}
		void SetupModel(Model3D* &pModel)
		{
			_Model = pModel;
			_Mesh = _Model->_Meshes.back();
			_SkinnedVertices = new Vertex[_Mesh->_nVertices];
			_Skeleton = ReplicateSkeleton(_Model->_Skeleton);
		};

		//Vertices to render
		void ClearSkinnedVertices(void)
		{
			memset(_SkinnedVertices, 0, _Mesh->_nVertices * sizeof(Vertex));
		};

		//Animation Based
		void SetAnimationStep(uint16 pStep)
		{
			_AnimationStep = pStep;
		};
		void MapAnimationSet(std::string pText = "None");
		void MapAnimationSet(uint16 &index);
		void UpdateAnimation()
		{
			if (showWarning && _cAnimationSet == NULL)
			{
				//this warning should be in the future PEngine manual instead, with just a crash...
				logger->Log(Logger::WARNING, "There are no animations, don't call UpdateAnimation!");
			}
			else if (_cAnimationSet != NULL)
			{
				ClearSkinnedVertices();
				_cKey += _AnimationStep;
				if (_cKey > _cAnimationSet->_MaxKey)
				{
					_cKey = 0;
				}
				CalcAnimation(_Skeleton);
				ComputeBoundingBoxSphere();
				CalcAttitude(_Skeleton, 0);
				SkinMesh(_Skeleton);
			}
		};
		void UpdateBindSpace(void)
		{
			CalcBindSpace(_Skeleton);
			CalcAttitude(_Skeleton, 0);
			SkinMesh(_Skeleton);
		};
		inline void CalcAnimation(void)
		{
			_cKey += _AnimationStep;
			if (_cKey > _cAnimationSet->_MaxKey)
			{
				_cKey = 0;
			}
			CalcAnimation(_Skeleton);
			ComputeBoundingBoxSphere();
		};
		inline void CalcBindSpace(void)
		{
			CalcBindSpace(_Skeleton);
		};
		inline void Update(void)
		{
			CalcAttitude(_Skeleton, 0);
			SkinMesh(_Skeleton);
		};
		void Draw(Renderer* renderer);

		void CreateCollisionBox(RECTANGLE& rect);
		void ComputeBoundingBoxSphere(void);
		//Elements for the AABB (_Low & _High)
		//and bounding sphere (_Center & _Radius)
		Vertex _Low, _High, _Center;
		float _Radius;
		bool showWarning = true;
	private:
		Logger* logger = LoggerPool::GetInstance().GetLogger();
		ObjectBone* _Skeleton;
		Mesh* _Mesh; //pointer to Model Mesh
		Vertex* _SkinnedVertices;
		Model3D* _Model;
		AnimationSet* _cAnimationSet;

		uint16 _cKey; //current animation Key
		uint16 _AnimationStep; //Animation Increment

		ObjectBone* ReplicateSkeleton(Bone* &pBone);
		void GetBoneAnimation(ObjectBone* &pBone);
		void CalcAttitude(ObjectBone* pBone, ObjectBone* pParentBone);
		void CalcAnimation(ObjectBone* &pBone);
		void CalcBindSpace(ObjectBone* &pBone);
		void SkinMesh(ObjectBone* pParentBone);
	};
}
#endif
