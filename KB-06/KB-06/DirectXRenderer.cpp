#include "DirectXRenderer.h"
#include "CustomD3DVertex.h"
//#include <sstream>

Renderer::DirectXRenderer::DirectXRenderer()
{
	logger = Logger::LoggerPool::GetInstance().GetLogger();
	g_pD3D = NULL;
	g_pd3dDevice = NULL;
	matrixCache = new D3DXMATRIX();
};

Renderer::DirectXRenderer::~DirectXRenderer()
{
	if (g_pd3dDevice != NULL)
	{
		g_pd3dDevice->Release();
	}

	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
	}
	Logger::LoggerPool::GetInstance().ReturnLogger(logger);
};

void Renderer::DirectXRenderer::InitD3D(HWND hWnd)
{
	if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		logger->Log(Logger::Logger::ERR, "Failed to instantiate Direct3DCreate9");
		return;
		//return E_FAIL; -> when switching from void to H_RESULT return type
	}

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = true;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &g_pd3dDevice)))
	{
		logger->Log(Logger::Logger::ERR, "Failed to instantiate Direct3D9 CreateDevice");
		return;
		//return E_FAIL; -> when switching from void to H_RESULT return type
	}

	logger->Log(Logger::Logger::WARNING, "Culling turned off");
	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);    // turn off culling

	//return S_OK; -> when switching from void to H_RESULT return type
};

void Renderer::DirectXRenderer::SetRenderState()
{
	this->g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);	//Counter Clockwise Cullmode
	this->g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE); //No lightning
	this->g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE); //Z buffer on
	this->g_pd3dDevice->SetRenderState(D3DRS_AMBIENT, 0xffffffff); //Ambient is white
	this->g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true); //Turn Alphablending on
	this->g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA); //Type alphablending
	this->g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA); //Type alphablending
	g_pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
};

void Renderer::DirectXRenderer::SetActiveCamera(CameraData camera)
{
	// Set up our view matrix. A view matrix can be defined given an eye point,
	// a point to lookat, and a direction for which way is up. Here, we set the
	// eye 0.5 units back along the z-axis and up 0 units, look at the 
	// origin + 0.5 on the z-axis, and define "up" to be in the y-direction.
	/*std::ostringstream oss;

	oss << "Camera x: " << camera.x << ", y: " << camera.y << ", z: " << camera.z 
		<< ", lookAtX: " << camera.lookAtX << ", lookAtY: " << camera.lookAtY << ", lookAtZ: " << camera.lookAtZ
		<< ", upVecX: " << camera.upVecX << ", upVecY: " << camera.upVecY << ", upVecZ: " << camera.upVecZ;
	logger->Log(Logger::Logger::LogLevel::DEBUG, oss.str().c_str());*/

	D3DXVECTOR3 vEyePt(camera.x, camera.y, camera.z);
	D3DXVECTOR3 vLookatPt(camera.lookAtX, camera.lookAtY, camera.lookAtZ);
	D3DXVECTOR3 vUpVec(camera.upVecX, camera.upVecY, camera.upVecZ);
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
	g_pd3dDevice->SetTransform(D3DTS_VIEW, &matView);

	// Set up our view matrix. A view matrix can be defined given an eye point,
	// a point to lookat, and a direction for which way is up. Here, we set the
	// eye 0.5 units back along the z-axis and up 0 units, look at the 
	// origin + 0.5 on the z-axis, and define "up" to be in the y-direction.
	/*D3DXVECTOR3 vEyePt(0, 0, -0.5f);
	D3DXVECTOR3 vLookatPt(0, 0, 0.5f);
	D3DXVECTOR3 vUpVec(0.0f, 0.5f, 0.0f);
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
	g_pd3dDevice->SetTransform(D3DTS_VIEW, &matView);*/
}

//Matrixen
void Renderer::DirectXRenderer::SetWorldMatrix(MatrixWrapper* WorldMatrix)
{
	this->g_pd3dDevice->SetTransform(D3DTS_WORLD, &(WorldMatrix->GetMatrix()));
};

void Renderer::DirectXRenderer::SetViewMatrix(MatrixWrapper* ViewMatrix)
{
	this->g_pd3dDevice->SetTransform(D3DTS_VIEW, &(ViewMatrix->GetMatrix()));
};

