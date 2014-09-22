#include "WindowManager.h"
#include <string>
#include "LoggerPool.h"
#include <sstream>
#include "stdafx.h"

Window::WindowManager::WindowManager()
{
	logger = Logger::LoggerPool::GetInstance().GetLogger();
}

	Window::WindowManager::WindowManager(Scene::SceneManager *sManager)
{
	sceneManager = sManager;
};

Window::WindowManager::~WindowManager()
{
	while (!windows.empty())
	{
		delete windows.back(), windows.pop_back();
	}
	delete sceneManager;
	logger->Log(Logger::Logger::INFO, "WindowManager destructed");
	Logger::LoggerPool::GetInstance().ReturnLogger(logger);
};

HWND Window::WindowManager::NewWindow(int x, int y, int width, int height)
{
	Logger::Logger* logger = Logger::LoggerPool::GetInstance().GetLogger();
	Window *window = new Window();
	HWND hwnd = window->Create(x, y, width, height, NULL, NULL, NULL);

	if (hwnd == NULL)
	{
		logger->Log(Logger::Logger::ERR, "Could not make window!");
		return NULL;
	}

	windows.push_back(window);
	Logger::LoggerPool::GetInstance().ReturnLogger(logger);

	std::list<WindowListener*>::iterator listenersIt;
	for (listenersIt = windowListeners.begin(); listenersIt != windowListeners.end(); ++listenersIt)
	{
		(*listenersIt)->OnWindowCreated(window);
		window->AddWindowListener((*listenersIt));
	}

	return hwnd;
};

void Window::WindowManager::UpdateWindows()
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

};

bool Window::WindowManager::HasActiveWindow()
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
};

Window::Window* Window::WindowManager::GetLastWindow()
{
	return windows.back();
};

Window::Window* Window::WindowManager::GetWindowByHWND(HWND hwnd)
{
	for (std::vector<Window*>::iterator it = windows.begin(); it != windows.end();) { // note the missing ++iter !

		if ((*it)->GetHWND() == hwnd)
		{
			return *it;
		}
	}

	return NULL;
};

std::vector<Window::Window*>* Window::WindowManager::GetAllWindows()
{
	return &windows;
}

void Window::WindowManager::AddWindowListener(WindowListener* p_windowListener)
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

void Window::WindowManager::RemoveWindowListener(WindowListener* p_windowListener)
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

void Window::WindowManager::ClearWindowListeners()
{
	windowListeners.clear();
	std::vector<Window*>::iterator windowIt;
	for (windowIt = windows.begin(); windowIt != windows.end(); ++windowIt)
	{
		(*windowIt)->ClearWindowListeners();
	}
}