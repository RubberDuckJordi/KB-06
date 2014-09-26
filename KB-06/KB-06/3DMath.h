/////////////////////////////////////////////////////////
// Frm_3DMath.h
// Declares Vector, matrix, rectangles and defines special
// array elements
/////////////////////////////////////////////////////////

#ifndef FRM_MATH_H
#define FRM_MATH_H

//#include <mem.h>//unknown, probably some OpenGL/GLut
#include <math.h>

#define MINFLOAT 1.17549435E-38F

//Vector description/////////////////////////
template <typename T>
class Vector
{
public:
	T x, y, z;
	Vector(void) : x(0), y(0), z(0)
	{
	};
	Vector(T px, T py, T pz) : x(px), y(py), z(pz)
	{
	};
	Vector(const Vector<T> &pv) :x(pv.x), y(pv.y), z(pv.z)
	{
	};
	Vector(const T* &pv)
	{
		x = pv[0];
		y = pv[1];
		z = pv[2];
	};

	Vector<T>& operator=(const Vector<T> &pv)
	{
		x = pv.x;
		y = pv.y;
		z = pv.z;
		return *this;
	};

	inline void Set(T px, T py, T pz)
	{
		x = px;
		y = py;
		z = pz;
	};
	bool operator>(const Vector<T> &pv)
	{
		return (x + y) > (pv.x + pv.y);
	};

	T operator[](int index)const
	{
		if (index == 1)
		{
			return y;
		}
		if (index == 2)
		{
			return z;
		}
		return x;
	};
	T& operator[](int index)
	{
		if (index == 1)
		{
			return y;
		}
		if (index == 2)
		{
			return z;
		}
		return x;
	};

	Vector<T> operator+(Vector<T> pv)const
	{
		return Vector<T>((T)(x + pv.x), (T)(y + pv.y), (T)(z + pv.z));
	};
	Vector<T> operator-(Vector<T>& pv)const
	{
		return Vector<T>((T)(x - pv.x), (T)(y - pv.y), (T)(z - pv.z));
	};
	Vector<T> operator*(T pT)const
	{
		return Vector<T>((T)(pT * x), (T)(pT * y), (T)(pT * z));
	};

	void Normalize(void)
	{
		Vector<T> pv((T)(x*x), (T)(y*y), (T)(z*z));
		T fLength = (T)(1.0f / (float)(pv.x + pv.y + pv.z));
		if (fLength < 1e-08)
		{
			return;
		}
		x = (T)(pv.x * fLength);
		y = (T)(pv.y * fLength);
		z = (T)(pv.z * fLength);
	};
	T Dot(Vector<T> pV)const
	{
		return (T)(x*pV.x + y*pV.y + z*pV.z);
	};
	Vector<T> Cross(Vector<T> pV)const
	{
		return Vector<T>((T)(y * pV.z - z * pV.y), (T)(z * pV.x - x * pV.z), (T)(x * pV.y - y * pV.x));
	};
	Vector<T> UnitCross(Vector<T> pV)const
	{
		Vector<T> pR((T)(y * pV.z - z * pV.y), (T)(z * pV.x - x * pV.z), (T)(x * pV.y - y * pV.x));
		pR.Normalize();
		return pR;
	};
};

typedef Vector<float> vector;

template<typename T, int size>
struct Array
{
	T data[size];
	Array(void)
	{
		memset(data, 0, size * sizeof(T));
	};
	Array(const Array<T, size> &pA)
	{
		memcpy(data, pA.data, size * sizeof(T));
	};
	Array(const T* pT)
	{
		memcpy(data, pT, size * sizeof(T));
	};

	Array<T, size>& operator=(Array<T, size> pA)
	{
		memcpy(data, pA.data, size * sizeof(T)); return *this;
	};
	Array<T, size>& operator+=(Array<T, size> pA);
	Array<T, size> operator*(const T pScalar);
	Array<T, size> operator+(Array<T, size> pA);
	Array<T, size> operator-(Array<T, size> pA);
	T operator[](int index)const
	{
		return data[index];
	};
	T& operator[](int index)
	{
		return data[index];
	};
};

