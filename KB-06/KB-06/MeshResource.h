#ifndef _RESOURCE_MESHRESOURCE_H_
#define _RESOURCE_MESHRESOURCE_H_
#include "Resource.h"
namespace Resource {
	class MeshResource : public Resource
	{
	public:
		MeshResource();
		~MeshResource();
		std::vector<Vertex>* GetVertices();
		std::vector<TextureCoordinate>* GetTextureCoordinates();
		std::vector<Normal>* GetNormals();
		std::vector<ParameterSpaceVertex>* GetParameterSpaceVertices();
		std::vector<FaceDefinition>* GetFaceDefinitions();
		void AddVertex(Vertex v);
		void AddTextureCoordinate(TextureCoordinate t);
		void AddNormal(Normal n);
		void AddParameterSpaceVertex(ParameterSpaceVertex p);
		void AddFaceDefinition(FaceDefinition f);
		//Mesh* GetMesh();
		void SetLoaded(bool state);
	protected:
		Mesh theMesh;
	};
}
#endif