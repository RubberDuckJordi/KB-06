#include "AnimationSet.h"
#include "XMesh.h"
#include "Bone.h"

#include "LoggerPool.h"

class Model3D
{
public:
	Model3D(void) : _Skeletton(0)
	{
	};
	~Model3D(void);
	XMesh* IsMeshName(std::string &pText);
	void ConcatenateMeshes(void);
	AnimationSet* FindAnimationSet(std::string &pText);
	Bone* _Skeletton;
	std::list<XMesh*> _Meshes;
	std::list<AnimationSet*> _AnimationSets;
private:
	pengine::Logger* logger = pengine::LoggerPool::GetInstance().GetLogger();
	void UpdateBoneIndices(Bone* &pBone);
};