#ifndef _XMATERIAL_H
#define _XMATERIAL_H

#include "Types.h"
#include "Array.h"

class XMaterial
{
public:
	bool IsName(std::string &pText){ if (strcmp(pText.c_str(), _Name.c_str()) == 0) return true; return false; };
	std::string _Name;
	Color4 _FaceColor;
	float _power;
	Color3 _SpecularColor, _EmissiveColor;
	uint16 _TextID;
	std::string _TextureName;
};
#endif