void Renderer::DirectXRenderer::SetViewMatrix(float posX, float posY, float posZ, float roatationX, float roatationY, float roatationZ)
{
	// Set up our view matrix. A view matrix can be defined given an eye point,
	// a point to lookat, and a direction for which way is up. Here, we set the
	// eye five units back along the z-axis and up three units, look at the 
	// origin, and define "up" to be in the y-direction.
	/*D3DXVECTOR3 vEyePt(posX, posY, posZ);
	D3DXVECTOR3 vLookatPt(roatationX, roatationY, roatationZ);
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);

	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);*/

	D3DXVECTOR3 vEyePt(posX, posY, posZ);
	D3DXVECTOR3 vLookatPt(roatationX, roatationY, roatationZ);
	D3DXVECTOR3 vUpVec(0.0f, 0.5f, 0.0f);
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);

	g_pd3dDevice->SetTransform(D3DTS_VIEW, &matView);
}

void Renderer::DirectXRenderer::SetProjectionMatrix(MatrixWrapper* ProjectionMatrix)
{
	this->g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &(ProjectionMatrix->GetMatrix()));
};

void Renderer::DirectXRenderer::SetProjectionMatrix(float FOV, float farClippingPlane)
{
	// For the projection matrix, we set up a perspective transform (which
	// transforms geometry from 3D view space to 2D viewport space, with
	// a perspective divide making objects smaller in the distance). To build
	// a perpsective transform, we need the field of view (1/4 pi is common),
	// the aspect ratio, and the near and far clipping planes (which define at
	// what distances geometry should be no longer be rendered).
	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, FOV, 1.0f, 1.0f, 1000.0f);
	g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}

//Scene
void Renderer::DirectXRenderer::BeginScene()
{
	this->g_pd3dDevice->BeginScene();
};

void Renderer::DirectXRenderer::ClearScene(PENGINEDWORD* count, PENGINEDWORD* flags, PENGINECOLOR* color, float z, PENGINEDWORD* stencil)
{
	this->g_pd3dDevice->Clear(*count, NULL, *flags, *color, z, *stencil);
};
void Renderer::DirectXRenderer::ClearScene(unsigned long count, unsigned long flags, Resource::RGBAColor color, float z, unsigned long stencil){
	flags = D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER;
	g_pd3dDevice->Clear(PENGINEDWORD(count), NULL, PENGINEDWORD(flags),
		D3DCOLOR_COLORVALUE(color.r, color.g, color.b, color.a), z, PENGINEDWORD(stencil));
};

void Renderer::DirectXRenderer::PresentScene(HWND hWnd)
{
	this->g_pd3dDevice->Present(NULL, NULL, hWnd, NULL);
};

void Renderer::DirectXRenderer::EndScene()
{
	this->g_pd3dDevice->EndScene();
};

//Buffers
void Renderer::DirectXRenderer::CreateVertexBuffer(int heightmapvertex, PENGINEDWORD* usage, PENGINEDWORD* fvf, PENGINEPOOL* pool, VertexBufferWrapper* vertexbuffer, HANDLE handle)
{
	this->g_pd3dDevice->CreateVertexBuffer(heightmapvertex, *usage, *fvf, static_cast<D3DPOOL>(*pool), vertexbuffer->GetVertexBuffer(), &handle);
};

void Renderer::DirectXRenderer::CreateIndexBuffer(int length, PENGINEDWORD* usage, PENGINEFORMAT* format, PENGINEPOOL* pool, IndexBufferWrapper* Indexbuffer, HANDLE* handle)
{
	this->g_pd3dDevice->CreateIndexBuffer(length, *usage, static_cast<D3DFORMAT>(*format), static_cast<D3DPOOL>(*pool), Indexbuffer->GetIndexBuffer(), NULL);
};

//Set stuff
void Renderer::DirectXRenderer::SetMaterial(MaterialWrapper* wrapper)
{
	g_pd3dDevice->SetMaterial(&wrapper->GetMaterial());
	//return g_pd3dDevice->SetMaterial(&wrapper->GetMaterial()); when H_RESULT as return type
};

