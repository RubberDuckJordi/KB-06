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
	delete windows;
	delete sceneManager;
	delete list;
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

	list = new WindowList();

	list->window = window;
	list->next = windows;
	windows = list;
};

void Window::WindowManager::updateWindows()
{
	MSG Msg;
	while (PeekMessage(&Msg, NULL, 0U, 0U, true) > 0)//if there's more than one message, go through all of them.
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	WindowList *list = windows;
	while (list != NULL)//loop through all the windows so we can render them.
	{
		Window* window = list->window;
		window->render(NULL);// Todo: get the scene that has to be rendered in this window...
		list = list->next;
	}
};

bool Window::WindowManager::hasActiveWindow()
{
	WindowList *previous = NULL;
	WindowList *current = windows;
	while (current != NULL)
	{
		if (current->window->state == closed)
		{
			if (current == windows)//it's the current root
			{
				previous = current;
				current = current->next;
				windows = current;
				delete previous;
			}
			else
			{
				WindowList *toDelete = current;
				previous->next = current->next;
				current = current->next;
				delete toDelete;
			}
		}
		else
		{
			previous = current;
			current = current->next;
		}
	}

	if (windows != NULL)
	{
		return true;
	}
	return false;
};

Window::Window* Window::WindowManager::getLastWindow()
{
	return windows->window;
};