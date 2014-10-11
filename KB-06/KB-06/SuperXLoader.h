#ifndef _PENGINE_SUPERXLOADER_H_
#define _PENGINE_SUPERXLOADER_H_

#include "XFileStructs.h"
#include "Model3D.h"
#include "LoggerPool.h"

#include <fstream>

namespace pengine
{
	class SuperXLoader
	{
	public:
		SuperXLoader();
		~SuperXLoader();
		bool Load(std::string pFilename, Model3D* &pT);

		/*!
		Transforms given text into a number, ignores everything that isn't number-related.
		*/
		float TextToNum(char* pText);
		/*!
		Removes all occurences of the given character from the given text.
		*/
		void Remove(char pDelimiter, char* pText);

	private:
		Logger* logger;
		std::ifstream fin;
		std::map<std::string, Material *> globalMaterials;
		std::map<std::string, Bone *> unlinkedSkinnedBones;
		Bone* _LoadSkeleton;
		Mesh* _LoadMesh;
		AnimationSet* _LoadAnimationSet;
		Model3D* _Object;

		/*!
		Processes the next thing it can read in the file.

		@return int16: X_COMMENT if it's a whitespace or actual comment. X_OBRACE if it's a {.
		X_EBRACE if it's a }. X_ERROR if there's a single /. Result of BlockID() otherwise.
		*/
		int16 ProcessBlock(void);

		/*!
		Tries to identify the given text as a block

		@param &pText: The text to find a block in.
		@return int16: The numerical identifier of a block, or X_ERROR/X_UNKNOWN/X_COMMENT if it's not a block.
		*/
		int16 BlockID(std::string &pText);

		/*!
		Capable of ignoring a complete block, including blocks that may be within it.
		*/
		void AvoidTemplate(void);

		/*!
		Ignores all input until pChar has been found, including pChar.
		*/
		void Find(uchar pChar);

		/*!
		Returns a unique identifier, makes use of both time and random.
		Currently used in case a block in the X file has no name.
		*/
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
		void ProcessMaterial(bool global);
		void ProcessSkinWeights();
		void ProcessAnimationSets();
		void ProcessAnimations(AnimationSet* &pAS);
		void ProcessAnimationKeys(Animation* &pA);
		void ProcessDeclData();
		void MapMeshToBones(Bone* &pBone);
	};
}
#endif