/////////////////////////////////////////////////////////
// IOModel_X.cpp
// load/save Frame descriptions
//
/////////////////////////////////////////////////////////

#include "SuperXLoader.h"

#define TEXT_BUFFER 255

#define MAX_TEMPLATES 15

namespace pengine
{
	struct XOF_TEMPLATEID{
		char* TxtID;
		uint16 TemplateID;
	};

	XOF_TEMPLATEID Templates[MAX_TEMPLATES] = {
		{ "template", X_TEMPLATE },
		{ "FrameTransformMatrix", X_FRAMETRANSFORMMATRIX },
		{ "Frame", X_FRAME },
		{ "XSkinMeshHeader", X_SKINMESHHEADER },
		{ "MeshTextureCoords", X_MESHTEXTURECOORDS },
		{ "MeshMaterialList", X_MESHMATERIALLIST },
		{ "MeshNormals", X_MESHNORMALS },
		{ "Mesh", X_MESH },
		{ "Material", X_MATERIAL },
		{ "SkinWeights", X_SKINWEIGHTS },
		{ "TextureFilename", X_TEXTUREFILENAME },
		{ "AnimationSet", X_ANIMATIONSET },
		{ "AnimationKey", X_ANIMATIONKEY },
		{ "Animation", X_ANIMATION },
		{ "Header", X_HEADER }
	};

	//////////////////////////////////////////////////////////
	//
	//       MAIN LOAD & SAVE FUNCTIONS
	//
	//////////////////////////////////////////////////////////

	bool IO_Model_X::Load(std::string pFilename, Model3D* &pT)
	{
		XFileHeader XHeader;

		////logger->LogAll(0, "SuperXLoader: Processing file:", pFilename);

		fin.open(pFilename.c_str(), std::ios::in);

		if (fin.bad())
		{
			////logger->LogAll(0, "SuperXLoader: Failed opening file:", pFilename);
			return false;
		}

		fin.read((char*)&XHeader, 16);
		if (XHeader.Magic != XOFFILE_FORMAT_MAGIC)
		{
			////logger->Log(0, "SuperXLoader: Not a .X model file. Aborted.");
			return false;
		}

		if (XHeader.Major_Version != XOFFILE_FORMAT_VERSION03)
		{
			////logger->Log(0, "SuperXLoader: Major version greater than 03. Aborted.");
			return false;
		}

		if ((XHeader.Minor_Version != XOFFILE_FORMAT_VERSION03) || (XHeader.Minor_Version != XOFFILE_FORMAT_VERSION02))
		{
			////logger->Log(0, "SuperXLoader: Minor version greater than 03. Aborted.");
			return false;
		}

		if (XHeader.Format != XOFFILE_FORMAT_TEXT)
		{
			////logger->Log(0, "SuperXLoader: Not a text format. Aborted.");
			return false;
		}

		_Object = pT;

		while (!fin.eof())
		{
			switch (ProcessBlock())
			{
			case X_ERROR:
				////logger->Log(0, "SuperXLoader: Stopped processing the file.");
				return false;
				break;
			case X_COMMENT:
				break; //nothing to do
			case X_EBRACE:
				break; //end of a block ?!
			case X_FRAME:
				ProcessBone((Bone*)0);
				break;
			case X_MESH:
				ProcessMesh();
				break;
			case X_ANIMATIONSET:
				ProcessAnimationSets();
				break;
			case X_OBRACE:
			default:
				AvoidTemplate();
				break;
			}
		}

		if (_LoadSkeletton != 0)
		{
			MapMeshToBones(_LoadSkeletton);
		}

		////logger->LogAll(0, "SuperXLoader: Processed file:", pFilename);

		fin.close();
		for (int i = 0; i < _LoadMesh->_nVertices; ++i)
		{
			/*////logger->LogAll(0, "GVD1", _LoadMesh->_Vertices[i].data[0]);
			////logger->LogAll(0, "GVD2", _LoadMesh->_Vertices[i].data[1]);
			////logger->LogAll(0, "GVD3", _LoadMesh->_Vertices[i].data[2]);*/
		}
		return true;
	}

	bool IO_Model_X::Save(std::string pFilename, Model3D* &pT)
	{
		return false;
	}

