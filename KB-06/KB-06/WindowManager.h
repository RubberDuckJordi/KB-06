#ifndef _PENGINE_WINDOWMANAGER_H_
#define _PENGINE_WINDOWMANAGER_H_

#include "Window.h"
#include "WindowListener.h"
#include "Renderer.h"
#include "SceneManager.h"

#include <Windows.h>
#include <vector>

namespace pengine
{

	class WindowManager
	{
	public:
		/*!
		Constructor (creates WindowManager).

		@param sceneManager: SceneManager which is used to render a scene.
		*/
		WindowManager();
		~WindowManager();

		/*!
		Creates a new window and adds it to a list of windows.

		@param *renderer: A pointer to the renderer is passed to render scenes.
		@param x: The horizontal position of the upper left corner of the window.
		@param y: The vertical position of the upper left corner of the window.
		@param width: The width of the window.
		@param height: The height of the window.
		*/
		HWND NewWindow(int x, int y, int width, int height);

		/*!
		Loops through the list of windows to update them.
		*/
		void UpdateWindows();

		/*!
		Checks if there is an active window.
		*/
		bool HasActiveWindow();

		/*!
		Looks for windows with WindowState::CLOSED and deletes them from memory
		*/
		void PurgeClosedWindows();

		/*!
		Gives back the last created window.

		@return Window*: A pointer to the last window.
		*/
		Window* GetLastWindow();

		Window* GetWindowByHWND(HWND hwnd);
		std::vector<Window*>* GetAllWindows();

		void AddWindowListener(WindowListener* p_windowListener);
		void RemoveWindowListener(WindowListener* p_windowListener);
		void ClearWindowListeners();

	private:
		std::vector<Window*> windows;
		SceneManager *sceneManager;

		Logger* logger;
		std::list<WindowListener*> windowListeners;
	};
}
#endif
