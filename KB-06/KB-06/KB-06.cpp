// KB-06.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdlib>
#include "logger.h"

int _tmain(int argc, _TCHAR* argv[])
{
	Logger* logger = Logger::getLogger("main");
	logger->log(Logger::ERR, "Iets");
	logger->log(Logger::WARNING, "Iets");
	logger->log(Logger::DEBUG, "Iets");
	logger->log(Logger::INFO, "Iets");
	return 0;
}

