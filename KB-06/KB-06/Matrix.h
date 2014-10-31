#ifndef _PENGINE_MATRIX_H_
#define _PENGINE_MATRIX_H_

#include "Vector.h"
#include "Types.h"
#include "Vector3.h"//same functionality as Vector.h, different implementation
#include <d3dx9.h>//ugly, might as well go fix this...
#include "PengineDefinitions.h"
#include "LoggerPool.h"
#include "Vertex.h"
#include <sstream>

namespace pengine
{
	class Matrix
	{
	public:
		float data[16];
		Matrix();
		Matrix(const Matrix &pm);
		Matrix(const float* pT);
		void Zero();
		// Creates an empty Matrix
		/*
		1 0 0 0
		0 1 0 0 
		0 0 1 0
		0 0 0 1
		*/
		void Identity();

		// operator overloading
		Matrix& operator=(const Matrix &pm);
		Matrix operator+(Matrix pm);
		Matrix operator-(Matrix pm);
		Matrix operator*(Matrix pm);
		Matrix& operator*=(Matrix &pm);
		Matrix operator*(float pT);
		Vector operator*(const Vector& pV);

		Vertex operator*(const Vertex& pV);

		float operator[](int index)const;
		float& operator[](int index);

		float _fastcall Index(int pRow, int pCol)const;
		float operator()(int pRow, int pCol)const;
		float& operator()(int pRow, int pCol);
		Vector GetRow(int index);
		Vector GetColumn(int index);
		void ScalingMatrix(const Vector &pvT);

		void TranslationMatrix(const std::array<float, 3> &pAT);

		void TranslationMatrix(Vertex &pAT);
		void QuaternionMatrix(float &x, float &y, float &z, float &w);

		static void CreateMatrix(float x, float y, float z, float yaw, float pitch, float roll, float scaleX, float scaleY, float scaleZ, Matrix* receiver);

		static void CreateLookAtMatrix(Vector3 pos, Vector3 lookAtPos, Vector3 upVector, Matrix* receiver);

		static void CreateOrthographicMatrix(float width, float height, float nearPlane, float farPlane, Matrix* receiver);

		/*!
		Makes a matrix with just the rotation, not the translation.
		This matrix can probably not be used as a view matrix.
		*/
		static void CreateObjectSpaceLookAtMatrix(Vector3* position, Vector3* lookAt, Matrix* receiver);

		static void PrintMatrix(Matrix* matrix);

	private:
		int k, l, row, col;
	};
}
#endif