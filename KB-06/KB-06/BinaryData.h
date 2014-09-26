#ifndef _RESOURCE_BINARYDATA_H_
#define _RESOURCE_BINARYDATA_H_

namespace pengine
{
	struct BinaryData{
		std::string fileName;
		char* rawData;
		unsigned int size;
	};
}
#endif