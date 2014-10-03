#ifndef _PENGINE_WINDOW_H_
#define _PENGINE_WINDOW_H_

#include "Scene.h"
#include "Renderer.h"
#include "Logger.h"
#include "WindowListener.h"

#include <Windows.h>

namespace pengine
{
	enum WindowState
	{
		fullscreen, maximized, normal, minimized, closed
	};

	class Window
	{
	public:
		Window();
		~Window();

		/*!
		Creates a window and returns it's HWND.

		@return HWND: The HWND of the created window.
		@param x: The horizontal position of the upper left corner of the window.
		@param y: The vertical position of the upper left corner of the window.
		@param nWidth: The width of the window.
		@param nHeight: The height of the window.
		@param hParent: The HWND of the creating window.
		@param hMenu: The menu of the created window.
		@param hInstance: The instance of this process.
		*/
		HWND Create(int x, int y, int nWidth, int nHeight, HWND hParent, HMENU hMenu, HINSTANCE hInstance);
		void Resize();
		void SetTitle(const char* title);
		HWND GetHWND();
		WindowState GetWindowState();

		/*!
		Abstract method that renders the given scene.

		@param *scene: The scene to be rendered.
		*/
		virtual void render(Scene *scene);

		void AddWindowListener(WindowListener* p_windowListener);
		void RemoveWindowListener(WindowListener* p_windowListener);
		void ClearWindowListeners();

	protected:
		static LRESULT CALLBACK BaseWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
		virtual LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
		WNDCLASSEX _WndClass;
		DWORD _dwExtendedStyle;
		DWORD _dwStyle;
		LPCWSTR _pszClassName;
		LPCWSTR _pszTitle;
		HWND _hwnd;
		WindowState state;
		std::list<WindowListener*> windowListeners;
		virtual void OnDestroy(HWND hwnd);

		Logger* logger;
	};
}
#endif