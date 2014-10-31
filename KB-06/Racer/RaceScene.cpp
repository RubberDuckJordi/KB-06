#include "RaceScene.h"

racer::RaceScene::RaceScene()
{
	elapsedTime = 0.0f;
	win = false;
	loss = false;
}

racer::RaceScene::~RaceScene()
{

}

void racer::RaceScene::Update(float deltaTime, std::map<pengine::Input, long>* actions)
{
	if (!win)
	{
		elapsedTime += deltaTime;
	}
	
	Scene::Update(deltaTime, actions);
	GetCurrentCamera()->SetThirdPersonEntity(raceCart, 75.0f, 30.0f);

	if (raceCart->GetCheckPoints()->size() == 0)
	{
		win = true;
	}
}

void racer::RaceScene::SetRaceCart(RaceCart* entity)
{
	raceCart = entity;
}

void racer::RaceScene::RenderToTexture(int texture, pengine::Renderer* renderer)
{
	//pengine::EntityCamera* aCamera = new pengine::EntityCamera();
	//aCamera->SetPosition(0.0f, 0.0f, 2.0f);
	//aCamera->SetLookAtPosition(0.0f, 0.0f, 0.0f, 0);

	//renderer->SetViewMatrix(aCamera->GetViewMatrix());
	//pengine::Matrix ortho;
	//pengine::Matrix::CreateOrthographicMatrix(50.0f, 50.0f, 1.0f, 10.0f, &ortho);
	//renderer->SetProjectionMatrix(&ortho);

	//pengine::Matrix aMatrix;
	//pengine::Matrix::CreateMatrix(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 10.0f, 10.0f, 1.0f, &aMatrix);
	//renderer->SetActiveMatrix(&aMatrix);
	//ColoredVertex vertices[] = {
	//	ColoredVertex(-0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, D3DCOLOR_ARGB(255, 255, 0, 0), 0.0f, 0.0f),
	//	ColoredVertex(0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, D3DCOLOR_ARGB(255, 0, 255, 0), 1.0f, 0.0f),
	//	ColoredVertex(0.0f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, D3DCOLOR_ARGB(255, 0, 0, 255), 0.5f, 1.0f)
	//};//holds a triangle that we will render to the texture
	//pengine::VertexBufferWrapper* wrapper = renderer->CreateColoredVertexBuffer(vertices, 3);
	//pengine::Material mat;
	//mat.texture = NULL;
	//mat.ambient = { 1.0f, 1.0f, 1.0f };
	//mat.diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
	//mat.emissive = { 1.0f, 1.0f, 1.0f };
	//mat.specular = { 1.0f, 1.0f, 1.0f };
	//mat.power = 10.0f;
	//renderer->SetMaterial(&mat);
	//renderer->DrawVertexBuffer(wrapper);//draw a triangle to the texture


	//pengine::Matrix::CreateMatrix(0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 3.0f, 3.0f, 1.0f, &aMatrix);
	//renderer->SetActiveMatrix(&aMatrix);
	//renderer->DrawString(std::to_string(elapsedTime), D3DCOLOR_ARGB(255, 255, 255, 0));

	//delete aCamera;
	//delete wrapper;

	/*int count = 0;
	auto i = collidables.begin();

	pengine::Collidable* c = *i;
	D3DCustomColoredVertex verts[] = {
	{ c->collisionBox.backBottomLeft.x, c->collisionBox.backBottomLeft.z, 1.0f, D3DCOLOR_ARGB(255, 255 * count, 0, 0), 0.0f, 1.0f },
	{ c->collisionBox.backBottomRight.x, c->collisionBox.backBottomRight.z, 1.0f, D3DCOLOR_ARGB(255, 255 * count, 0, 0), 1.0f, 0.0f },
	{ c->collisionBox.frontBottomRight.x, c->collisionBox.frontBottomRight.z, 1.0f, D3DCOLOR_ARGB(255, 255 * count, 0, 0), 0.0f, 0.0f },

	{ c->collisionBox.frontBottomRight.x, c->collisionBox.frontBottomRight.z, 1.0f, D3DCOLOR_ARGB(255, 255 * count, 0, 0), 0.0f, 1.0f },
	{ c->collisionBox.frontBottomLeft.x, c->collisionBox.frontBottomLeft.z, 1.0f, D3DCOLOR_ARGB(255, 255 * count, 0, 0), 1.0f, 1.0f },
	{ c->collisionBox.backBottomLeft.x, c->collisionBox.backBottomLeft.z, 1.0f, D3DCOLOR_ARGB(255, 255 * count, 0, 0), 1.0f, 0.0f },

	{ c->collisionBox2.backBottomLeft.x, c->collisionBox2.backBottomLeft.z, 1.0f, D3DCOLOR_ARGB(255, 255, 0, 0), 0.0f, 1.0f },
	{ c->collisionBox2.backBottomRight.x, c->collisionBox2.backBottomRight.z, 1.0f, D3DCOLOR_ARGB(255, 255, 0, 0), 1.0f, 0.0f },
	{ c->collisionBox2.frontBottomRight.x, c->collisionBox2.frontBottomRight.z, 1.0f, D3DCOLOR_ARGB(255, 255, 0, 0), 0.0f, 0.0f },

	{ c->collisionBox2.frontBottomRight.x, c->collisionBox2.frontBottomRight.z, 1.0f, D3DCOLOR_ARGB(255, 255, 0, 0), 0.0f, 1.0f },
	{ c->collisionBox2.frontBottomLeft.x, c->collisionBox2.frontBottomLeft.z, 1.0f, D3DCOLOR_ARGB(255, 255, 0, 0), 1.0f, 1.0f },
	{ c->collisionBox2.backBottomLeft.x, c->collisionBox2.backBottomLeft.z, 1.0f, D3DCOLOR_ARGB(255, 255, 0, 0), 1.0f, 0.0f }
	};

	pengine::VertexBufferWrapper* wrapper2 = renderer->CreateColoredVertexBuffer(verts, 12);
	pengine::Material mat2;
	mat.texture = NULL;
	mat.ambient = { 1.0f, 1.0f, 1.0f };
	mat.diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
	mat.emissive = { 1.0f, 1.0f, 1.0f };
	mat.specular = { 1.0f, 1.0f, 1.0f };
	mat.power = 10.0f;
	renderer->SetMaterial(&mat2);
	renderer->DrawVertexBuffer(wrapper2, 12);

	++count;*/
}

