#ifndef _TRECT_H_
#define _TRECT_H_
template <typename T>
class trect
{
public:
	T xs, ys, xe, ye;
	trect(void) : xs(0), ys(0), xe(0), ye(0)
	{
	};
	trect(const trect<T> &prect)
	{
		xs = prect.xs;
		ys = prect.ys;
		xe = prect.xe;
		ye = prect.ye;
	};
	trect<T>& operator=(const trect<T> &prect)
	{
		xs = prect.xs;
		ys = prect.ys;
		xe = prect.xe;
		ye = prect.ye;
		return *this;
	};
	trect<T>& operator+=(const Vector<T> &pV)
	{
		xs += pV.x;
		ys += pV.y;
		xe += pV.x;
		ye += pV.y;
		return *this;
	};

	/*
	trect<T>& operator+=(Vector<T> &pV)
	{
	xs += pV[VX];
	ys += pV[VY];
	xe += pV[VX];
	ye += pV[VY];
	return *this;
	};*/

	trect(const T pxs, const T pys, const T pxe, const T pye)
	{
		xs = pxs;
		ys = pys;
		xe = pxe;
		ye = pye;
	};
	inline void Set(const T pxs, const T pys, const T pxe, const T pye)
	{
		xs = pxs;
		ys = pys;
		xe = pxe;
		ye = pye;
	};
	bool _fastcall InRect(const T &px, const T &py)
	{
		if (px < xs)
		{
			return false;
		}
		if (px > xe)
		{
			return false;
		}
		if (py < ys)
		{
			return false;
		}
		if (py > ye)
		{
			return false;
		}
		return true;
	};
	bool _fastcall InRect(const Vector<T> &pv)
	{
		if (pv.x < xs)
		{
			return false;
		}
		if (pv.x > xe)
		{
			return false;
		}
		if (pv.y < ys)
		{
			return false;
		}
		if (pv.y > ye)
		{
			return false;
		}
		return true;
	};

	/*
	bool _fastcall InRect( Vector<T> &pv)
	{
	if (pv[VX] < xs)
	{
	return false;
	}
	if (pv[VX] > xe)
	{
	return false;
	}
	if (pv[VY] < ys)
	{
	return false;
	}
	if (pv[VY] > ye)
	{
	return false;
	}
	return true;
	};*/

	bool _fastcall InRect(const trect<T> &prect)
	{
		if ((prect.xe <= xe) &&
			(prect.ye <= ye) &&
			(prect.xs >= xs) &&
			(prect.ys >= ys))
		{
			return true;
		}
		return false;
	}
	bool _fastcall Intersect(const trect<T> &prect)
	{
		if (prect.xe < xs)
		{
			return false;
		}
		if (prect.xs > xe)
		{
			return false;
		}
		if (prect.ye < ys)
		{
			return false;
		}
		if (prect.ys > ye)
		{
			return false;
		}
		return true;
	};
	bool _fastcall Union(const trect<T> &prect)
	{
		if (!Intersect(prect))
		{
			return false;
		}
		if (xs < prect.xs)
		{
			xs = prect.xs;
		}
		if (ys < prect.ys)
		{
			ys = prect.ys;
		}
		if (xe > prect.xe)
		{
			xe = prect.xe;
		}
		if (ye > prect.ye)
		{
			ye = prect.ye;
		}
		return true;
	};
};
#endif