	//////////////////////////////////////////////////////////
	//
	//       UTILITIES
	//
	//////////////////////////////////////////////////////////

	int16 IO_Model_X::ProcessBlock(void)
	{
		std::string Text;
		char Token = fin.peek();
		switch (Token)
		{
		case '\n':
		case ' ':
		case '\t':
			fin.get();
			return X_COMMENT; //spaces are identified as comments
			break;
		case '{':
			return X_OBRACE;
			break;
		case '}':
			fin.get();
			return X_EBRACE; //We arrived at the end of the block
			break;
		case '/':
			fin.get();
			if (fin.peek() != '/')
			{
				return X_ERROR;
			} //we processed a block name starting with slash ?!
			break;
		case '#':
			fin.ignore(TEXT_BUFFER, '\n');
			return X_COMMENT;
			break;
		default:
			fin >> Text;
			return BlockID(Text);
		};
		return X_COMMENT;
	}

	int16 IO_Model_X::BlockID(std::string &pText)
	{
		long Pos;

		if (fin.eof())
		{
			return X_COMMENT;
		}

		if (pText.empty())
		{
			////logger->Log(0, "SuperXLoader: Error: no block read!");
			return X_ERROR;
		}

		for (int i = 0; i < MAX_TEMPLATES; i++)
		{
			Pos = pText.find(Templates[i].TxtID);
			if (Pos > -1)
			{
				fin.get(); //eats the whitespace after the block name.
				return Templates[i].TemplateID;
			}
		}
		////logger->LogAll(0, "SuperXLoader: Unknown block:", pText);
		return X_UNKNOWN;
	}

	void IO_Model_X::AvoidTemplate(void){
		char Token;

		fin.ignore(TEXT_BUFFER, '{');

		while (!fin.eof()){
			Token = fin.peek();
			if (Token == '{')
				AvoidTemplate();
			if (Token == '}')
			{
				fin.get();
				return;
			}
			fin.get();
		}
	}

	void IO_Model_X::Find(uchar pChar)
	{
		fin.ignore(TEXT_BUFFER, pChar);
	}

	char* IO_Model_X::SetUID(char pType)
	{
		//This is a quick hack to derive a Unique ID for blocks with
		//no identifier names like in the tiny_4anim.x example.

		_X_UID.Integer = rand();// 4 bytes semi-random, it's the same random number every app launch, but random enough... for now atleast
		_X_UID.Text[4] = pType; //We set the 5th byte with a significant character

		//If any of the first 4 bytes are under 32 we add 32
		//We want to avoid the occurrence of the char '\0' within
		//the first 4 bytes since this would truncate the text returned.
		if (_X_UID.Text[0] < 32) _X_UID.Text[0] += 32;
		if (_X_UID.Text[1] < 32) _X_UID.Text[1] += 32;
		if (_X_UID.Text[2] < 32) _X_UID.Text[2] += 32;
		if (_X_UID.Text[3] < 32) _X_UID.Text[3] += 32;
		return _X_UID.Text;
	}

	//////////////////////////////////////////////////////////
	//
	//       TRANSFORM MATRIX
	//
	//////////////////////////////////////////////////////////

	void IO_Model_X::ProcessFrameTransformMatrix(Bone* &pB)
	{
		char Text[TEXT_BUFFER];

		Find('{');
		for (int i = 0; i < 15; i++)
		{
			fin.getline(Text, TEXT_BUFFER, ',');
			pB->_MatrixPos[i] = TextToNum(Text);
		}
		fin.getline(Text, TEXT_BUFFER, ';');
		pB->_MatrixPos[15] = TextToNum(Text);
		//   pB->_TransMatrix = pB->_MatrixPos;
		Find('}');
	}

	//////////////////////////////////////////////////////////
	//
	//       BONE WITHIN SKELETTON
	//
	//////////////////////////////////////////////////////////

