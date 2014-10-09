#include "TrackBlock.h"


TrackBlock::TrackBlock(float width, float lenght)
{
	this->width = width;
	this->lenght = lenght;
}

TrackBlock::~TrackBlock()
{
}

void TrackBlock::Draw(pengine::Renderer* renderer)
{
	if (xModel != NULL)
	{
		renderer->SetActiveMatrix(myCachedMatrix->theMatrix); //should be called every frame

		xModel->ClearSkinnedVertices();
		//xModel->UpdateAnimation();
		xModel->Draw(renderer);
	}
}

void TrackBlock::SetXModel(pengine::Object3D* p_xModel)
{
	xModel = p_xModel;
}