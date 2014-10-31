#ifndef _PENGINE_WINDOWLISTENER_H_
#define _PENGINE_WINDOWLISTENER_H_

#include "Window.h"

/*
Listener interface can be implemented and added to the window manager to receive events whenever a window is created, focus is gained or lost.

OnWindowFocusGained event is called from the Window
OnWindowCreated event is called from the WindowManager
*/

namespace pengine
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