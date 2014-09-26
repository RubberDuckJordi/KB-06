#include "WindowManager.h"
#include "LoggerPool.h"
#include "stdafx.h"

#include <string>
#include <sstream>

pengine::WindowManager::WindowManager()
{
	logger = LoggerPool::GetInstance().GetLogger();
}

pengine::WindowManager::WindowManager(pengine::SceneManager *sManager)
{
	sceneManager = sManager;
}

pengine::WindowManager::~WindowManager()
{
	while (!windows.empty())
	{
		delete windows.back(), windows.pop_back();
	}
	delete sceneManager;
	logger->Log(Logger::INFO, "WindowManager destructed");
	LoggerPool::GetInstance().ReturnLogger(logger);
}

HWND pengine::WindowManager::NewWindow(int x, int y, int width, int height)
{
	pengine::Logger* logger = pengine::LoggerPool::GetInstance().GetLogger();
	Window *window = new Window();
	HWND hwnd = window->Create(x, y, width, height, NULL, NULL, NULL);

	if (hwnd == NULL)
	{
		logger->Log(Logger::ERR, "Could not make window!");
		return NULL;
	}

	windows.push_back(window);
	pengine::LoggerPool::GetInstance().ReturnLogger(logger);

	std::list<WindowListener*>::iterator listenersIt;
	for (listenersIt = windowListeners.begin(); listenersIt != windowListeners.end(); ++listenersIt)
	{
		(*listenersIt)->OnWindowCreated(window);
		window->AddWindowListener((*listenersIt));
	}

	return hwnd;
}

void pengine::WindowManager::UpdateWindows()
{
	MSG Msg;
	while (PeekMessage(&Msg, NULL, 0U, 0U, true) > 0)//if there's more than one message, go through all of them.
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	/*  Window does not render; See renderer
	for (long index = 0; index < (long)windows.size(); ++index) {
	windows.at(index)->render(NULL);// Todo: get the scene that has to be rendered in this window...
	}
	*/
}

bool pengine::WindowManager::HasActiveWindow()
{
	/*for (int index = 0; index < windows.size(); ++index) {
		//windows.at(index)->render(NULL);// Todo: get the scene that has to be rendered in this window...
		if (windows.at(index)->state == closed)
		{
		//delete window
		delete windows.at(index);
		windows.erase(index);
		}
		}*/

	for (std::vector<Window*>::iterator it = windows.begin(); it != windows.end();) { // note the missing ++iter !; noted, does not work properly, attempts to destroy non instatiated objects

		if ((*it)->GetWindowState() == closed)
		{
			//delete window
			delete * it;
			it = windows.erase(it);
		}
		else {
			++it;
		}
	}

	if (windows.size() != 0)
	{
		return true;
	}
	return false;
}

pengine::Window* pengine::WindowManager::GetLastWindow()
{
	return windows.back();
}

pengine::Window* pengine::WindowManager::GetWindowByHWND(HWND hwnd)
{
	for (std::vector<Window*>::iterator it = windows.begin(); it != windows.end();) // note the missing ++iter !
	{

		if ((*it)->GetHWND() == hwnd)
		{
			return *it;
		}
	}

	return NULL;
}

std::vector<pengine::Window*>* pengine::WindowManager::GetAllWindows()
{
	return &windows;
}

void pengine::WindowManager::AddWindowListener(WindowListener* p_windowListener)
{
	if (p_windowListener != NULL)
	{
		windowListeners.push_back(p_windowListener);
		std::vector<Window*>::iterator windowIt;
		for (windowIt = windows.begin(); windowIt != windows.end(); ++windowIt)
		{
			(*windowIt)->AddWindowListener(p_windowListener);
		}

	}
}

void pengine::WindowManager::RemoveWindowListener(WindowListener* p_windowListener)
{
	if (p_windowListener != NULL)
	{
		windowListeners.remove(p_windowListener);
		std::vector<Window*>::iterator windowIt;
		for (windowIt = windows.begin(); windowIt != windows.end(); ++windowIt)
		{
			(*windowIt)->RemoveWindowListener(p_windowListener);
		}
	}
}

void pengine::WindowManager::ClearWindowListeners()
{
	windowListeners.clear();
	std::vector<Window*>::iterator windowIt;
	for (windowIt = windows.begin(); windowIt != windows.end(); ++windowIt)
	{
		(*windowIt)->ClearWindowListeners();
	}
}