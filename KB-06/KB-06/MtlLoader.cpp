#include "stdafx.h"
#include "MtlLoader.h"
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include <vector>
#include "Material.h"
#include "StringHelper.h"


Material MtlLoader::Load(std::string file){
	std::ifstream ifs("cube.mtl", std::ifstream::in);
	std::string line;
	std::vector<std::string> elements;

	Material material;
	material.ambientColor.b = 1.0f;
	while (ifs.good()) {
		getline(ifs, line);
		elements = StringHelper::split(line, ' ');
		if (elements.size() > 0){
			if (elements[0] == "mtllib "){

			}
		}
	}
	return material;
}