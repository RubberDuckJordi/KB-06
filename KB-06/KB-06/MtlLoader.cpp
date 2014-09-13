#include "stdafx.h"
#include "MtlLoader.h"
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include <vector>
#include "Material.h"
#include "StringHelper.h"
#include "LoggerPool.h"
#include "MTLResource.h"


Resource::Resource* Resource::MtlLoader::LoadResource(char* path, ResourceManager* rsmgr)
{

	Logger::Logger* logger = Logger::LoggerPool::GetInstance().GetLogger();

	MTLResource* materials = new MTLResource();
	std::ifstream ifs(path, std::ifstream::in);
	std::string line;
	std::vector<std::string> elements;

	std::string currentMaterialName = "";//Wanted to use a char* directly but the issues that gave were above my paygrade...
	Material* currentMaterial = new Material;
	while (ifs.good()) {
		getline(ifs, line);
		elements = Logger::StringHelper::split(line, ' ');
		if (elements.size() > 0){
			if (elements[0] == "newmtl"){
				if (currentMaterialName == "")
				{
					currentMaterial = new Material;
				}
				else
				{
					std::string strPath = path;
					logger->Log(Logger::Logger::DEBUG, "loading: " + strPath);
					logger->Log(Logger::Logger::DEBUG, "Material name: " + currentMaterialName);
					logger->Log(Logger::Logger::DEBUG, "ambientColor: " + std::to_string(currentMaterial->ambientColor.r) + " " + std::to_string(currentMaterial->ambientColor.g) + " " + std::to_string(currentMaterial->ambientColor.b));
					logger->Log(Logger::Logger::DEBUG, "diffuseColor: " + std::to_string(currentMaterial->diffuseColor.r) + " " + std::to_string(currentMaterial->diffuseColor.g) + " " + std::to_string(currentMaterial->diffuseColor.b));
					logger->Log(Logger::Logger::DEBUG, "specularWeight: " + std::to_string(currentMaterial->specularWeight));

					materials->AddMaterial(&currentMaterialName[0], *currentMaterial);
					delete currentMaterial;
					currentMaterial = new Material;
				}
				std::vector<char> chars(elements[1].c_str(), elements[1].c_str() + elements[1].size() + 1u);
				currentMaterialName = &chars[0];
			}
			else if (elements[0] == "Ka")
			{
				currentMaterial->ambientColor.r = strtof(elements[1].c_str(), 0);
				currentMaterial->ambientColor.g = strtof(elements[2].c_str(), 0);
				currentMaterial->ambientColor.b = strtof(elements[3].c_str(), 0);
			}
			else if (elements[0] == "Kd")
			{
				currentMaterial->diffuseColor.r = strtof(elements[1].c_str(), 0);
				currentMaterial->diffuseColor.g = strtof(elements[2].c_str(), 0);
				currentMaterial->diffuseColor.b = strtof(elements[3].c_str(), 0);
			}
			else if (elements[0] == "Ks")
			{
				currentMaterial->SpecularColor.r = strtof(elements[1].c_str(), 0);
				currentMaterial->SpecularColor.g = strtof(elements[2].c_str(), 0);
				currentMaterial->SpecularColor.b = strtof(elements[3].c_str(), 0);
			}
			else if (elements[0] == "Ns")
			{
				logger->Log(Logger::Logger::INFO, "Ns");
				currentMaterial->specularWeight = strtof(elements[1].c_str(), 0);
			}
			else if (elements[0] == "d" || elements[0] == "Tr")
			{
				currentMaterial->alpha = strtof(elements[1].c_str(), 0);
			}
		}
		if (!ifs.good())
		{
			std::string strPath(path);
			logger->Log(Logger::Logger::DEBUG, "loaded: " + strPath);
			logger->Log(Logger::Logger::DEBUG, "Material name: " + currentMaterialName);
			logger->Log(Logger::Logger::DEBUG, "ambientColor: " + std::to_string(currentMaterial->ambientColor.r) + " " + std::to_string(currentMaterial->ambientColor.g) + " " + std::to_string(currentMaterial->ambientColor.b));
			logger->Log(Logger::Logger::DEBUG, "diffuseColor: " + std::to_string(currentMaterial->diffuseColor.r) + " " + std::to_string(currentMaterial->diffuseColor.g) + " " + std::to_string(currentMaterial->diffuseColor.b));
			logger->Log(Logger::Logger::DEBUG, "specularWeight: " + std::to_string(currentMaterial->specularWeight));
			materials->AddMaterial(&currentMaterialName[0], *currentMaterial);
			delete currentMaterial;
		}
	}
	ifs.close();
	materials->SetLoaded(true);

	Logger::LoggerPool::GetInstance().ReturnLogger(logger);
	return materials;
}