void racer::RaceScene::Render(pengine::Renderer* renderer)
{
	Scene::Render(renderer);

	pengine::Matrix aMatrix;

	pengine::Matrix::CreateMatrix(0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 3.0f, 3.0f, 1.0f, &aMatrix);
	renderer->SetActiveMatrix(&aMatrix);
	
	pengine::Matrix aMatrix2;
	pengine::Matrix aMatrix3;
	pengine::Matrix::CreateMatrix(0.0f, 15.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, &aMatrix2);
	pengine::Matrix::CreateMatrix(currentCamera->GetLookAtPosition()->x, currentCamera->GetLookAtPosition()->y, currentCamera->GetLookAtPosition()->z, 0.0f, 0.0f, 0.0f, 2.0f, 2.0f, 2.0f, &aMatrix3);
	pengine::Matrix::CreateObjectSpaceLookAtMatrix(currentCamera->GetPosition(), currentCamera->GetLookAtPosition(), &aMatrix);
	aMatrix = aMatrix2 * aMatrix * aMatrix3;
	renderer->SetActiveMatrix(&aMatrix);

	if (!win)
	{
		int r = int(1 * (elapsedTime / 30 * 255));
		if (r >= 255)
		{
			r = 255;
		}
		renderer->DrawString(std::to_string(elapsedTime), D3DCOLOR_ARGB(0, r, 100, 0));
	}
	else
	{
		renderer->DrawString("Victory!\n" +std::to_string(elapsedTime), D3DCOLOR_ARGB(0, 100, 255, 100));
	}

	renderer->Setshader(shader);
	pengine::Matrix mWorld;
	pengine::Matrix::CreateMatrix(-100, 140, 0, -90, 0, 0, 10, 10, 10, &mWorld);
	pengine::Matrix mProj = *GetCurrentCamera()->GetProjectionMatrix();
	pengine::Matrix mView = *GetCurrentCamera()->GetViewMatrix();
	pengine::Matrix mWorldViewProjection = mWorld * mView * mProj;
	
	renderer->SetshaderMatrix(renderer->GetshaderParameterHandle("g_mWorldViewProjection"), &mWorldViewProjection);
	renderer->SetshaderMatrix(renderer->GetshaderParameterHandle("g_mWorld"), &mWorld);

	D3DXCOLOR lowGrey = D3DXCOLOR(0.1f, 1.0f, 0.1f, 1.0f);
	renderer->SetshaderValue(renderer->GetshaderParameterHandle("g_MaterialAmbientColor"), &lowGrey, sizeof(D3DXCOLOR));

	D3DXCOLOR white = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
	renderer->SetshaderValue(renderer->GetshaderParameterHandle("g_LightDiffuse"), &white, sizeof(D3DXCOLOR));
	renderer->SetshaderValue(renderer->GetshaderParameterHandle("g_MaterialDiffuseColor"), &white, sizeof(D3DXCOLOR));

	D3DXVECTOR3 lightDir = D3DXVECTOR3(sinf(D3DX_PI * 2 * 1 / 1 - D3DX_PI / 6), 0, -cosf(D3DX_PI * 2 * 1 / 1 - D3DX_PI / 6));
	renderer->SetshaderValue(renderer->GetshaderParameterHandle("g_LightDir"), &lightDir, sizeof(D3DXVECTOR3));

	renderer->SetshaderTechnique(renderer->GetshaderTechniqueHandle("RenderScene"));

	UINT cPasses, iPass;
	renderer->BeginRenderingWithshader(&cPasses);

	for (iPass = 0; iPass < cPasses; iPass++)
	{
		renderer->BeginRenderingWithPass(iPass);
		//do all them renderings... tricky
		renderer->DrawString("Hello shaders!", D3DCOLOR_ARGB(0, 255, 0, 0));
		renderer->EndRenderingPass();
	}
	renderer->EndRenderingWithshader();
	//pengine::Material mat;
	//mat.texture = NULL;
	//mat.ambient = { 0.0f, 0.0f, 0.0f };
	//mat.diffuse = { 0.0f, 0.0f, 0.0f, 1.0f };
	//mat.emissive = { 0.0f, 0.0f, 0.0f };
	//mat.specular = { 0.0f, 0.0f, 0.0f };
	//mat.power = 10.0f;

	//renderer->SetMaterial(&mat);
	//renderer->SetTextureToRenderedTexture(0);

	//Vertex vertices[] = {
	//	Vertex(2.0f, -2.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f),//bl
	//	Vertex(-2.0f, 2.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f),//tr
	//	Vertex(2.0f, 2.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f),//tl

	//	Vertex(2.0f, -2.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f),//bl
	//	Vertex(-2.0f, -2.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f),//br
	//	Vertex(-2.0f, 2.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f)//tr
	//};//holds a square that we will render with the texture, so we can see the contents of the texture
	//pengine::VertexBufferWrapper* wrapper = renderer->CreateVertexBuffer(vertices, 6);
	//renderer->DrawVertexBuffer(wrapper);//draw the square

	//delete wrapper;
}