void Renderer::DirectXRenderer::SetTexture(TextureWrapper* wrapper)
{
	g_pd3dDevice->SetTexture(0, wrapper->GetTexture());
	// return g_pd3dDevice->SetTexture(0, wrapper->GetTexture()); when H_RESULT as return type
};

void Renderer::DirectXRenderer::SetFvF(PENGINEDWORD* fvf)
{
	g_pd3dDevice->SetFVF(*fvf);
};


//Draw functions
void Renderer::DirectXRenderer::DrawPrimitive(Resource::Mesh mesh)
{
	//g_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, mesh.vertices.size, 0, mesh.faceDefinitions.size * 3);
};

void Renderer::DirectXRenderer::DrawSubset(MeshWrapper* wrapper, int subset)
{
	(wrapper->GetMesh())->DrawSubset(subset);
};

//??
void Renderer::DirectXRenderer::SetStreamSource() //??
{

};

void Renderer::DirectXRenderer::SetIndices() //??
{

};

//GetDevice
LPDIRECT3DDEVICE9* Renderer::DirectXRenderer::GetDevice()
{
	return &g_pd3dDevice;
};

void Renderer::DirectXRenderer::Draw(Resource::Mesh* mesh){
	if (meshCache.find(mesh) == meshCache.end()){
		logger->Log(Logger::Logger::DEBUG, "Mesh not converted to LPD3DXMESH yet.");

		LPD3DXMESH d3dMesh;
		int	amountOfVertices = 0;
		int amountOfIndices = 0;
		for (unsigned int i = 0; i < mesh->subsets.size(); ++i){
			amountOfVertices += mesh->subsets.at(i).vertices.size();
			amountOfIndices += mesh->subsets.at(i).faceDefinitions.size();
		}
		if (FAILED(D3DXCreateMeshFVF(amountOfIndices, amountOfVertices, 0, D3DCustomVertexFVF, g_pd3dDevice, &d3dMesh))){
			logger->Log(Logger::Logger::ERR, "Failed to create a D3DXCreateMeshFVF. Generating a cube");
			D3DXCreateBox(g_pd3dDevice, 1.0f, 1.0f, 1.0f, &d3dMesh, NULL); 
		}
		else {
			D3DCustomVertex* d3dVertices = new D3DCustomVertex[amountOfVertices];
			unsigned short* indices = new unsigned short[amountOfIndices * 3];

			for (unsigned int i = 0; i < mesh->subsets.size(); ++i){
				for (unsigned int j = 0; j < mesh->subsets.at(i).vertices.size(); ++j){
					D3DCustomVertex newVertex;
					newVertex.x = mesh->subsets.at(i).vertices.at(j).x;
					newVertex.y = mesh->subsets.at(i).vertices.at(j).y;
					newVertex.z = mesh->subsets.at(i).vertices.at(j).z;
					d3dVertices[j] = newVertex;
				}
				int index = -1;
				for (unsigned int j = 0; j < mesh->subsets.at(i).faceDefinitions.size(); ++j){
					indices[++index] = mesh->subsets.at(i).faceDefinitions.at(j).v1;
					indices[++index] = mesh->subsets.at(i).faceDefinitions.at(j).v2;
					indices[++index] = mesh->subsets.at(i).faceDefinitions.at(j).v3;
					int test = 10;
				}
			}
			VOID* pVoid;

			LPDIRECT3DVERTEXBUFFER9 v_buffer;
			d3dMesh->GetVertexBuffer(&v_buffer);
			// lock v_buffer and load the vertices into it
			v_buffer->Lock(0, 0, (void**)&pVoid, 0);
			memcpy(pVoid, d3dVertices, amountOfVertices*sizeof(D3DCustomVertex));
			v_buffer->Unlock();
	
			LPDIRECT3DINDEXBUFFER9 i_buffer;
			d3dMesh->GetIndexBuffer(&i_buffer);
			// lock i_buffer and load the indices into it
			i_buffer->Lock(0, 0, (void**)&pVoid, 0);
			memcpy(pVoid, indices, amountOfIndices * 3 * sizeof(unsigned short));
			i_buffer->Unlock();

			logger->Log(Logger::Logger::DEBUG, "Mesh converted to LPD3DXMESH.");
		}
		meshCache[mesh] = d3dMesh;
		//D3DXSaveMeshToX(L"test.x", d3dMesh, NULL, NULL, NULL, 0, 1); //save mesh to file to debug
	}

	meshCache[mesh]->DrawSubset(0); // always draw the first subset incase it's a d3dx9 generated cube
	for (int i = 1; i < mesh->subsets.size(); ++i){ // So we start at 1 instead of 0
		meshCache[mesh]->DrawSubset(1 + i);
	}
}

