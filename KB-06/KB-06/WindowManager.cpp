#include "WindowManager.h"
#include <string>
#include "Logger.h"
#include "LoggerPool.h"
#include <sstream>
#include "stdafx.h"

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
};

HWND Window::WindowManager::NewWindow(Renderer *renderer, int x, int y, int width, int height)
{
	Logger::Logger* logger = Logger::LoggerPool::GetInstance().GetLogger();
	Window *window = new Window(renderer);
	HWND hwnd = window->Create(x, y, width, height, NULL, NULL, NULL);

	if (hwnd == NULL)
	{
		logger->Log(Logger::Logger::ERR, "Could not make window!");
		return NULL;
	}

	windows.push_back(window);
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

	for (long index = 0; index < (long)windows.size(); ++index) {
		windows.at(index)->render(NULL);// Todo: get the scene that has to be rendered in this window...
	}

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

	for (std::vector<Window*>::iterator it = windows.begin(); it != windows.end();) { // note the missing ++iter !
		
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