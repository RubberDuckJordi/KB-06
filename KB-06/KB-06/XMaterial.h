#ifndef _PENGINE_XMATERIAL_H
#define _PENGINE_XMATERIAL_H

#include "Types.h"
#include "Array.h"
#include "RGBAColor.h"

namespace pengine
{
	class XMaterial
	{
	public:
		bool IsName(std::string &pText)
		{
			if (strcmp(pText.c_str(), _Name.c_str()) == 0)
			{
				return true;
			}
			return false;
		}
		std::string _Name;
		Color4 _FaceColor;
		float _power;
		Color3 _SpecularColor, _EmissiveColor;
		uint16 _TextID;
		std::string _TextureName;

		RGBAColor   Diffuse;        /* Diffuse color RGBA */
		RGBAColor   Ambient;        /* Ambient color RGB */
		RGBAColor   Specular;       /* Specular 'shininess' */
		RGBAColor   Emissive;       /* Emissive color RGB */
		float       Power;          /* Sharpness if specular highlight */
	};
}
#endif