	void IO_Model_X::ProcessBone(Bone* pBone)
	{
		Bone* cBone;
		int16 Token;
		char Data[TEXT_BUFFER];

		cBone = new Bone();

		Token = fin.peek();
		if (Token != '{')
			fin >> cBone->_Name;
		else
			cBone->_Name = SetUID('B');

		if (pBone == 0)
		{
			////logger->LogAll(0, "SuperXLoader: Skeleton 1st bone:", cBone->_Name);
			_LoadSkeletton = cBone;
			_Object->_Skeletton = _LoadSkeletton;
		}
		else
		{
			////logger->LogAll(0, "SuperXLoader:", pBone->_Name, "", "->" + cBone->_Name);
			pBone->_Bones.push_back(cBone);
		}
		Find('{');
		Token = X_OBRACE;
		while (Token != X_EBRACE)
		{
			Token = ProcessBlock();
			switch (Token)
			{
			case X_COMMENT:
				break; //used for spaces and other kind of comments
			case X_EBRACE:
				return; //this is the end, my only friend ...
				break;
			case X_OBRACE:
				fin.getline(Data, TEXT_BUFFER, '}');
				cBone->_MeshName = Data;
				break;
			case X_FRAME:
				ProcessBone(cBone);
				break;
			case X_FRAMETRANSFORMMATRIX:
				ProcessFrameTransformMatrix(cBone);
				break;
			case X_MESH:
				ProcessMesh();
				cBone->_MeshName = _LoadMesh->_Name;
				break;
			default:
				AvoidTemplate();
				break;
			}
		}
	}

	//////////////////////////////////////////////////////////
	//
	//       MESH
	//
	//////////////////////////////////////////////////////////

	void IO_Model_X::ProcessMesh(void)
	{
		std::string Text;
		int16 Token;
		char Data[TEXT_BUFFER];

		_LoadMesh = new Mesh();
		if (!_Object->_Meshes.empty())
		{
			Mesh* LastMesh = _Object->_Meshes.back();
			_LoadMesh->_FirstVertex = LastMesh->_FirstVertex + LastMesh->_nVertices;
			_LoadMesh->_FirstFace = LastMesh->_FirstFace + LastMesh->_nFaces;
			_LoadMesh->_FirstTextureCoord = LastMesh->_FirstTextureCoord + LastMesh->_nTextureCoords;
			_LoadMesh->_FirstMaterial = LastMesh->_FirstMaterial + LastMesh->_nMaterials;
			if (_LoadMesh->_FirstTextureCoord < _LoadMesh->_FirstVertex)
			{
				_LoadMesh->_FirstTextureCoord = _LoadMesh->_FirstVertex;
			}
			_LoadMesh->_FirstNormal = LastMesh->_FirstNormal + LastMesh->_nNormals;
			if (_LoadMesh->_FirstNormal < _LoadMesh->_FirstVertex)
			{
				_LoadMesh->_FirstNormal = _LoadMesh->_FirstVertex;
			}

			////logger->LogAll(0, "SuperXLoader: Starting Vertex index:", _LoadMesh->_FirstVertex);
			////logger->LogAll(0, "SuperXLoader: Starting Face index:", _LoadMesh->_FirstFace);
			////logger->LogAll(0, "SuperXLoader: Starting TextureCoord index:", _LoadMesh->_FirstTextureCoord);
			////logger->LogAll(0, "SuperXLoader: Starting Normal index:", _LoadMesh->_FirstNormal);
			////logger->LogAll(0, "SuperXLoader: Starting Material index:", _LoadMesh->_FirstMaterial);
		}

		Token = fin.peek();
		if (Token != '{')
		{
			fin >> _LoadMesh->_Name;
		}
		else
		{
			_LoadMesh->_Name = SetUID('M');
		}

		Find('{');
		////logger->LogAll(0, "SuperXLoader: Mesh:", _LoadMesh->_Name);

		fin.getline(Data, TEXT_BUFFER, ';');
		_LoadMesh->_nVertices = (uint16)TextToNum(Data);
		////logger->LogAll(0, "SuperXLoader: Number of vertices:", _LoadMesh->_nVertices);
		_LoadMesh->_Vertices = new Vertex[_LoadMesh->_nVertices];
		//   _LoadMesh->_SkinnedVertices = new Frm::Vertex[_LoadMesh->_nVertices];
		for (int i = 0; i < _LoadMesh->_nVertices; i++)
		{
			fin.getline(Data, TEXT_BUFFER, ';');
			_LoadMesh->_Vertices[i].x = TextToNum(Data);
			fin.getline(Data, TEXT_BUFFER, ';');
			_LoadMesh->_Vertices[i].y = TextToNum(Data);
			fin.getline(Data, TEXT_BUFFER, ';');
			_LoadMesh->_Vertices[i].z = TextToNum(Data);
			fin.get();//eats either the comma or the semicolon at the end of each vertex description
		}

		fin.getline(Data, TEXT_BUFFER, ';');
		_LoadMesh->_nFaces = (uint16)TextToNum(Data);
		////logger->LogAll(0, "SuperXLoader: Number of Faces:", _LoadMesh->_nFaces);
		_LoadMesh->_Faces = new Face[_LoadMesh->_nFaces]();
		for (uint32 i = 0; i < _LoadMesh->_nFaces; ++i)
		{
			Find(';');
			fin.getline(Data, TEXT_BUFFER, ',');
			_LoadMesh->_Faces[i].data[0] = (uint16)TextToNum(Data);
			fin.getline(Data, TEXT_BUFFER, ',');
			_LoadMesh->_Faces[i].data[1] = (uint16)TextToNum(Data);
			fin.getline(Data, TEXT_BUFFER, ';');
			_LoadMesh->_Faces[i].data[2] = (uint16)TextToNum(Data);
			fin.get(); //eats either the comma or the semicolon at the end of each face description

			////logger->LogAll(0, "SuperXLoader: Face", std::to_string(i), ":",
			//	std::to_string(_LoadMesh->_Faces[i].data[0]), 
			//	std::to_string(_LoadMesh->_Faces[i].data[1]), 
			//	std::to_string(_LoadMesh->_Faces[i].data[2]));
		}

		Token = X_COMMENT;
		while (Token != X_EBRACE)
		{
			Token = ProcessBlock();
			switch (Token)
			{
			case X_COMMENT:
				break; //used for spaces and other kind of comments
			case X_EBRACE:
				_Object->_Meshes.push_back(_LoadMesh);
				return; //this is the end, my only friend ...
				break;
			case X_MESHNORMALS:
				ProcessMeshNormals();
				break;
			case X_MESHTEXTURECOORDS:
				ProcessMeshTextureCoords();
				break;
			case X_MESHMATERIALLIST:
				ProcessMeshMaterials();
				break;
			case X_SKINMESHHEADER:
				AvoidTemplate();
				break;
			case X_SKINWEIGHTS:
				ProcessSkinWeights();
				break;
			default:
				AvoidTemplate();
				break;
			}
		}
		_Object->_Meshes.push_back(_LoadMesh);
	}

