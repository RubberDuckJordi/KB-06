#ifndef _PENGINE_BINARYDATA_H_
#define _PENGINE_BINARYDATA_H_

#include <string>

/*
Struct to hold binary data that has been loaded from a file
Is used for textures
*/

namespace pengine
{
	struct BinaryData
	{
		std::string fileName;
		char* rawData;
		unsigned int size;
	};
}
#endif