#ifndef _PENGINEDEFINITIONS_H_
#define _PENGINEDEFINITIONS_H_

// #include <float.h>

typedef unsigned long       PENGINEDWORD;
typedef unsigned char       PENGINEBYTE;

// color definitions
typedef PENGINEDWORD PENGINECOLOR;
// end color definitions

// format definitions
#ifndef MAKEFOURCC
#define MAKEFOURCC(ch0, ch1, ch2, ch3)                              \
	((PENGINEDWORD)(PENGINEBYTE)(ch0) | ((PENGINEDWORD)(PENGINEBYTE)(ch1) << 8) | \
	((PENGINEDWORD)(PENGINEBYTE)(ch2) << 16) | ((PENGINEDWORD)(PENGINEBYTE)(ch3) << 24))
#endif /* defined(MAKEFOURCC) */



enum PENGINEFORMAT
{
	FMT_UNKNOWN = 0,

	FMT_R8G8B8 = 20,
	FMT_A8R8G8B8 = 21,
	FMT_X8R8G8B8 = 22,
	FMT_R5G6B5 = 23,
	FMT_X1R5G5B5 = 24,
	FMT_A1R5G5B5 = 25,
	FMT_A4R4G4B4 = 26,
	FMT_R3G3B2 = 27,
	FMT_A8 = 28,
	FMT_A8R3G3B2 = 29,
	FMT_X4R4G4B4 = 30,
	FMT_A2B10G10R10 = 31,
	FMT_A8B8G8R8 = 32,
	FMT_X8B8G8R8 = 33,
	FMT_G16R16 = 34,
	FMT_A2R10G10B10 = 35,
	FMT_A16B16G16R16 = 36,

	FMT_A8P8 = 40,
	FMT_P8 = 41,

	FMT_L8 = 50,
	FMT_A8L8 = 51,
	FMT_A4L4 = 52,

	FMT_V8U8 = 60,
	FMT_L6V5U5 = 61,
	FMT_X8L8V8U8 = 62,
	FMT_Q8W8V8U8 = 63,
	FMT_V16U16 = 64,
	FMT_A2W10V10U10 = 67,

	FMT_UYVY = MAKEFOURCC('U', 'Y', 'V', 'Y'),
	FMT_R8G8_B8G8 = MAKEFOURCC('R', 'G', 'B', 'G'),
	FMT_YUY2 = MAKEFOURCC('Y', 'U', 'Y', '2'),
	FMT_G8R8_G8B8 = MAKEFOURCC('G', 'R', 'G', 'B'),
	FMT_DXT1 = MAKEFOURCC('D', 'X', 'T', '1'),
	FMT_DXT2 = MAKEFOURCC('D', 'X', 'T', '2'),
	FMT_DXT3 = MAKEFOURCC('D', 'X', 'T', '3'),
	FMT_DXT4 = MAKEFOURCC('D', 'X', 'T', '4'),
	FMT_DXT5 = MAKEFOURCC('D', 'X', 'T', '5'),

	FMT_D16_LOCKABLE = 70,
	FMT_D32 = 71,
	FMT_D15S1 = 73,
	FMT_D24S8 = 75,
	FMT_D24X8 = 77,
	FMT_D24X4S4 = 79,
	FMT_D16 = 80,

	FMT_D32F_LOCKABLE = 82,
	FMT_D24FS8 = 83,




	FMT_L16 = 81,

	FMT_VERTEXDATA = 100,
	FMT_INDEX16 = 101,
	FMT_INDEX32 = 102,

	FMT_Q16W16V16U16 = 110,

	FMT_MULTI2_ARGB8 = MAKEFOURCC('M', 'E', 'T', '1'),

	// Floating point surface formats

	// s10e5 formats (16-bits per channel)
	FMT_R16F = 111,
	FMT_G16R16F = 112,
	FMT_A16B16G16R16F = 113,

	// IEEE s23e8 formats (32-bits per channel)
	FMT_R32F = 114,
	FMT_G32R32F = 115,
	FMT_A32B32G32R32F = 116,

	FMT_CxV8U8 = 117,




	FMT_FORCE_DWORD = 0x7fffffff
}; // end format definitions


// material definitions

// colorvalue definitions


struct PENGINECOLORVALUE {
	float r;
	float g;
	float b;
	float a;
};



struct PENGINEMATERIAL
{
	PENGINECOLORVALUE   Diffuse;        /* Diffuse color RGBA */
	PENGINECOLORVALUE   Ambient;        /* Ambient color RGB */
	PENGINECOLORVALUE   Specular;       /* Specular 'shininess' */
	PENGINECOLORVALUE   Emissive;       /* Emissive color RGB */
	float           Power;          /* Sharpness if specular highlight */
}; // end material definitions


// pool definitions


enum PENGINEPOOL 
{
	POOL_DEFAULT = 0,
	POOL_MANAGED = 1,
	POOL_SYSTEMMEM = 2,
	POOL_SCRATCH = 3,

	POOL_FORCE_DWORD = 0x7fffffff
}; // end pool definitions

#endif // end penginedefinitions