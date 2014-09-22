#ifndef __WINDOW_WINDOWLISTENER_H__
#define __WINDOW_WINDOWLISTENER_H__

#include "Window.h"

namespace Window
{
	class Window;

	class WindowListener
	{
	public:
		virtual void OnWindowFocusGained(Window* window) = 0;
		virtual void OnWindowFocusLost(Window* window) = 0;
		virtual void OnWindowCreated(Window* window) = 0;
	};
}

#endif