	//////////////////////////////////////////////////////////
	//
	//       TEXTURE COORDS
	//
	//////////////////////////////////////////////////////////

	void IO_Model_X::ProcessMeshTextureCoords(void)
	{
		char Data[TEXT_BUFFER];

		Find('{');

		fin.getline(Data, TEXT_BUFFER, ';');
		_LoadMesh->_nTextureCoords = (uint16)TextToNum(Data);
		////logger->LogAll(0, "SuperXLoader: Number of Texture Coords:", _LoadMesh->_nTextureCoords);
		_LoadMesh->_TextureCoords = new TCoord[_LoadMesh->_nTextureCoords];
		for (int i = 0; i < _LoadMesh->_nTextureCoords; i++)
		{
			fin.getline(Data, TEXT_BUFFER, ';');
			_LoadMesh->_TextureCoords[i].data[0] = TextToNum(Data);
			fin.getline(Data, TEXT_BUFFER, ';');
			_LoadMesh->_TextureCoords[i].data[1] = TextToNum(Data);
			fin.get();//eats the comma or the semicolon at the end
		}
		Find('}');
	}

	//////////////////////////////////////////////////////////
	//
	//       MESH NORMAL VECTORS
	//
	//////////////////////////////////////////////////////////

	void IO_Model_X::ProcessMeshNormals(void)
	{
		char Data[TEXT_BUFFER];

		Find('{');
		fin.getline(Data, TEXT_BUFFER, ';');
		_LoadMesh->_nNormals = (uint16)TextToNum(Data);
		////logger->LogAll(0, "SuperXLoader: Number of normals:", _LoadMesh->_nNormals);
		_LoadMesh->_Normals = new Vector<float>[_LoadMesh->_nNormals];
		for (int i = 0; i < _LoadMesh->_nNormals; i++)
		{
			fin.getline(Data, TEXT_BUFFER, ';');
			_LoadMesh->_Normals[i].x = TextToNum(Data);
			fin.getline(Data, TEXT_BUFFER, ';');
			_LoadMesh->_Normals[i].y = TextToNum(Data);
			fin.getline(Data, TEXT_BUFFER, ';');
			_LoadMesh->_Normals[i].z = TextToNum(Data);
			fin.get();//eats the comma or the semicolon at the end
		}

		_LoadMesh->_FaceNormals = new Face[_LoadMesh->_nFaces];
		for (uint32 i = 0; i < _LoadMesh->_nFaces; i++)
		{
			Find(';');
			fin.getline(Data, TEXT_BUFFER, ',');
			_LoadMesh->_FaceNormals[i].data[0] = (uint16)TextToNum(Data);
			fin.getline(Data, TEXT_BUFFER, ',');
			_LoadMesh->_FaceNormals[i].data[1] = (uint16)TextToNum(Data);
			fin.getline(Data, TEXT_BUFFER, ';');
			_LoadMesh->_FaceNormals[i].data[2] = (uint16)TextToNum(Data);
			fin.get(); //eats either the comma or the semicolon at the end of each face description
			////logger->LogAll(0, "SuperXLoader: Face Normal index", std::to_string(i) + ":",
			//	std::to_string(_LoadMesh->_FaceNormals[i].data[0]), 
			//	std::to_string(_LoadMesh->_FaceNormals[i].data[1]), 
			//	std::to_string(_LoadMesh->_FaceNormals[i].data[2]));
		}

		Find('}');
	}


