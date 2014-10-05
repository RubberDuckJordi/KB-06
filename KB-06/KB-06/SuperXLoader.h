#ifndef _PENGINE_SUPERXLOADER_H_
#define _PENGINE_SUPERXLOADER_H_

#include "IO.h"
#include "XFileStructs.h"
#include "Model3D.h"
#include "LoggerPool.h"

#include <fstream>

namespace pengine
{
	class IO_Model_X : IO < Model3D* >
	{
	public:
		IO_Model_X(void)
		{
			_Type = IO_3DX;
		};
		bool Load(std::string pFilename, Model3D* &pT);
		bool Save(std::string pFilename, Model3D* &pT);
		bool Load(std::string pFilename, std::vector<Model3D*> &pVT)
		{
			return false;
		};
		bool Save(std::string pFilename, std::vector<Model3D*> &pVT)
		{
			return false;
		};

	private:
		Logger* logger = LoggerPool::GetInstance().GetLogger();
		std::ifstream fin;
		Bone* _LoadSkeletton;
		Mesh* _LoadMesh;
		AnimationSet* _LoadAnimationSet;
		Model3D* _Object;

		//Utilities
		int16 ProcessBlock(void);
		int16 BlockID(std::string &pText);
		void AvoidTemplate(void);
		void Find(uchar pChar);
		//Unique X struct ID in case no name are found
		//Uses the Windows function GetTickCount
		char* SetUID(char pType);
		//structure used by the previous function to quickly
		//convert a 32 bit number to a non-significant text.
		union
		{
			uint32 Integer;
			char Text[5];
		}_X_UID;

		//X File struct processing
		uint32 _MaxKey; //Max animation key for a loaded animation set
		void ProcessFrameTransformMatrix(Bone* &pB);
		void ProcessBone(Bone* pBone);
		void ProcessMesh();
		void ProcessMeshTextureCoords();
		void ProcessMeshMaterials();
		void ProcessMeshNormals();
		void ProcessMaterial();
		void ProcessSkinWeights();
		void ProcessAnimationSets();
		void ProcessAnimations(AnimationSet* &pAS);
		void ProcessAnimationKeys(Animation* &pA);
		void ProcessDeclData();
		void MapMeshToBones(Bone* &pBone);
	};
}
#endif