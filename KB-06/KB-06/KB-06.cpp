// KB-06.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdlib>
#include "logger.h"
#include "WindowManager.h"

int _tmain(int argc, _TCHAR* argv[])
{
	Logger::Logger* logger = Logger::Logger::GetLogger("main");
	logger->SetLogLevel(Logger::Logger::DEBUG);
	logger->Log(Logger::Logger::ERR, "Iets");
	logger->Log(Logger::Logger::WARNING, "Iets");
	logger->Log(Logger::Logger::DEBUG, "Iets");
	logger->Log(Logger::Logger::INFO, "Iets");

	Window::WindowManager* wManager = new Window::WindowManager(NULL);
	wManager->newWindow(NULL, 10, 10, 500, 500);
	wManager->getLastWindow()->SetTitle("Waarom lees jij deze titel? Het kost je meer tijd dan het waard is!");
	wManager->newWindow(NULL, 100, 100, 500, 500);
	wManager->getLastWindow()->SetTitle("Waarom lees jij deze titel? Het kost je meer tijd dan het waard is!");

	while (wManager->hasActiveWindow())
	{
		wManager->updateWindows();
		//Do things like input, game logic, ...
	}
	return 0;
}