typedef Array<unsigned short, 3> Face;
typedef Array<float, 3> Vertex;
typedef Array<float, 2> TCoord;
typedef Array<float, 4> Color4;
typedef Array<float, 3> Color3;

template<typename T>
Array<T, 4> Set4(T px, T py, T pz, T pw)
{
	T data[4];
	data[0] = px;
	data[1] = py;
	data[2] = pz;
	data[3] = pw;
	return Array<T, 4>(data);
};

template<typename T>
Array<T, 3> Set3(T px, T py, T pz)
{
	T data[3];
	data[0] = px;
	data[1] = py;
	data[2] = pz;
	return Array<T, 3>(data);
};

template<typename T>
Array<T, 2> Set2(T pu, T pv)
{
	T data[2];
	data[0] = pu;
	data[1] = pv;
	return Array<T, 2>(data);
};

template <typename T>
class Matrix
{
public:
	T data[16];
	Matrix(void)
	{
		memset(data, 0, 16 * sizeof(T));
	};
	Matrix(const Matrix<T> &pm)
	{
		memcpy(data, pm.data, 16 * sizeof(T));
	};
	Matrix(const T* pT)
	{
		memcpy(data, pT, 16 * sizeof(T));
	};
	void Zero(void)
	{
		memset(data, 0, 16 * sizeof(T));
	};
	void Identity(void)
	{
		memset(data, 0, 16 * sizeof(T));
		data[0] = (T)1;
		data[5] = (T)1;
		data[10] = (T)1;
		data[15] = (T)1;
	};
	Matrix<T>& operator=(const Matrix<T> &pm)
	{
		memcpy(data, pm.data, 16 * sizeof(T));
		return *this;
	};
	Matrix<T> operator+(Matrix<T> pm);
	Matrix<T> operator-(Matrix<T> pm);
	Matrix<T> operator*(Matrix<T> pm);
	Matrix<T>& operator*=(Matrix<T> &pm);
	Matrix<T> operator*(T pT);
	Vector<T> operator*(const Vector<T>& pV);
	Array<T, 3> operator*(const Array<T, 3>& pV);

	T operator[](int index)const
	{
		return data[index];
	};
	T& operator[](int index)
	{
		return data[index];
	};

	T _fastcall Index(int pRow, int pCol)const
	{
		return data[(pRow << 2) + pCol];
	};
	T operator()(int pRow, int pCol)const
	{
		return data[(pRow << 2) + pCol];
	};
	T& operator()(int pRow, int pCol)
	{
		return data[(pRow << 2) + pCol];
	};
	Vector<T> GetRow(int index)
	{
		index <<= 2;
		return Vector<T>(data[index++], data[index++], data[index]);
	};
	Vector<T> GetColumn(int index)
	{
		return Vector<T>(data[index], data[index + 4], data[index + 8]);
	};
	void ScalingMatrix(const Vector<T> &pvT);
	void TranslationMatrix(const Array<T, 3> &pAT);
	void QuaternionMatrix(T &x, T &y, T &z, T &w);

private:
	int k, l, row, col;
};

typedef Matrix<float> matrix;
//typedef matrix<float> Matrix4F;

template <typename T>
class Quaternion {
public:
	T data[4];
	Quaternion(void)
	{
		memset(data, 0, 4 * sizeof(T));
	};
	Quaternion(const Quaternion<T> &pq)
	{
		memcpy(data, pq.data, 4 * sizeof(T));
	};
	Quaternion(const T* pT)
	{
		memcpy(data, pT, 4 * sizeof(T));
	};
	void Zero(void)
	{
		memset(data, 0, 4 * sizeof(T));
	};
	T operator[](int index)const
	{
		return data[index];
	};
	T& operator[](int index)
	{
		return data[index];
	};
	Quaternion<T>& operator=(const Quaternion<T> &pq)
	{
		memcpy(data, pq.data, 4 * sizeof(T));
		return *this;
	};
	Quaternion<T> operator+(Quaternion<T> pq);
	Quaternion<T> operator*(Quaternion<T> pq);
	Quaternion<T> operator*(T pT);
	T Dot(Quaternion<T> &pq);
	Quaternion<T> Slerp(T pT, Quaternion<T> &pq);
private:
	float qACos(float pValue);
};