	//////////////////////////////////////////////////////////
	//
	//       MATERIALS USED IN MESH
	//
	//////////////////////////////////////////////////////////

	void IO_Model_X::ProcessMeshMaterials(void)
	{
		std::string Text;
		int16 Token;
		char Data[TEXT_BUFFER];

		Find('{');

		fin.getline(Data, TEXT_BUFFER, ';');
		_LoadMesh->_nMaterials = (uint16)TextToNum(Data);
		logger->LogAll(0, "SuperXLoader: Number of Materials:", Data);

		fin.getline(Data, TEXT_BUFFER, ';');
		_LoadMesh->_FaceMaterials = new uint16[(uint16)TextToNum(Data)];
		for (uint32 i = 0; i < _LoadMesh->_nFaces - 1; i++)
		{
			fin.getline(Data, TEXT_BUFFER, ',');
			_LoadMesh->_FaceMaterials[i] = (uint16)TextToNum(Data);
		}
		fin.getline(Data, TEXT_BUFFER, ';');
		_LoadMesh->_FaceMaterials[_LoadMesh->_nFaces - 1] = (uint16)TextToNum(Data);
		fin.get(); //eats the last semicolon

		Token = X_COMMENT;
		while (Token != X_EBRACE)
		{
			Token = ProcessBlock();
			switch (Token)
			{
			case X_COMMENT:
				break; //used for spaces and other kind of comments
			case X_EBRACE:
				return; //this is the end, my only friend ...
				break;
			case X_MATERIAL: ProcessMaterial();
				break;
			default:
				AvoidTemplate();
				break;
			}
		}
	}

	//////////////////////////////////////////////////////////
	//
	//       MATERIAL DESCRIPTION
	//
	//////////////////////////////////////////////////////////

