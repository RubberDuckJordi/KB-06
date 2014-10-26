#include "DefaultScene.h"
#include "Logger.h"
#include "LoggerPool.h"

namespace pengine
{
	DefaultScene::DefaultScene()
	{

	}

	DefaultScene::~DefaultScene()
	{

	}

	void DefaultScene::Update(float deltaTime, std::map<Input, long>* actions)
	{
		Scene::Update(deltaTime, actions);
	}

	void DefaultScene::RenderToTexture(int textureIndex, Renderer* renderer)
	{
		EntityCamera* aCamera = new EntityCamera();
		aCamera->SetPosition(0.0f, 0.0f, 2.0f);
		aCamera->SetLookAtPosition(0.0f, 0.0f, 0.0f, 0);

		renderer->SetViewMatrix(aCamera->GetViewMatrix());
		Matrix* ortho = new Matrix();
		Matrix::CreateOrthographicMatrix(1.0f, 1.0f, 1.0f, 10.0f, ortho);
		renderer->SetProjectionMatrix(ortho);

		Matrix* aMatrix = new pengine::Matrix();
		aMatrix->CreateMatrix(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, aMatrix);
		renderer->SetActiveMatrix(aMatrix);
		ColoredVertex vertices[] = {
			ColoredVertex(-0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, D3DCOLOR_ARGB(255, 255, 0, 0), 0.0f, 0.0f),
			ColoredVertex(0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, D3DCOLOR_ARGB(255, 0, 255, 0), 1.0f, 0.0f),
			ColoredVertex(0.0f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, D3DCOLOR_ARGB(255, 0, 0, 255), 0.5f, 1.0f)
		};//holds a triangle that we will render to the texture
		VertexBufferWrapper* wrapper = renderer->CreateColoredVertexBuffer(vertices, 3);
		Material mat;
		mat.texture = NULL;
		mat.ambient = { 1.0f, 1.0f, 1.0f };
		mat.diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
		mat.emissive = { 1.0f, 1.0f, 1.0f };
		mat.specular = { 1.0f, 1.0f, 1.0f };
		mat.power = 10.0f;
		renderer->SetMaterial(&mat);
		renderer->DrawVertexBuffer(wrapper);//draw a triangle to the texture


		Matrix::CreateMatrix(0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.06f, 0.06f, 1.0f, aMatrix);
		renderer->SetActiveMatrix(aMatrix);
		renderer->DrawString("abcdefghi\njklmnopqr\nstuvwxyz0\n123456789\n!?#+-$ ()\n.'/\\<>[]{\n},*:", D3DCOLOR_ARGB(255, 255, 255, 255));
		delete wrapper;
	}

	void DefaultScene::Render(Renderer* renderer)
	{
		Scene::Render(renderer);
		Matrix* aMatrix = new pengine::Matrix();
		aMatrix->CreateMatrix(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, aMatrix);
		renderer->SetActiveMatrix(aMatrix);
		Material mat;
		mat.texture = NULL;
		mat.ambient = { 0.0f, 0.0f, 0.0f };
		mat.diffuse = { 0.0f, 0.0f, 0.0f, 1.0f };
		mat.emissive = { 0.0f, 0.0f, 0.0f };
		mat.specular = { 0.0f, 0.0f, 0.0f };
		mat.power = 10.0f;

		renderer->SetMaterial(&mat);
		renderer->SetTextureToRenderedTexture(0);

		ColoredVertex vertices[] = {
			ColoredVertex(10.0f, -10.0f, 0.0f, 0.0f, 0.0f, 0.0f, D3DCOLOR_ARGB(255, 255, 0, 0), 0.0f, 1.0f),//bl
			ColoredVertex(-10.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, D3DCOLOR_ARGB(255, 0, 255, 0), 1.0f, 0.0f),//tr
			ColoredVertex(10.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, D3DCOLOR_ARGB(255, 0, 0, 255), 0.0f, 0.0f),//tl

			ColoredVertex(10.0f, -10.0f, 0.0f, 0.0f, 0.0f, 0.0f, D3DCOLOR_ARGB(255, 255, 0, 0), 0.0f, 1.0f),//bl
			ColoredVertex(-10.0f, -10.0f, 0.0f, 0.0f, 0.0f, 0.0f, D3DCOLOR_ARGB(255, 0, 0, 0), 1.0f, 1.0f),//br
			ColoredVertex(-10.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, D3DCOLOR_ARGB(255, 0, 255, 0), 1.0f, 0.0f)//tr
		};//holds a square that we will render with the texture, so we can see the contents of the texture
		VertexBufferWrapper* wrapper = renderer->CreateColoredVertexBuffer(vertices, 6);
		renderer->DrawVertexBuffer(wrapper);//draw the square

		Matrix::CreateMatrix(0.0f, 15.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, aMatrix);
		renderer->SetActiveMatrix(aMatrix);
		renderer->DrawString("Hello world!\nLife is great!\nOr is it?\nWell I'm pretty\nsure it is...\nActually I'm\nnot so sure\nanymore...", D3DCOLOR_ARGB(127, 0, 127, 0));
		delete wrapper;
	}
}