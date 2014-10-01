#ifndef _PENGINE_MODEL3D_H_
#define _PENGINE_MODEL3D_H_

#include "AnimationSet.h"
#include "XMesh.h"
#include "Bone.h"

#include "LoggerPool.h"

namespace pengine
{
	class Model3D
	{
	public:
		Model3D(void) : _Skeletton(0)
		{
		};
		~Model3D(void);
		Mesh* IsMeshName(std::string &pText);
		void ConcatenateMeshes(void);
		AnimationSet* FindAnimationSet(std::string &pText);
		Bone* _Skeletton;
		std::list<Mesh*> _Meshes;
		std::list<AnimationSet*> _AnimationSets;
	private:
		Logger* logger = LoggerPool::GetInstance().GetLogger();
		void UpdateBoneIndices(Bone* &pBone);
	};
}
#endif