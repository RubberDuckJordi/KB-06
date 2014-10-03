#ifndef _PENGINE_PENGINEDEFINITIONS_H_
#define _PENGINE_PENGINEDEFINITIONS_H_

namespace pengine
{
	typedef unsigned long       PENGINEDWORD;
	typedef unsigned char       PENGINEBYTE;

	// color definitions
	typedef PENGINEDWORD PENGINECOLOR;
	// end color definitions

	//windows definitions
	typedef unsigned long PENGINEDWORD;
	//end windows definitions

	// format definitions
#ifndef CMAKEFOURCC
#define CMAKEFOURCC(ch0, ch1, ch2, ch3)                              \
	((PENGINEDWORD)(PENGINEBYTE)(ch0) | ((PENGINEDWORD)(PENGINEBYTE)(ch1) << 8) | \
	((PENGINEDWORD)(PENGINEBYTE)(ch2) << 16) | ((PENGINEDWORD)(PENGINEBYTE)(ch3) << 24))

#endif /* defined(CMAKEFOURCC) */

#define M_PI 3.14159265358979323846f
#define RADIANS(degree) (M_PI * (degree) / 180.0f)
#define DEGREES(radian) (radian) * (180 / M_PI)

	struct CameraData
	{
		float x, y, z, lookAtX, lookAtY, lookAtZ, upVecX, upVecY, upVecZ;
	};

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

		FMT_UYVY = CMAKEFOURCC('U', 'Y', 'V', 'Y'),
		FMT_R8G8_B8G8 = CMAKEFOURCC('R', 'G', 'B', 'G'),
		FMT_YUY2 = CMAKEFOURCC('Y', 'U', 'Y', '2'),
		FMT_G8R8_G8B8 = CMAKEFOURCC('G', 'R', 'G', 'B'),
		FMT_DXT1 = CMAKEFOURCC('D', 'X', 'T', '1'),
		FMT_DXT2 = CMAKEFOURCC('D', 'X', 'T', '2'),
		FMT_DXT3 = CMAKEFOURCC('D', 'X', 'T', '3'),
		FMT_DXT4 = CMAKEFOURCC('D', 'X', 'T', '4'),
		FMT_DXT5 = CMAKEFOURCC('D', 'X', 'T', '5'),

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

		FMT_MULTI2_ARGB8 = CMAKEFOURCC('M', 'E', 'T', '1'),

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


	// pool definitions
	enum PENGINEPOOL
	{
		POOL_DEFAULT = 0,
		POOL_MANAGED = 1,
		POOL_SYSTEMMEM = 2,
		POOL_SCRATCH = 3,

		POOL_FORCE_DWORD = 0x7fffffff
	}; // end pool definitions