void Renderer::DirectXRenderer::SetActiveMatrix(PEngineMatrix* matrix)
{
	matrixCache->_11 = matrix->_11;
	matrixCache->_12 = matrix->_12;
	matrixCache->_13 = matrix->_13;
	matrixCache->_14 = matrix->_14;

	matrixCache->_21 = matrix->_21;
	matrixCache->_22 = matrix->_22;
	matrixCache->_23 = matrix->_23;
	matrixCache->_24 = matrix->_24;

	matrixCache->_31 = matrix->_31;
	matrixCache->_32 = matrix->_32;
	matrixCache->_33 = matrix->_33;
	matrixCache->_34 = matrix->_34;

	matrixCache->_41 = matrix->_41;
	matrixCache->_42 = matrix->_42;
	matrixCache->_43 = matrix->_43;
	matrixCache->_44 = matrix->_44;

	g_pd3dDevice->SetTransform(D3DTS_WORLD, matrixCache);
}


/**
* set the world matrix
* @param matrix
* @param offset
* @param staticEntity
*/
void Renderer::DirectXRenderer::SetWorldMatrix(D3DXMATRIX* matrix, D3DXMATRIX* offset, bool staticEntity)
{
	D3DXMATRIX worldMatrix;
	if (staticEntity)
	{
		worldMatrix = *matrix;
	}
	else
	{
		worldMatrix = *matrix * *offset;
	}
	g_pd3dDevice->SetTransform(D3DTS_WORLD, &worldMatrix);
}

void Renderer::DirectXRenderer::SetWorldMatrixForStaticEntity(Resource::Vertex* p_translation, Resource::Vertex* p_rotation, Resource::Vertex* p_scaling)
{
	D3DXMATRIX* transformation = CreateD3DMATRIX(p_translation, p_rotation, p_scaling);
	SetWorldMatrix(transformation, NULL, true);
}

void Renderer::DirectXRenderer::SetWorldMatrix(Resource::Vertex* p_translation, Resource::Vertex* p_rotation, Resource::Vertex* p_scaling, Resource::Vertex* p_cameraPosition, Resource::Vertex* p_cameraRotation)
{
	D3DXMATRIX* transformation = CreateD3DMATRIX(p_translation, p_rotation, p_scaling);
	D3DXMATRIX* offset = CreateD3DMATRIX(p_cameraPosition, p_cameraRotation, NULL);

	SetWorldMatrix(transformation, offset, false);
}


D3DXMATRIX* Renderer::DirectXRenderer::CreateD3DMATRIX(Resource::Vertex* p_translation, Resource::Vertex* p_rotation, Resource::Vertex* p_scaling)
{
	D3DXMATRIX translation;

	D3DXMATRIX rotationX;
	D3DXMATRIX rotationY;
	D3DXMATRIX rotationZ;
	D3DXMATRIX* transformation = new D3DXMATRIX();

	D3DXMatrixTranslation(&translation, (*p_translation).x, (*p_translation).y, (*p_translation).z);

	//(PI/180)*angle = Degree to Radian
	D3DXMatrixRotationX(&rotationX, DEGREES(p_rotation->x));
	D3DXMatrixRotationY(&rotationY, (D3DX_PI / 180) * (*p_rotation).y);
	D3DXMatrixRotationZ(&rotationZ, (D3DX_PI / 180) * (*p_rotation).z);
	//D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, roll);

	//First rotate, scale, then translate the entity
	//Otherwise the translation will be rotated
	(*transformation) = rotationX * rotationY * rotationZ;

	(*transformation) *= translation;
	if (p_scaling != NULL)
	{
		D3DXMATRIX* scaling = new D3DXMATRIX();
		D3DXMatrixScaling(scaling, (*p_scaling).x, (*p_scaling).y, (*p_scaling).z);
		(*transformation) *= (*scaling);
	}

	return transformation;
}