typedef Quaternion<float> quaternion;

//Rectangle description///////////////////////
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

//// Implementation details ////////////////////

template<typename T, int size>
Array<T, size>& Array<T, size>::operator+=(Array<T, size> pA)
{
	for (int i = 0; i < size; i++)
	{
		data[i] += pA.data[i];
	}
	return *this;
}

template<typename T, int size>
Array<T, size> Array<T, size>::operator*(const T pScalar)
{
	T rdata[size];
	memcpy(rdata, data, size * sizeof(T));
	for (int i = 0; i < size; i++)
	{
		rdata[i] *= pScalar;
	}
	return Array<T, size>(rdata);
}

template<typename T, int size>
Array<T, size> Array<T, size>::operator+(Array<T, size> pA)
{
	T rdata[size];
	for (int i = 0; i < size; i++)
	{
		rdata[i] = data[i] + pA.data[i];
	}
	return Array<T, size>(rdata);
};

template<typename T, int size>
Array<T, size> Array<T, size>::operator-(Array<T, size> pA)
{
	T rdata[size];
	for (int i = 0; i < size; i++)
	{
		rdata[i] = data[i] - pA.data[i];
	}
	return Array<T, size>(rdata);
};

template<typename T>
Matrix<T> Matrix<T>::operator+(Matrix<T> pm)
{
	T Rdata[16];
	for (k = 0; k < 16; k++)
	{
		Rdata[k] = data[k] + pm.data[k];
	}
	return Matrix<T>(Rdata);
}

template<typename T>
Matrix<T> Matrix<T>::operator-(Matrix<T> pm)
{
	T Rdata[16];
	for (k = 0; k < 16; k++)
	{
		Rdata[k] = data[k] - pm.data[k];
	}
	return Matrix<T>(Rdata);
}

template<typename T>
Matrix<T> Matrix<T>::operator*(Matrix<T> pm)
{
	T Rdata[16];
	for (row = 0; row < 16; row += 4)
	{
		for (col = 0; col < 4; col++)
		{
			l = 0;
			Rdata[row + col] = 0;
			for (k = 0; k < 4; k++, l += 4)
			{
				Rdata[row + col] += data[row + k] * pm.data[l + col];
			}
		}
	}
	return Matrix<T>(Rdata);
}

