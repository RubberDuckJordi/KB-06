#ifndef _PENGINE_TYPES_H_
#define _PENGINE_TYPES_H_

#include <array>

namespace pengine
{
	typedef short int int16;
	typedef long int int32;
	typedef unsigned short int uint16;
	typedef unsigned long int uint32;
	typedef unsigned char uchar;
	typedef short int int16;
	typedef long int int32;
	typedef std::array<int, 3> Face;
	typedef std::array<float, 2> TCoord;
}
#endif
