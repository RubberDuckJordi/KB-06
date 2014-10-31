#ifndef _PENGINE_RGBACOLOR_H_
#define _PENGINE_RGBACOLOR_H_

namespace pengine
{
	struct RGBAColor
	{
		RGBAColor()
		{
			r = g = b = a = 0.0f;
		}
		RGBAColor(float _r, float _g, float _b, float _a)
		{
			r = _r;
			g = _g;
			b = _b;
			a = _a;
		}
		float r, g, b, a;
	};
}
#endif