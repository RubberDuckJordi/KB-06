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
		Matrix* aMatrix = new pengine::Matrix();
		aMatrix->CreateMatrix(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, aMatrix);
		renderer->SetActiveMatrix(aMatrix);
		renderer->ActivateRenderingToTexture(500, 500, 0xFF0000FF);
		D3DCustomVertex vertices[] = {
			{ -1.0f, -1.0f, 1.5f, 0.0f, 0.0f },
			{ 1.0f, -1.0f, 1.5f, 0.5f, 1.0f },
			{ 0.0f, 1.0f, 2.0f, 1.0f, 0.0f }
		};//holds a triangle that we will render to the texture
		EntityCamera* cam = new EntityCamera();
		cam->SetPosition(0, 0, 0);
		cam->SetLookAtPosition(0, 0, -1, 0);
		renderer->SetActiveCamera(cam->GetCameraData(), true);//set the camera to a position so the stuff rendered on the texture isn't translated
		VertexBufferWrapper* wrapper = renderer->CreateVertexBuffer(vertices, 3, D3DCustomVertexFVF);
		Material mat;
		mat.texture = NULL;
		mat.ambient = { 0.0f, 0.0f, 0.0f };
		mat.diffuse = { 0.0f, 0.0f, 0.0f, 1.0f };
		mat.emissive = { 0.0f, 0.0f, 0.0f };
		mat.specular = { 0.0f, 0.0f, 0.0f };
		mat.power = 10.0f;
		renderer->SetMaterial(&mat);
		renderer->DrawVertexBuffer(wrapper, 3);//draw a triangle to the texture

		renderer->DeactivateRenderingToTexture();
		renderer->SetMaterial(&mat);
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