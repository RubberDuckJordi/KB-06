#include "WindowManager.h"
#include <string>
#include "Logger.h"
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

void Window::WindowManager::newWindow(Renderer *renderer, int x, int y, int width, int height)
{
	Window *window = new Window(renderer);
	HWND hwnd = window->Create(x, y, width, height, NULL, NULL, NULL);

	if (hwnd == NULL)
	{
		Logger::Logger::GetLogger("main")->Log(Logger::Logger::ERR, "Could not make window!");
		return;
	}

	windows.push_back(window);
};

void Window::WindowManager::updateWindows()
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

bool Window::WindowManager::hasActiveWindow()
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
		
		if ((*it)->state == closed)
		{
			//delete window
			delete * it;
			it = windows.erase(it);
		}
		else {
			++it;
		}
	}

	for (std::vector<Window*>::iterator it = windows.begin(); it != windows.end(); ++it) {
		/* std::cout << *it; ... */
	}

	if (windows.size() != 0)
	{
		return true;
	}
	return false;
};

Window::Window* Window::WindowManager::getLastWindow()
{
	return windows.back();
};