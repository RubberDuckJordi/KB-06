// KB-06.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdlib>
#include "logger.h"
#include "WindowManager.h"

int _tmain(int argc, _TCHAR* argv[])
{
	Logger* logger = Logger::GetLogger("main");
	logger->SetLogLevel(Logger::DEBUG);
	logger->Log(Logger::ERR, "Iets");
	logger->Log(Logger::WARNING, "Iets");
	logger->Log(Logger::DEBUG, "Iets");
	logger->Log(Logger::INFO, "Iets");

	WindowManager* wManager = new WindowManager(NULL);
	wManager->newWindow(NULL, 10, 10, 500, 500);
	wManager->getLastWindow()->SetTitle("Waarom lees jij deze titel? Het kost je meer tijd dan het waard was!");
	wManager->newWindow(NULL, 100, 100, 500, 500);
	wManager->getLastWindow()->SetTitle("Waarom lees jij deze titel? Het kost je meer tijd dan het waard was!");

	while (wManager->hasActiveWindow())
	{
		wManager->updateWindows();
		//Do things like input, game logic, ...
	}

	return 0;
}

