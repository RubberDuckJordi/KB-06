#include "stdafx.h"
#include "ObjMeshFactory.h"
#include "Mesh.h"
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include "StringHelper.h"
#include "LoggerPool.h"

Resource::Mesh Resource::ObjMeshFactory::Load(const std::string file){
	std::ifstream ifs(file, std::ifstream::in);
	std::string line;
	std::vector<std::string> elements;
	std::vector<std::string> faces;

	Mesh mesh;
	while (ifs.good()) {
		getline(ifs, line);
		elements = Logger::StringHelper::split(line, ' ');
		if (elements.size() > 0){
			if (elements[0] == "mtllib"){
				//resourceManager->loadMaterials(elements[1]);
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
				mesh.vertices.push_back(newVertex);
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
				mesh.textureCoordinates.push_back(newTextureCoordinate);
			}
			else if (elements[0] == "vn"){
				Normal newNormal;
				newNormal.x = strtof(elements[1].c_str(), 0);
				newNormal.y = strtof(elements[2].c_str(), 0);
				newNormal.z = strtof(elements[3].c_str(), 0);
				mesh.normals.push_back(newNormal);
			}
			else if (elements[0] == "vp"){
				ParameterSpaceVertex newParameterSpaceVertex;
				newParameterSpaceVertex.u = strtof(elements[1].c_str(), 0);
				newParameterSpaceVertex.v = strtof(elements[2].c_str(), 0);
				newParameterSpaceVertex.w = strtof(elements[3].c_str(), 0);
				mesh.parameterSpaceVertices.push_back(newParameterSpaceVertex);
			}
			else if (elements[0] == "f"){
				for (unsigned int i = 1; i < elements.size(); ++i){
					faces = Logger::StringHelper::split(line, '/');
					FaceDefinition newFaceDefinition;
					newFaceDefinition.v1 = atoi(faces[0].c_str());;
					newFaceDefinition.v2 = atoi(faces[1].c_str());;
					newFaceDefinition.v3 = atoi(faces[2].c_str());;
					mesh.faceDefinitions.push_back(newFaceDefinition);
				}
			}
		}
	}

	ifs.close();
	Logger::Logger* logger = Logger::LoggerPool::GetInstance().GetLogger();
	logger->Log(Logger::Logger::DEBUG, "loaded: " + file);
	logger->Log(Logger::Logger::DEBUG, "vertices: " + std::to_string(mesh.vertices.size()));
	logger->Log(Logger::Logger::DEBUG, "textureCoordinates: " + std::to_string(mesh.textureCoordinates.size()));
	logger->Log(Logger::Logger::DEBUG, "normals: " + std::to_string(mesh.normals.size()));
	logger->Log(Logger::Logger::DEBUG, "parameterSpaceVertices: " + std::to_string(mesh.parameterSpaceVertices.size()));
	logger->Log(Logger::Logger::DEBUG, "faceDefinitions: " + std::to_string(mesh.faceDefinitions.size()));
	Logger::LoggerPool::GetInstance().ReturnLogger(logger);
	return mesh;
}

std::string Resource::ObjMeshFactory::GetExtension(){
	return "obj.mesh";
}