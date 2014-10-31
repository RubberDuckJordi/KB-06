#ifndef _PENGINE_MODEL3D_H_
#define _PENGINE_MODEL3D_H_

#include "AnimationSet.h"
#include "Mesh.h"
#include "Bone.h"
#include "LoggerPool.h"

namespace pengine
{
	class Model3D
	{
	public:
		Model3D(Bone* skeleton = 0);
		~Model3D();
		Mesh* IsMeshName(std::string &pText);
		void ConcatenateMeshes(void);
		AnimationSet* FindAnimationSet(std::string &pText);
		Bone* skeleton;
		std::list<Mesh*> meshes;
		std::list<AnimationSet*> animationsets;
	private:
		Logger* logger;
		void UpdateBoneIndices(Bone* &pBone);
	};
}
#endif