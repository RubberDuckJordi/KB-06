// KB-06.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdlib>
#include "loggerPool.h"
#include "WindowManager.h"

int _tmain(int argc, _TCHAR* argv[])
{
	Logger::Logger* logger = Logger::LoggerPool::GetInstance().GetLogger();
	logger->SetLogLevel(Logger::Logger::DEBUG);
	logger->Log(Logger::Logger::ERR, "Iets");
	logger->Log(Logger::Logger::WARNING, "Iets");
	logger->Log(Logger::Logger::DEBUG, "Iets");
	logger->Log(Logger::Logger::INFO, "Iets");

	Window::WindowManager* wManager = new Window::WindowManager(NULL);
	wManager->NewWindow(NULL, 10, 10, 500, 500);
	wManager->GetLastWindow()->SetTitle("Waarom lees jij deze titel? Het kost je meer tijd dan het waard is!");
	wManager->NewWindow(NULL, 100, 100, 500, 500);
	wManager->GetLastWindow()->SetTitle("Waarom lees jij deze titel? Het kost je meer tijd dan het waard is!");

	while (wManager->HasActiveWindow())
	{
		wManager->UpdateWindows();
		//Do things like input, game logic, ...
	}
	Logger::LoggerPool::GetInstance().ReturnLogger(logger);
	return 0;
}

