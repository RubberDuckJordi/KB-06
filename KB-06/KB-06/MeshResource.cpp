#include "stdafx.h"
#include "MeshResource.h"


Resource::MeshResource::MeshResource()
{
}


Resource::MeshResource::~MeshResource()
{
}

std::vector<Resource::Vertex>* Resource::MeshResource::GetVertices()
{
	return &theMesh.vertices;
}

std::vector<Resource::TextureCoordinate>* Resource::MeshResource::GetTextureCoordinates()
{
	return &theMesh.textureCoordinates;
}

std::vector<Resource::Normal>* Resource::MeshResource::GetNormals()
{
	return &theMesh.normals;
}

std::vector<Resource::ParameterSpaceVertex>* Resource::MeshResource::GetParameterSpaceVertices()
{
	return &theMesh.parameterSpaceVertices;
}

std::vector<Resource::FaceDefinition>* Resource::MeshResource::GetFaceDefinitions()
{
	return &theMesh.faceDefinitions;
}

void Resource::MeshResource::AddVertex(Vertex v)
{
	theMesh.vertices.push_back(v);
}

void Resource::MeshResource::AddTextureCoordinate(TextureCoordinate t)
{
	theMesh.textureCoordinates.push_back(t);
}

void Resource::MeshResource::AddNormal(Normal n)
{
	theMesh.normals.push_back(n);
}

void Resource::MeshResource::AddParameterSpaceVertex(ParameterSpaceVertex p)
{
	theMesh.parameterSpaceVertices.push_back(p);
}

void Resource::MeshResource::AddFaceDefinition(FaceDefinition f)
{
	theMesh.faceDefinitions.push_back(f);
}

/*Resource::Mesh* Resource::MeshResource::GetMesh()
{
	return &theMesh;
}*/

void Resource::MeshResource::SetLoaded(bool state)
{
	isLoaded = state;
}