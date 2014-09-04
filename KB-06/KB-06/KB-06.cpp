// KB-06.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdlib>
#include "logger.h"

int _tmain(int argc, _TCHAR* argv[])
{
	Logger* logger = Logger::GetLogger("main");
	logger->SetLogLevel(Logger::DEBUG);
	logger->Log(Logger::ERR, "Iets");
	logger->Log(Logger::WARNING, "Iets");
	logger->Log(Logger::DEBUG, "Iets");
	logger->Log(Logger::INFO, "Iets");
	return 0;
}

