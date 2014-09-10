#ifndef _MATERIAL_H_
#define _MATERIAL_H_
#include "RGBColor.h"
struct Material {
	char* name;
	RGBColor ambientColor;
	RGBColor diffuseColor;
	RGBColor SpecularColor;
};
#endif