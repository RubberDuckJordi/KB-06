#ifndef _ARRAY_H_
#define _ARRAY_H_

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
#endif