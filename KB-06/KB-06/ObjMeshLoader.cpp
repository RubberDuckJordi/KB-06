#include "stdafx.h"
#include "ObjMeshLoader.h"
#include "Mesh.h"
#include "Subset.h"
#include "StringHelper.h"
#include "LoggerPool.h"
#include "Material.h"

#include <vector>
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream

Resource::Mesh Resource::ObjMeshLoader::Load(const std::string file)
{
	std::ifstream ifs(file, std::ifstream::in);
	std::string line;
	std::vector<std::string> elements;
	std::vector<std::string> faces;
	std::vector<std::string> materials;

	Mesh mesh;
	int currentSubset;

	while (ifs.good())
	{
		getline(ifs, line);
		elements = Logger::StringHelper::split(line, ' ');
		if (elements.size() > 0)
		{
			if (elements[0] == "mtllib")
			{
				mesh.defaultMaterialFiles.push_back(elements[1]);
			}
			else if (elements[0] == "usemtl")
			{
				currentSubset = materials.size();
				Material material;
				material.name = elements[1];
				Subset subset;
				mesh.subsets.push_back(subset);
				mesh.subsets.at(currentSubset).defaultMaterial = material;
				materials.push_back(material.name);
			}
			else if (elements[0] == "v")
			{
				Vertex newVertex;
				newVertex.x = strtof(elements[1].c_str(), 0);
				newVertex.y = strtof(elements[2].c_str(), 0);
				newVertex.z = strtof(elements[3].c_str(), 0);
				if (elements.size() > 4)
				{
					newVertex.w = strtof(elements[4].c_str(), 0);
				}
				else
				{
					newVertex.w = 1.0f;
				}
				mesh.subsets.at(currentSubset).vertices.push_back(newVertex);

			}
			else if (elements[0] == "vt")
			{
				TextureCoordinate newTextureCoordinate;
				newTextureCoordinate.u = strtof(elements[1].c_str(), 0);
				newTextureCoordinate.v = strtof(elements[2].c_str(), 0);
				if (elements.size() > 3)
				{
					newTextureCoordinate.w = strtof(elements[3].c_str(), 0);
				}
				else
				{
					newTextureCoordinate.w = 0.0f;
				}
				mesh.subsets.at(currentSubset).textureCoordinates.push_back(newTextureCoordinate);
			}
			else if (elements[0] == "vn")
			{
				Normal newNormal;
				newNormal.x = strtof(elements[1].c_str(), 0);
				newNormal.y = strtof(elements[2].c_str(), 0);
				newNormal.z = strtof(elements[3].c_str(), 0);
				mesh.subsets.at(currentSubset).normals.push_back(newNormal);
			}
			else if (elements[0] == "vp")
			{
				ParameterSpaceVertex newParameterSpaceVertex;
				newParameterSpaceVertex.u = strtof(elements[1].c_str(), 0);
				newParameterSpaceVertex.v = strtof(elements[2].c_str(), 0);
				newParameterSpaceVertex.w = strtof(elements[3].c_str(), 0);
				mesh.subsets.at(currentSubset).parameterSpaceVertices.push_back(newParameterSpaceVertex);
			}
			else if (elements[0] == "f")
			{
				std::vector<int> faceDefinition;

				for (unsigned int i = 1; i < elements.size(); ++i)
				{
					faces = Logger::StringHelper::split(elements.at(i), '/');

					faceDefinition.push_back(atoi(faces[0].c_str()));
					faceDefinition.push_back(atoi(faces[1].c_str()));
					faceDefinition.push_back(atoi(faces[2].c_str()));
				}
				FaceDefinition newFaceDefinition;
				newFaceDefinition.v1 = faceDefinition.at(0) - 1;
				newFaceDefinition.v2 = faceDefinition.at(3) - 1;
				newFaceDefinition.v3 = faceDefinition.at(6) - 1;
				mesh.subsets.at(currentSubset).faceDefinitions.push_back(newFaceDefinition);
				newFaceDefinition.v1 = faceDefinition.at(6) - 1;
				newFaceDefinition.v2 = faceDefinition.at(9) - 1;
				newFaceDefinition.v3 = faceDefinition.at(0) - 1;
				mesh.subsets.at(currentSubset).faceDefinitions.push_back(newFaceDefinition);
			}
		}
	}
	ifs.close();
	mesh.fileName = file;
	Logger::Logger* logger = Logger::LoggerPool::GetInstance().GetLogger();
	logger->Log(Logger::DEBUG, "loaded: " + file);
	logger->Log(Logger::DEBUG, "subsets: " + std::to_string(mesh.subsets.size()));
	for (unsigned int i = 0; i < mesh.subsets.size(); ++i)
	{
		logger->Log(Logger::DEBUG, "vertices: " + std::to_string(mesh.subsets.at(i).vertices.size()));
		logger->Log(Logger::DEBUG, "textureCoordinates: " + std::to_string(mesh.subsets.at(i).textureCoordinates.size()));
		logger->Log(Logger::DEBUG, "normals: " + std::to_string(mesh.subsets.at(i).normals.size()));
		logger->Log(Logger::DEBUG, "parameterSpaceVertices: " + std::to_string(mesh.subsets.at(i).parameterSpaceVertices.size()));
		logger->Log(Logger::DEBUG, "faceDefinitions: " + std::to_string(mesh.subsets.at(i).faceDefinitions.size()));
	}
	Logger::LoggerPool::GetInstance().ReturnLogger(logger);
	return mesh;
}

std::string Resource::ObjMeshLoader::GetExtension()
{
	return "obj.mesh";
}