	void IO_Model_X::ProcessMaterial(void)
	{
		std::string Text;
		int16 Token;
		char Data[TEXT_BUFFER];

		Material* NewMaterial = new Material;

		Find('{');

		fin.getline(Data, TEXT_BUFFER, ';');
		NewMaterial->diffuse.r = TextToNum(Data);
		fin.getline(Data, TEXT_BUFFER, ';');
		NewMaterial->diffuse.g = TextToNum(Data);
		fin.getline(Data, TEXT_BUFFER, ';');
		NewMaterial->diffuse.b = TextToNum(Data);
		fin.getline(Data, TEXT_BUFFER, ';');
		NewMaterial->diffuse.a = TextToNum(Data);

		fin.get(); //eats the last semicolon
		fin.getline(Data, TEXT_BUFFER, ';');
		NewMaterial->power = TextToNum(Data);

		fin.getline(Data, TEXT_BUFFER, ';');
		NewMaterial->specular.r = TextToNum(Data);
		fin.getline(Data, TEXT_BUFFER, ';');
		NewMaterial->specular.g = TextToNum(Data);
		fin.getline(Data, TEXT_BUFFER, ';');
		NewMaterial->specular.b = TextToNum(Data);

		fin.get();//eats the last semicolon

		fin.getline(Data, TEXT_BUFFER, ';');
		NewMaterial->emissive.r = TextToNum(Data);
		fin.getline(Data, TEXT_BUFFER, ';');
		NewMaterial->emissive.g = TextToNum(Data);
		fin.getline(Data, TEXT_BUFFER, ';');
		NewMaterial->emissive.b = TextToNum(Data);

		fin.get();//eats the last semicolon

		Token = X_COMMENT;
		while (Token != '}')
		{
			Token = ProcessBlock();
			switch (Token)
			{
			case X_COMMENT:
				break; //used for spaces and other kind of comments
			case X_EBRACE:
				_LoadMesh->_Materials.push_back(NewMaterial);
				return; //this is the end, my only friend ...
				break;
			case X_TEXTUREFILENAME:
				Find('{');
				Find('"');
				fin.getline(Data, TEXT_BUFFER, '"');
				NewMaterial->texturePath = Data;
				Find('}');
				break;
			default:
				AvoidTemplate();
				break;
			}
		}
		_LoadMesh->_Materials.push_back(NewMaterial);
	}

	//////////////////////////////////////////////////////////
	//
	//       SKIN WEIGHTS
	//
	//////////////////////////////////////////////////////////
	void IO_Model_X::ProcessSkinWeights(void)
	{
		Bone* cBone;
		std::string temp;
		char Data[TEXT_BUFFER];

		Find('{');
		Find('"');
		fin.getline(Data, TEXT_BUFFER, '"');
		temp = Data;
		cBone = _LoadSkeletton->IsName(temp);
		//   cBone->_Mesh = _LoadMesh;
		////logger->LogAll(0, "SuperXLoader: Skinning bone:", cBone->_Name);
		Find(';');

		fin.getline(Data, TEXT_BUFFER, ';');
		cBone->_nVertices = (uint16)TextToNum(Data);
		cBone->_Vertices = new uint16[cBone->_nVertices];
		for (uint32 i = 0; i < cBone->_nVertices - 1; i++)
		{
			fin.getline(Data, TEXT_BUFFER, ',');
			cBone->_Vertices[i] = (uint16)TextToNum(Data);
			////logger->LogAll(0, "SuperXLoader: Vertex:", atoi(Data));
		}
		fin.getline(Data, TEXT_BUFFER, ';');
		cBone->_Vertices[cBone->_nVertices - 1] = (uint16)TextToNum(Data);
		////logger->LogAll(0, "SuperXLoader: Vertex:", atoi(Data));

		cBone->_Weights = new float[cBone->_nVertices];
		for (uint32 i = 0; i < cBone->_nVertices - 1; i++)
		{
			fin.getline(Data, TEXT_BUFFER, ',');
			cBone->_Weights[i] = TextToNum(Data);
			//      MYTRACE("Weight:", atof(Data));/**/
			////logger->LogAll(0, "SuperXLoader: Weight:", atof(Data));
		}
		fin.getline(Data, TEXT_BUFFER, ';');
		cBone->_Weights[cBone->_nVertices - 1] = TextToNum(Data);
		//   MYTRACE("Weight:", atof(Data));/**/
		////logger->LogAll(0, "SuperXLoader: Weight:", atof(Data));

		for (int i = 0; i < 15; i++)
		{
			fin.getline(Data, TEXT_BUFFER, ',');
			cBone->_SkinOffset[i] = TextToNum(Data);
		}
		fin.getline(Data, TEXT_BUFFER, ';');
		cBone->_SkinOffset[15] = TextToNum(Data);
		Find('}');
	}

