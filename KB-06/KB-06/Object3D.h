#ifndef _PENGINE_OBJECT3D_H_
#define _PENGINE_OBJECT3D_H_

#include "Mesh.h"
#include "Matrix.h"
#include "Bone.h"
#include "AnimationSet.h"
#include "Model3D.h"
#include "Renderer.h"
#include "ObjectBone.h"
#include "Beam.h"

namespace pengine
{
	class Object3D
	{
	public:
		Object3D();
		~Object3D();
		void SetupModel(Model3D* &pModel);

		void ClearSkinnedVertices();

		//Animation Based
		void SetAnimationStep(uint16 pStep);
		void MapAnimationSet(std::string pText = "None");
		void MapAnimationSet(uint16 &index);
		void UpdateAnimation();
		void UpdateBindSpace();
		void CalcAnimation();
		void CalcBindSpace();
		void Update();

		void CacheToRenderer(Renderer* renderer);
		void Render(Renderer* renderer);

		void CreateCollisionBox(BEAM& rect);
		float GetMinZ();
		float GetMaxZ();
		float GetMinX();
		float GetMaxX();
		float GetMinY();
		float GetMaxY();
		void ComputeBoundingBoxSphere();

		/*!
		Gets the maximum radius you can possibly get with a default scaling of 1.
		This means that any rotated state of this object falls within the radius.
		If you change scaling, you'll need to multiply this result with the 
		highest scaled axis;
		*/
		float GetMaxRadius();

		//Elements for the AABB (low & high)
		//and bounding sphere (center & _Radius)
		Vector3 low, high, center;

		bool showWarning;
	private:
		Logger* logger;
		std::list<IndexBufferWrapper*> indexBuffers;
		ObjectBone* skeleton;//also known as rootbone
		Mesh* _Mesh; //pointer to Model Mesh
		Vertex* _SkinnedVertices;
		Model3D* _Model;
		AnimationSet* _cAnimationSet;

		uint16 _cKey; //current animation Key
		uint16 animationstep; //Animation Increment

		ObjectBone* ReplicateSkeleton(Bone* &pBone);
		void GetBoneAnimation(ObjectBone* &pBone);
		void CalcAttitude(ObjectBone* pBone, ObjectBone* pParentBone);
		void CalcAnimation(ObjectBone* &pBone);
		void CalcBindSpace(ObjectBone* &pBone);
		void SkinMesh(ObjectBone* pParentBone);
	};
}
#endif
