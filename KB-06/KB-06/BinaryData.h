#ifndef _PENGINE_BINARYDATA_H_
#define _PENGINE_BINARYDATA_H_

#include <string>

namespace pengine
{
	struct BinaryData{
		std::string fileName;
		char* rawData;
		unsigned int size;
	};
}
#endif