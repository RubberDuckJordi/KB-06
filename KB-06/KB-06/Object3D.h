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

		//Vertices to render
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
		void ComputeBoundingBoxSphere();

		//Elements for the AABB (_Low & _High)
		//and bounding sphere (_Center & _Radius)
		Vertex _Low, _High, _Center;
		/*!
		The radius in object space, including any animations
		*/
		float _RadiusHorizontal, _RadiusVertical;
		bool showWarning;
	private:
		Logger* logger;
		std::list<IndexBufferWrapper*> indexBuffers;
		ObjectBone* _Skeleton;//also known as rootbone
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