template<typename T>
Matrix<T>& Matrix<T>::operator*=(Matrix<T> &pm)
{
	T Rdata[16];
	for (row = 0; row < 16; row += 4)
	{
		for (col = 0; col < 4; col++)
		{
			l = 0;
			Rdata[row + col] = 0;
			for (k = 0; k < 4; k++, l += 4)
			{
				Rdata[row + col] += data[row + k] * pm.data[l + col];
			}
		}
	}
	memcpy(data, Rdata, 16 * sizeof(T));
	return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(T pT)
{
	T Rdata[16];
	memcpy(Rdata, data, 16 * sizeof(T));
	for (k = 0; k < 16; k++)
	{
		Rdata[k] *= pT;
	}
	return Matrix<T>(Rdata);
}

template<typename T>
Vector<T> Matrix<T>::operator*(const Vector<T>& pV)
{
	T vdata[4], pvdata[4];
	pvdata[0] = pV.x;
	pvdata[1] = pV.y;
	pvdata[2] = pV.z;
	pvdata[3] = 0;
	for (col = 0; col < 4; col++)
	{
		vdata[row] = 0;
		k = 0;
		for (row = 0; row < 4; row++, k += 4)
		{
			vdata[col] += data[k + col] * pvdata[row];
		}
	}
	return Vector<T>(vdata);
}

template<typename T>
Array<T, 3> Matrix<T>::operator*(const Array<T, 3>& pV)
{
	T vdata[4], pvdata[4];

	memcpy(pvdata, pV.data, 3 * sizeof(T));
	pvdata[3] = 1.0f;

	for (col = 0; col < 4; col++)
	{
		k = 0;
		vdata[col] = 0;
		for (row = 0; row < 4; row++, k += 4)
		{
			vdata[col] += data[k + col] * pvdata[row];
		}
	}

	return Array<T, 3>(vdata);
}

template<typename T>
void Matrix<T>::ScalingMatrix(const Vector<T> &pvT)
{
	Identity();
	data[0] = pvT.x;
	data[5] = pvT.y;
	data[10] = pvT.z;
}

template<typename T>
void Matrix<T>::TranslationMatrix(const Array<T, 3> &pAT)
{
	Identity();
	data[12] = pAT[0];
	data[13] = pAT[1];
	data[14] = pAT[2];
}

template<typename T>
void Matrix<T>::QuaternionMatrix(T &x, T &y, T &z, T &w)
{
	T xx = x*x; T yy = y*y; T zz = z*z;
	T xy = x*y; T xz = x*z; T yz = y*z;
	T wx = w*x; T wy = w*y; T wz = w*z;

	data[0] = 1 - 2 * (yy + zz);
	data[1] = 2 * (xy - wz);
	data[2] = 2 * (xz + wy);

	data[4] = 2 * (xy + wz);
	data[5] = 1 - 2 * (xx + zz);
	data[6] = 2 * (yz - wx);

	data[8] = 2 * (xz - wy);
	data[9] = 2 * (yz + wx);
	data[10] = 1 - 2 * (xx + yy);

	data[3] = data[7] = data[11] = 0.0f;
	data[12] = data[13] = data[14] = 0.0f;
	data[15] = 1.0f;
}

/*************************************************
NEW- NEW- NEW- NEW- NEW- NEW- NEW- NEW- NEW- NEW*/

template<typename T>
float Quaternion<T>::qACos(float pValue)
{
	if (-1.0f < pValue)
	{
		if (pValue < 1.0f)
		{
			return (float)acos(pValue);
		}
		else
		{
			return 0.0f;
		}
	}
	else
	{
		return M_PI;
	}
}

template<typename T>
Quaternion<T> Quaternion<T>::operator+(Quaternion<T> pq)
{
	T rdata[4];
	rdata[0] = pq.data[0] + data[0];
	rdata[1] = pq.data[1] + data[1];
	rdata[2] = pq.data[2] + data[2];
	rdata[3] = pq.data[3] + data[3];
	return Quaternion<T>(rdata);
}

template<typename T>
Quaternion<T> Quaternion<T>::operator*(T pT)
{
	T rdata[4];
	rdata[0] = pT * data[0];
	rdata[1] = pT * data[1];
	rdata[2] = pT * data[2];
	rdata[3] = pT * data[3];
	return Quaternion<T>(rdata);
}

template<typename T>
T Quaternion<T>::Dot(Quaternion<T> &pq)
{
	return ((data[0] * pq.data[0]) + (data[1] * pq.data[1]) + (data[2] * pq.data[2]) + (data[3] * pq.data[3]));
}

template<typename T>
Quaternion<T> Quaternion<T>::Slerp(T pT, Quaternion<T> &pq)
{
	//We calculate the angle spread between both quaternions
	T AngleCos = pq.Dot(*this);
	T Angle = qACos(AngleCos); //see the function ACos above

	if (Angle < MINFLOAT)
	{
		return quaternion<T>(*this);
	}
	//We calculate the interpolated angle and deduce the resulting quaternion
	T InvAngleSin = (T)(1.0f / sin(Angle));

	T Coeff0 = sin((1 - pT) * Angle) * InvAngleSin;
	T Coeff1 = sin(pT * Angle) * InvAngleSin;
	return Quaternion<T>((*this * Coeff0) + (pq * Coeff1));
}

/*************************************************/

#endif