	/*************************************************
	NEW- NEW- NEW- NEW- NEW- NEW- NEW- NEW- NEW- NEW*/

	//////////////////////////////////////////////////////////
	//
	//       ANIMATION SET
	//
	//////////////////////////////////////////////////////////
	void IO_Model_X::ProcessAnimationSets(void)
	{
		//   std::string Text;
		int16 Token;
		//   char Data[TEXT_BUFFER];

		_MaxKey = 0;
		_LoadAnimationSet = new AnimationSet;

		Token = fin.peek();
		if (Token != '{')
		{
			fin >> _LoadAnimationSet->_Name;
		}
		else
		{
			_LoadAnimationSet->_Name = SetUID('A');
		}

		Find('{');
		////logger->LogAll(0, "SuperXLoader: Animation Set:", _LoadAnimationSet->_Name);

		Token = X_COMMENT;
		while (Token != X_EBRACE)
		{
			Token = ProcessBlock();
			switch (Token)
			{
			case X_COMMENT:
				break; //used for spaces and other kind of comments
			case X_EBRACE:
				_LoadAnimationSet->_MaxKey = _MaxKey;
				////logger->LogAll(0, "SuperXLoader: MaxKey:", _MaxKey);
				_Object->_AnimationSets.push_back(_LoadAnimationSet);
				return; //this is the end, my only friend ...
			case X_ANIMATION:
				ProcessAnimations(_LoadAnimationSet);
				break;
			default:
				AvoidTemplate();
				break;
			}
		}
		_LoadAnimationSet->_MaxKey = _MaxKey;
		////logger->LogAll(0, "SuperXLoader: MaxKey:", _MaxKey);
		_Object->_AnimationSets.push_back(_LoadAnimationSet);
	}

	//////////////////////////////////////////////////////////
	//
	//       ANIMATION
	//
	//////////////////////////////////////////////////////////
	void IO_Model_X::ProcessAnimations(AnimationSet* &pAS)
	{
		int16 Token;
		char Data[TEXT_BUFFER];
		Animation* TempAnimation = new Animation;

		Find('{');

		Token = X_COMMENT;
		while (Token != X_EBRACE)
		{
			Token = ProcessBlock();
			switch (Token)
			{
			case X_COMMENT:
				break; //used for spaces and other kind of comments
			case X_EBRACE:
				pAS->_Animations.push_back(TempAnimation);
				return; //this is the end, my only friend ...
				break;
			case X_OBRACE:
				Find('{');
				fin.getline(Data, TEXT_BUFFER, '}');
				Remove(' ', Data);
				TempAnimation->_BoneName = Data;
				////logger->LogAll(0, "SuperXLoader: Animated Bone:", TempAnimation->_BoneName);
				break;
			case X_ANIMATIONKEY:
				ProcessAnimationKeys(TempAnimation);
				break;
			default:
				AvoidTemplate(); break;
			}
		}
		pAS->_Animations.push_back(TempAnimation);
	}

