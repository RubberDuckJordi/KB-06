#include "stdafx.h"
#include "ObjLoader.h"
#include "Mesh.h"
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include "StringHelper.h"
#include "LoggerPool.h"
#include "MeshResource.h"


Resource::ObjLoader::ObjLoader(){};

/*Resource::Mesh Resource::ObjLoader::Load(const std::string file, const ResourceManager* resourceManager){

}*/

/*std::string Resource::ObjLoader::GetExtension(){
	return "obj.mesh";
}*/

Resource::Resource* Resource::ObjLoader::LoadResource(char* path, ResourceManager* rsmgr)
{
	Logger::Logger* logger = Logger::LoggerPool::GetInstance().GetLogger();
	std::ifstream ifs(path, std::ifstream::in);
	std::string line;
	std::vector<std::string> elements;
	std::vector<std::string> faces;

	MeshResource* mesh = new MeshResource();
	while (ifs.good()) {
		getline(ifs, line);
		elements = Logger::StringHelper::split(line, ' ');
		if (elements.size() > 0){
			if (elements[0] == "mtllib"){
				//resourceManager->loadMaterials(elements[1]);
				char* mtlPath = &elements[1][0];//fancy conversion of str:elements[1] to char*
				rsmgr->GetResource(mtlPath, "mtl");
				logger->Log(Logger::Logger::WARNING, "I am pretty sure we need to link the MTL to (parts of) the OBJ somehow...");
			}
			else if (elements[0] == "v"){
				Vertex newVertex;
				newVertex.x = strtof(elements[1].c_str(), 0);
				newVertex.y = strtof(elements[2].c_str(), 0);
				newVertex.z = strtof(elements[3].c_str(), 0);
				if (elements.size() > 4){
					newVertex.w = strtof(elements[4].c_str(), 0);
				}
				else {
					newVertex.w = 1.0f;
				}
				//mesh.vertices.push_back(newVertex);
				mesh->AddVertex(newVertex);
			}
			else if (elements[0] == "vt"){
				TextureCoordinate newTextureCoordinate;
				newTextureCoordinate.u = strtof(elements[1].c_str(), 0);
				newTextureCoordinate.v = strtof(elements[2].c_str(), 0);
				if (elements.size() > 3){
					newTextureCoordinate.w = strtof(elements[3].c_str(), 0);
				}
				else {
					newTextureCoordinate.w = 0.0f;
				}
				//mesh.textureCoordinates.push_back(newTextureCoordinate);
				mesh->AddTextureCoordinate(newTextureCoordinate);
			}
			else if (elements[0] == "vn"){
				Normal newNormal;
				newNormal.x = strtof(elements[1].c_str(), 0);
				newNormal.y = strtof(elements[2].c_str(), 0);
				newNormal.z = strtof(elements[3].c_str(), 0);
				//mesh.normals.push_back(newNormal);
				mesh->AddNormal(newNormal);
			}
			else if (elements[0] == "vp"){
				ParameterSpaceVertex newParameterSpaceVertex;
				newParameterSpaceVertex.u = strtof(elements[1].c_str(), 0);
				newParameterSpaceVertex.v = strtof(elements[2].c_str(), 0);
				newParameterSpaceVertex.w = strtof(elements[3].c_str(), 0);
				//mesh.parameterSpaceVertices.push_back(newParameterSpaceVertex);
				mesh->AddParameterSpaceVertex(newParameterSpaceVertex);
			}
			else if (elements[0] == "f"){
				for (unsigned int i = 1; i < elements.size(); ++i){
					faces = Logger::StringHelper::split(line, '/');
					FaceDefinition newFaceDefinition;
					newFaceDefinition.v1 = atoi(faces[0].c_str());;
					newFaceDefinition.v2 = atoi(faces[1].c_str());;
					newFaceDefinition.v3 = atoi(faces[2].c_str());;
					//mesh.faceDefinitions.push_back(newFaceDefinition);
					mesh->AddFaceDefinition(newFaceDefinition);
				}
			}
		}
		mesh->SetLoaded(true);
	}

	ifs.close();
	
	std::string strPath = path;
	logger->Log(Logger::Logger::DEBUG, "loaded: " + strPath);
	logger->Log(Logger::Logger::DEBUG, "vertices: " + std::to_string(mesh->GetVertices()->size()));
	logger->Log(Logger::Logger::DEBUG, "textureCoordinates: " + std::to_string(mesh->GetTextureCoordinates()->size()));
	logger->Log(Logger::Logger::DEBUG, "normals: " + std::to_string(mesh->GetNormals()->size()));
	logger->Log(Logger::Logger::DEBUG, "parameterSpaceVertices: " + std::to_string(mesh->GetParameterSpaceVertices()->size()));
	logger->Log(Logger::Logger::DEBUG, "faceDefinitions: " + std::to_string(mesh->GetFaceDefinitions()->size()));
	Logger::LoggerPool::GetInstance().ReturnLogger(logger);
	return (Resource*)mesh;
}