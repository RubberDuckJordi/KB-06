#pragma once

struct PEngineMatrix
{
	float	_11, _12, _13, _14,
	_21, _22, _23, _24,
	_31, _32, _33, _34,
	_41, _42, _43, _44;
};

class RenderMatrix
{
public:
	RenderMatrix();
	~RenderMatrix();
	void CreateMatrix(float x, float y, float z, float yaw, float pitch, float roll, float scaleX, float scaleY, float scaleZ, PEngineMatrix* matrix);
	PEngineMatrix* theMatrix;
};