	//////////////////////////////////////////////////////////
	//
	//       ANIMATION KEY
	//
	//////////////////////////////////////////////////////////
	void IO_Model_X::ProcessAnimationKeys(Animation* &pA)
	{
		int Type, Size;
		char Data[TEXT_BUFFER];
		RotateKey* 	TempRot;
		ScaleKey*	   TempScale;
		PositionKey* TempPos;
		MatrixKey*	TempMatrix;

		Find('{');
		fin.getline(Data, TEXT_BUFFER, ';');
		Type = (uint16)atoi(Data);
		fin.getline(Data, TEXT_BUFFER, ';');
		Size = (uint16)atoi(Data);

		switch (Type)
		{
		case 0:
			////logger->LogAll(0, "SuperXLoader:", Size, "Rotation Keys");
			pA->_Rotations.reserve(Size);
			while (Size--)
			{
				TempRot = new RotateKey;
				fin.getline(Data, TEXT_BUFFER, ';');
				TempRot->Time = (uint16)TextToNum(Data);
				if (TempRot->Time > _MaxKey)
				{
					_MaxKey = TempRot->Time;
				}
				Find(';');
				fin.getline(Data, TEXT_BUFFER, ',');
				TempRot->Rotation[0] = TextToNum(Data);
				fin.getline(Data, TEXT_BUFFER, ',');
				TempRot->Rotation[1] = TextToNum(Data);
				fin.getline(Data, TEXT_BUFFER, ',');
				TempRot->Rotation[2] = TextToNum(Data);
				fin.getline(Data, TEXT_BUFFER, ';');
				TempRot->Rotation[3] = TextToNum(Data);
				Find(';');
				fin.get();
				pA->_Rotations.push_back(TempRot);
			}
			break;
		case 1:
			////logger->LogAll(0, "SuperXLoader:", Size, "Scaling Keys");
			pA->_Scalings.reserve(Size);
			while (Size--)
			{
				TempScale = new ScaleKey;
				fin.getline(Data, TEXT_BUFFER, ';');
				TempScale->Time = (uint16)TextToNum(Data);
				if (TempScale->Time > _MaxKey)
				{
					_MaxKey = TempScale->Time;
				}
				Find(';');
				fin.getline(Data, TEXT_BUFFER, ',');
				TempScale->Scale.x = TextToNum(Data);
				fin.getline(Data, TEXT_BUFFER, ',');
				TempScale->Scale.y = TextToNum(Data);
				fin.getline(Data, TEXT_BUFFER, ';');
				TempScale->Scale.z = TextToNum(Data);
				Find(';');
				fin.get();
				pA->_Scalings.push_back(TempScale);
			}
			break;
		case 2:
			////logger->LogAll(0, "SuperXLoader:", Size, "Position Keys");
			pA->_Translations.reserve(Size);
			while (Size--)
			{
				TempPos = new PositionKey;
				fin.getline(Data, TEXT_BUFFER, ';');
				TempPos->Time = (uint16)TextToNum(Data);
				if (TempPos->Time > _MaxKey)
				{
					_MaxKey = TempPos->Time;
				}
				Find(';');
				fin.getline(Data, TEXT_BUFFER, ',');
				TempPos->Translation.x = TextToNum(Data);
				fin.getline(Data, TEXT_BUFFER, ',');
				TempPos->Translation.y = TextToNum(Data);
				fin.getline(Data, TEXT_BUFFER, ';');
				TempPos->Translation.z = TextToNum(Data);
				Find(';');
				fin.get();
				pA->_Translations.push_back(TempPos);
			}
			break;
		case 4:
			////logger->LogAll(0, "SuperXLoader:", Size, "Matrix Keys");
			pA->_Matrices.reserve(Size);
			while (Size--)
			{
				TempMatrix = new MatrixKey;
				fin.getline(Data, TEXT_BUFFER, ';');
				TempMatrix->Time = (uint16)TextToNum(Data);
				if (TempMatrix->Time > _MaxKey)
				{
					_MaxKey = TempMatrix->Time;
				}
				Find(';');
				for (int i = 0; i < 15; i++)
				{
					fin.getline(Data, TEXT_BUFFER, ',');
					TempMatrix->Matrix[i] = TextToNum(Data);
				}
				fin.getline(Data, TEXT_BUFFER, ';');
				TempMatrix->Matrix[15] = TextToNum(Data);
				Find(';');
				fin.get();
				pA->_Matrices.push_back(TempMatrix);
			}
			break;
		default:
			////logger->LogAll(0, "SuperXLoader: Unknown Type", Type, "...");
			break;
		}

		Find('}');
	}

	/***END*******************************************/

	//////////////////////////////////////////////////////////
	//
	//       MAP MESH TO BONES
	//
	//////////////////////////////////////////////////////////
	void IO_Model_X::MapMeshToBones(Bone* &pBone)
	{
		if (pBone->_MeshName.empty())
		{
			pBone->_MeshName = _LoadMesh->_Name;
		}

		////logger->LogAll(0, "SuperXLoader: Bone", pBone->_Name, "is linked to mesh ", pBone->_MeshName);

		if (!pBone->_Bones.empty())
		{
			for (std::list<Bone*>::iterator i = pBone->_Bones.begin(); i != pBone->_Bones.end(); i++)
			{
				if ((*i)->_MeshName.empty())
				{
					(*i)->_MeshName = pBone->_MeshName;
				}
				MapMeshToBones(*i);
			}
		}
	}
}