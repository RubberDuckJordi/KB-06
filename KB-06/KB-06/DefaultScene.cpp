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

	void DefaultScene::Render(Renderer* renderer)
	{
		Scene::Render(renderer);
		renderer->ActivateRenderingToTexture(500, 500);
		D3DCustomVertex vertices[] = {
			{ -1.0f, -1.0f, 1.5f, 0.0f, 0.0f },
			{ 1.0f, -1.0f, 1.5f, 0.5f, 1.0f },
			{ 0.0f, 1.0f, 1.5f, 1.0f, 0.0f }
		};//holds a triangle that we will render to the texture
		EntityCamera* cam = new EntityCamera();
		renderer->SetActiveCamera(cam->GetCameraData(), true);//set the camera to a position so the stuff rendered on the texture isn't translated
		VertexBufferWrapper* wrapper = renderer->CreateVertexBuffer(vertices, 3, D3DCustomVertexFVF);
		Material mat;
		mat.texture = NULL;
		renderer->SetMaterial(&mat);
		renderer->DrawVertexBuffer(wrapper, 3);//draw a triangle to the texture

		renderer->DeactivateRenderingToTexture();
		renderer->SetTextureToRenderedTexture();
		renderer->SetActiveCamera(currentCamera->GetCameraData(), false);//set the camera back to what it was

		D3DCustomVertex vertices2[] = {
			{ 10.0f, -10.0f, 0.0f, 0.0f, 1.0f },//bl
			{ -10.0f, 10.0f, 0.0f, 1.0f, 0.0f },//tr
			{ 10.0f, 10.0f, 0.0f, 0.0f, 0.0f },//tl

			{ 10.0f, -10.0f, 0.0f, 0.0f, 1.0f },//bl
			{ -10.0f, -10.0f, 0.0f, 1.0f, 1.0f },//br
			{ -10.0f, 10.0f, 0.0f, 1.0f, 0.0f }//tr
		};//holds a square that we will render with the texture, so we can see the contents of the texture
		VertexBufferWrapper* wrapper2 = renderer->CreateVertexBuffer(vertices2, 6, D3DCustomVertexFVF);
		renderer->DrawVertexBuffer(wrapper2, 6);//draw the square
	}
}