	// render state definitions
	enum PENGINERENDERSTATETYPE {
		PENGINE_ZENABLE = 7,    /* D3DZBUFFERTYPE (or TRUE/FALSE for legacy) */
		PENGINE_FILLMODE = 8,    /* D3DFILLMODE */
		PENGINE_SHADEMODE = 9,    /* D3DSHADEMODE */
		PENGINE_ZWRITEENABLE = 14,   /* TRUE to enable z writes */
		PENGINE_ALPHATESTENABLE = 15,   /* TRUE to enable alpha tests */
		PENGINE_LASTPIXEL = 16,   /* TRUE for last-pixel on lines */
		PENGINE_SRCBLEND = 19,   /* D3DBLEND */
		PENGINE_DESTBLEND = 20,   /* D3DBLEND */
		PENGINE_CULLMODE = 22,   /* D3DCULL */
		PENGINE_ZFUNC = 23,   /* D3DCMPFUNC */
		PENGINE_ALPHAREF = 24,   /* D3DFIXED */
		PENGINE_ALPHAFUNC = 25,   /* D3DCMPFUNC */
		PENGINE_DITHERENABLE = 26,   /* TRUE to enable dithering */
		PENGINE_ALPHABLENDENABLE = 27,   /* TRUE to enable alpha blending */
		PENGINE_FOGENABLE = 28,   /* TRUE to enable fog blending */
		PENGINE_SPECULARENABLE = 29,   /* TRUE to enable specular */
		PENGINE_FOGCOLOR = 34,   /* D3DCOLOR */
		PENGINE_FOGTABLEMODE = 35,   /* D3DFOGMODE */
		PENGINE_FOGSTART = 36,   /* Fog start (for both vertex and pixel fog) */
		PENGINE_FOGEND = 37,   /* Fog end      */
		PENGINE_FOGDENSITY = 38,   /* Fog density  */
		PENGINE_RANGEFOGENABLE = 48,   /* Enables range-based fog */
		PENGINE_STENCILENABLE = 52,   /* BOOL enable/disable stenciling */
		PENGINE_STENCILFAIL = 53,   /* D3DSTENCILOP to do if stencil test fails */
		PENGINE_STENCILZFAIL = 54,   /* D3DSTENCILOP to do if stencil test passes and Z test fails */
		PENGINE_STENCILPASS = 55,   /* D3DSTENCILOP to do if both stencil and Z tests pass */
		PENGINE_STENCILFUNC = 56,   /* D3DCMPFUNC fn.  Stencil Test passes if ((ref & mask) stencilfn (stencil & mask)) is true */
		PENGINE_STENCILREF = 57,   /* Reference value used in stencil test */
		PENGINE_STENCILMASK = 58,   /* Mask value used in stencil test */
		PENGINE_STENCILWRITEMASK = 59,   /* Write mask applied to values written to stencil buffer */
		PENGINE_TEXTUREFACTOR = 60,   /* D3DCOLOR used for multi-texture blend */
		PENGINE_WRAP0 = 128,  /* wrap for 1st texture coord. set */
		PENGINE_WRAP1 = 129,  /* wrap for 2nd texture coord. set */
		PENGINE_WRAP2 = 130,  /* wrap for 3rd texture coord. set */
		PENGINE_WRAP3 = 131,  /* wrap for 4th texture coord. set */
		PENGINE_WRAP4 = 132,  /* wrap for 5th texture coord. set */
		PENGINE_WRAP5 = 133,  /* wrap for 6th texture coord. set */
		PENGINE_WRAP6 = 134,  /* wrap for 7th texture coord. set */
		PENGINE_WRAP7 = 135,  /* wrap for 8th texture coord. set */
		PENGINE_CLIPPING = 136,
		PENGINE_LIGHTING = 137,
		PENGINE_AMBIENT = 139,
		PENGINE_FOGVERTEXMODE = 140,
		PENGINE_COLORVERTEX = 141,
		PENGINE_LOCALVIEWER = 142,
		PENGINE_NORMALIZENORMALS = 143,
		PENGINE_DIFFUSEMATERIALSOURCE = 145,
		PENGINE_SPECULARMATERIALSOURCE = 146,
		PENGINE_AMBIENTMATERIALSOURCE = 147,
		PENGINE_EMISSIVEMATERIALSOURCE = 148,
		PENGINE_VERTEXBLEND = 151,
		PENGINE_CLIPPLANEENABLE = 152,
		PENGINE_POINTSIZE = 154,   /* float point size */
		PENGINE_POINTSIZE_MIN = 155,   /* float point size min threshold */
		PENGINE_POINTSPRITEENABLE = 156,   /* BOOL point texture coord control */
		PENGINE_POINTSCALEENABLE = 157,   /* BOOL point size scale enable */
		PENGINE_POINTSCALE_A = 158,   /* float point attenuation A value */
		PENGINE_POINTSCALE_B = 159,   /* float point attenuation B value */
		PENGINE_POINTSCALE_C = 160,   /* float point attenuation C value */
		PENGINE_MULTISAMPLEANTIALIAS = 161,  // BOOL - set to do FSAA with multisample buffer
		PENGINE_MULTISAMPLEMASK = 162,  // DWORD - per-sample enable/disable
		PENGINE_PATCHEDGESTYLE = 163,  // Sets whether patch edges will use float style tessellation
		PENGINE_DEBUGMONITORTOKEN = 165,  // DEBUG ONLY - token to debug monitor
		PENGINE_POINTSIZE_MAX = 166,   /* float point size max threshold */
		PENGINE_INDEXEDVERTEXBLENDENABLE = 167,
		PENGINE_COLORWRITEENABLE = 168,  // per-channel write enable
		PENGINE_TWEENFACTOR = 170,   // float tween factor
		PENGINE_BLENDOP = 171,   // D3DBLENDOP setting
		PENGINE_POSITIONDEGREE = 172,   // NPatch position interpolation degree. D3DDEGREE_LINEAR or D3DDEGREE_CUBIC (default)
		PENGINE_NORMALDEGREE = 173,   // NPatch normal interpolation degree. D3DDEGREE_LINEAR (default) or D3DDEGREE_QUADRATIC
		PENGINE_SCISSORTESTENABLE = 174,
		PENGINE_SLOPESCALEDEPTHBIAS = 175,
		PENGINE_ANTIALIASEDLINEENABLE = 176,
		PENGINE_MINTESSELLATIONLEVEL = 178,
		PENGINE_MAXTESSELLATIONLEVEL = 179,
		PENGINE_ADAPTIVETESS_X = 180,
		PENGINE_ADAPTIVETESS_Y = 181,
		PENGINE_ADAPTIVETESS_Z = 182,
		PENGINE_ADAPTIVETESS_W = 183,
		PENGINE_ENABLEADAPTIVETESSELLATION = 184,
		PENGINE_TWOSIDEDSTENCILMODE = 185,   /* BOOL enable/disable 2 sided stenciling */
		PENGINE_CCW_STENCILFAIL = 186,   /* D3DSTENCILOP to do if ccw stencil test fails */
		PENGINE_CCW_STENCILZFAIL = 187,   /* D3DSTENCILOP to do if ccw stencil test passes and Z test fails */
		PENGINE_CCW_STENCILPASS = 188,   /* D3DSTENCILOP to do if both ccw stencil and Z tests pass */
		PENGINE_CCW_STENCILFUNC = 189,   /* D3DCMPFUNC fn.  ccw Stencil Test passes if ((ref & mask) stencilfn (stencil & mask)) is true */
		PENGINE_COLORWRITEENABLE1 = 190,   /* Additional ColorWriteEnables for the devices that support D3DPMISCCAPS_INDEPENDENTWRITEMASKS */
		PENGINE_COLORWRITEENABLE2 = 191,   /* Additional ColorWriteEnables for the devices that support D3DPMISCCAPS_INDEPENDENTWRITEMASKS */
		PENGINE_COLORWRITEENABLE3 = 192,   /* Additional ColorWriteEnables for the devices that support D3DPMISCCAPS_INDEPENDENTWRITEMASKS */
		PENGINE_BLENDFACTOR = 193,   /* D3DCOLOR used for a constant blend factor during alpha blending for devices that support D3DPBLENDCAPS_BLENDFACTOR */
		PENGINE_SRGBWRITEENABLE = 194,   /* Enable rendertarget writes to be DE-linearized to SRGB (for formats that expose D3DUSAGE_QUERY_SRGBWRITE) */
		PENGINE_DEPTHBIAS = 195,
		PENGINE_WRAP8 = 198,   /* Additional wrap states for vs_3_0+ attributes with D3DDECLUSAGE_TEXCOORD */
		PENGINE_WRAP9 = 199,
		PENGINE_WRAP10 = 200,
		PENGINE_WRAP11 = 201,
		PENGINE_WRAP12 = 202,
		PENGINE_WRAP13 = 203,
		PENGINE_WRAP14 = 204,
		PENGINE_WRAP15 = 205,
		PENGINE_SEPARATEALPHABLENDENABLE = 206,  /* TRUE to enable a separate blending function for the alpha channel */
		PENGINE_SRCBLENDALPHA = 207,  /* SRC blend factor for the alpha channel when PENGINE_SEPARATEDESTALPHAENABLE is TRUE */
		PENGINE_DESTBLENDALPHA = 208,  /* DST blend factor for the alpha channel when PENGINE_SEPARATEDESTALPHAENABLE is TRUE */
		PENGINE_BLENDOPALPHA = 209,  /* Blending operation for the alpha channel when PENGINE_SEPARATEDESTALPHAENABLE is TRUE */

		PENGINE_FORCE_DWORD = 0x7fffffff, /* force 32-bit size enum */
	}; // end render state definitions
}

#endif // end penginedefinitions