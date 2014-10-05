#include "TrackBlock.h"


TrackBlock::TrackBlock(float width, float height)
{
	this->width = width;
	this->height = height;
}

TrackBlock::~TrackBlock()
{
}

void TrackBlock::Draw(pengine::Renderer* renderer)
{
	if (xModel != NULL)
	{
		renderer->SetActiveMatrix(myCachedMatrix->theMatrix); //should be called every frame

		pengine::MaterialWrapper* materialWrapper;
		int materialCount;
		xModel->GetMaterials(materialWrapper, materialCount);

		pengine::TextureWrapper* textureWrapper;
		int textureCount;
		xModel->GetTextures(textureWrapper, textureCount);

		renderer->SetMaterialWrapper(materialWrapper);
		renderer->SetTexture(textureWrapper);
		renderer->DrawSubset(xModel->GetMesh(), 0);
	}
}

void TrackBlock::SetXModel(pengine::XModel* p_xModel)
{
	xModel = p_xModel;
}