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
		aCamera->SetPosition(0.0f, 0.0f, -100.0f);
		aCamera->SetLookAtPosition(0.0f, 0.0f, 0.0f, 0);
		logger->Log(Logger::DEBUG, "CurrentCamera x: " + std::to_string(currentCamera->GetPosition()->x) + ", y: " + std::to_string(currentCamera->GetPosition()->y) + ", z: " + std::to_string(currentCamera->GetPosition()->z));
		logger->Log(Logger::DEBUG, "CurrentCamera lookat x: " + std::to_string(currentCamera->GetLookAtPosition()->x) + ", y: " + std::to_string(currentCamera->GetLookAtPosition()->y) + ", z: " + std::to_string(currentCamera->GetLookAtPosition()->z));

		renderer->SetViewMatrix(aCamera->GetViewMatrix());
		renderer->SetProjectionMatrix(currentCamera->GetProjectionMatrix());

		/*EntityCamera* cam = new EntityCamera();
		cam->SetPosition(0.0f, 0.0f, 1.0f);
		cam->SetLookAtPosition(0.0f, 0.0f, -1.0f, 0.0f);
		renderer->SetViewMatrix(cam->GetViewMatrix(), true);*/
		//renderer->SetProjectionMatrix(currentCamera->GetProjectionMatrix());

		Matrix* aMatrix = new pengine::Matrix();
		aMatrix->CreateMatrix(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, aMatrix);
		renderer->SetActiveMatrix(aMatrix);
		D3DCustomVertex vertices[] = {
		{ -10.0f, -10.0f, 1.5f, 0.0f, 0.0f },
		{ 10.0f, -10.0f, 1.5f, 0.5f, 1.0f },
		{ 0.0f, 10.0f, 1.5f, 1.0f, 0.0f }
		};//holds a triangle that we will render to the texture
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
	}

	void DefaultScene::Render(Renderer* renderer)
	{
		Scene::Render(renderer);
		Matrix* aMatrix = new pengine::Matrix();
		aMatrix->CreateMatrix(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, aMatrix);
		renderer->SetActiveMatrix(aMatrix);
		/*D3DCustomVertex vertices[] = {
			{ -1.0f, -1.0f, 6.0f, 0.0f, 0.0f },
			{1.0f, -1.0f, 6.0f, 0.5f, 1.0f },
			{ 0.0f, 1.0f, 6.0f, 1.0f, 0.0f }
		};//holds a triangle that we will render to the texture
		VertexBufferWrapper* wrapper = renderer->CreateVertexBuffer(vertices, 3, D3DCustomVertexFVF);*/
		Material mat;
		mat.texture = NULL;
		mat.ambient = { 0.0f, 0.0f, 0.0f };
		mat.diffuse = { 0.0f, 0.0f, 0.0f, 1.0f };
		mat.emissive = { 0.0f, 0.0f, 0.0f };
		mat.specular = { 0.0f, 0.0f, 0.0f };
		mat.power = 10.0f;
		//renderer->SetMaterial(&mat);
		//renderer->DrawVertexBuffer(wrapper, 3);//draw a triangle to the texture

		renderer->SetMaterial(&mat);
		renderer->SetTextureToRenderedTexture(0);

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